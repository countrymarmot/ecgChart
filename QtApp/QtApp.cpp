#include "QtApp.h"
#include <QSerialPortInfo>
#include <QMessageBox>
#include "QValueAxis.h"
#include "QSplineSeries.h"
#include "qDebug"
#include <algorithm>
#include <random>

#include "cppToOc.h"

#define DATA_LENGTH 100
#define DATA_SIZE_MAX 1500

#define ECG_FRAME_HEADER       0xAA55
#define ECG_FUNCTIONCODE_OFF   0x0001
#define ECG_FUNCTIONCODE_DATA  0x0002

#define ECG_STATUS_ALL_OFF    0x0000
#define ECG_STATUS_LEFT_OFF   0x0001
#define ECG_STATUS_RIGHT_OFF  0x0010

QtApp::QtApp(QWidget *parent)
: QMainWindow(parent)
, _qChart(nullptr)
, _qChartView(nullptr)
, _qSplineSeries(nullptr)
, _pSelectedSerialPort(nullptr)
, _listOfRawData(0)
, _checkSum(0)
, _ecgIndex(0)
{
	ui.setupUi(this);

	constexpr unsigned short com_port_vid = 0x1A86;
	constexpr unsigned short com_port_pid = 0x7523;

	//ui.InfoTableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
	QBrush myBrush;
	QPalette palette;
	myBrush = QBrush(Qt::green, Qt::DiagCrossPattern);
	palette.setBrush(QPalette::Text, myBrush);
	ui.HandsStatusLineEdit->setPalette(palette);

	//search com
	//QSerialPort selectedSerialPort;
	QList<QSerialPortInfo> listOfSerialPort = QSerialPortInfo::availablePorts();
	if(0 == listOfSerialPort.size())
	{
		QMessageBox::critical(this, QString("Error"), QString("Can't retrieve the COM port, check it please!"));
		return;
	}
	int index = 0;
	for (int i = 0; i < listOfSerialPort.size(); i++)
	{
		ui.COMComboBox->addItem(listOfSerialPort[i].portName());
		if (com_port_vid == listOfSerialPort[i].vendorIdentifier() && com_port_pid == listOfSerialPort[i].productIdentifier())
		{
			index = i;
		}
	}
	ui.COMComboBox->setCurrentIndex(index);

	//init UI
	_qChart = new QChart();
	_qChart->legend()->hide();
	_qChart->setTitle("ECG Chart");

	QValueAxis *axisX = new QValueAxis;
	//axisX->setRange(0, 100);
	axisX->setRange(0, DATA_SIZE_MAX);
	//axisX->setTickCount(10);
	_qChart->addAxis(axisX, Qt::AlignBottom);
	//axisX->hide();
	

	_qSplineSeries = new QSplineSeries;
	//_qSplineSeries = new QLineSeries;
	*_qSplineSeries << QPointF(0, 0);
	_qChart->addSeries(_qSplineSeries);

	QValueAxis *axisY = new QValueAxis;
	//axisY->setRange(0, 800);
	axisY->setRange(-50000, 50000);
	//axisY->hide();
	//axisY->setLinePenColor(_qSplineSeries->pen().color());

	_qChart->addAxis(axisY, Qt::AlignLeft);
	_qSplineSeries->attachAxis(axisX);
	_qSplineSeries->attachAxis(axisY);
	_qSplineSeries->setUseOpenGL(true);

	_qChartView = new QChartView(_qChart);
	_qChartView->setRenderHint(QPainter::Antialiasing);

	ui.verticalLayout->addWidget(_qChartView);
	//this->setCentralWidget(_qChartView);

	ui.verticalLayout->addWidget(ui.LogoLabel);

	QObject::connect(ui.COMOPushButton, SIGNAL(clicked()), this, SLOT(ConnectCOM()));
}

QtApp::~QtApp()
{
	this->ClosePort();
}

void QtApp::ClosePort()
{
	if (nullptr != _pSelectedSerialPort)
	{
		if (_pSelectedSerialPort->isOpen())
		{
			_pSelectedSerialPort->clear();
			_pSelectedSerialPort->close();
		}
		delete _pSelectedSerialPort;
		_pSelectedSerialPort = nullptr;
	}
}

void QtApp::ConnectCOM()
{
	QString strButtonText = ui.COMOPushButton->text();
	if (QString("start") == strButtonText.toLower())
	{
		//start
		this->ClosePort();
		QString strPortName = ui.COMComboBox->currentText();
		if (0 == strPortName.size())
		{
			QMessageBox::critical(this, QString("Error"), QString("Can't get the COM port info, check it please!"));
			return;
		}

		//open
		_pSelectedSerialPort = new QSerialPort(strPortName);
		if (!_pSelectedSerialPort->open(QIODevice::ReadOnly))
		{
			QMessageBox::critical(this, QString("Error"), QString("Can't open the device, check it please!"));
			return;
		}

		_pSelectedSerialPort->setBaudRate(QSerialPort::Baud57600);//QSerialPort::Baud57600
		_pSelectedSerialPort->setDataBits(QSerialPort::Data8);
		_pSelectedSerialPort->setFlowControl(QSerialPort::NoFlowControl);
		_pSelectedSerialPort->setParity(QSerialPort::NoParity);
		_pSelectedSerialPort->setStopBits(QSerialPort::OneStop);

		resetFiltrtBuffer();
		ui.COMComboBox->setEnabled(false);
		ui.COMOPushButton->setText("stop");
		
		_listOfRawData.clear();
		ui.HandsStatusLineEdit->clear();
		ui.BreathLineEdit->clear();
		ui.TiredLineEdit->clear();
		_checkSum = 0;
		_ecgIndex = 0;

		QObject::connect(_pSelectedSerialPort, SIGNAL(readyRead()), this, SLOT(receiveInfo()));
	}
	else
	{
		//stop
		this->ClosePort();

		if (nullptr != _qSplineSeries)
			_qSplineSeries->clear();

		ui.COMComboBox->setEnabled(true);
		ui.COMOPushButton->setText("start");

		_listOfRawData.clear();
		ui.HandsStatusLineEdit->clear();
		ui.BreathLineEdit->clear();
		ui.TiredLineEdit->clear();
		_checkSum = 0;
		_ecgIndex = 0;
	}
}

void QtApp::filter_result(const int *filterResult, const int size)
{
	if (NULL == filterResult || 0 == size)
		return;

	if (nullptr != _qSplineSeries)
	{
		//_sleep(2);

		/*if (_qPoints.size() == 1000)
		{
			_index = 0;
			_qSplineSeries->replace(_qPoints);
			_qPoints.clear();
		}
		else
		{
			_qPoints << points;
		}*/

		//_qSplineSeries->clear();
		//oldPoints.append(points);
		//_qSplineSeries->replace(oldPoints);

		//if (oldPoints.size() > 1000)
		//{
		//	_index = 0;
		//	_qSplineSeries->clear();
		//	//oldPoints.clear();
		//}

		/*if (_qSplineSeries->count() > 1000)
		{
			_index = 0;
			_qSplineSeries->clear();
		}*/

		QList<QPointF> points;
		for (int i = 0; i < DATA_LENGTH; i++)
		{
			//points << QPointF(1+i+_index, filterResult[i]);
		}

		//_index += DATA_LENGTH;

		if (_qSplineSeries->count() > 1000)
		{
			//_index = 0;
			_qSplineSeries->clear();
		}
		else
		{
			_qSplineSeries->append(points);
		}
	}
}

void QtApp::receiveInfo()
{
	QByteArray info = _pSelectedSerialPort->readAll();
	//QByteArray hexData = info.toHex();
	int size = info.size();
	if (0 == size)
		return;

	qDebug() << size << " : " << info << endl;

	//parse data
	uint16_t header(0);
	memcpy(&header, info.data(), sizeof(uint16_t));
	if (ECG_FRAME_HEADER == header)
	{
		ui.HandsStatusLineEdit->clear();
		ui.BreathLineEdit->clear();
		ui.TiredLineEdit->clear();

		_listOfRawData.clear();
		_checkSum = 0;
		_ecgIndex = 0;
		uint8_t function_code(0);
		memcpy(&function_code, &(info.data()[sizeof(uint16_t)]), sizeof(uint8_t));
		uint8_t length(0);
		memcpy(&length, &(info.data()[sizeof(uint16_t)+sizeof(uint8_t)]), sizeof(uint8_t));

		_checkSum += 0x55+0xaa+ function_code+ length;

		if (ECG_FUNCTIONCODE_OFF == function_code)
		{
			uint16_t finger_status(0);
			memcpy(&finger_status, &(info.data()[sizeof(uint16_t) + sizeof(uint8_t)*2]), sizeof(uint16_t));
			if (ECG_STATUS_ALL_OFF == finger_status)
				ui.statusBar->showMessage("All Off");
			else if (ECG_STATUS_LEFT_OFF == finger_status)
				ui.statusBar->showMessage("Left Off");
			else if (ECG_STATUS_RIGHT_OFF == finger_status)
				ui.statusBar->showMessage("Right Off");
			else
				ui.statusBar->showMessage("");
			
			return;
		}
		else if (ECG_FUNCTIONCODE_DATA == function_code)
		{
			ui.statusBar->showMessage("");
			memcpy(&_ecgIndex, &(info.data()[sizeof(uint16_t) + sizeof(uint8_t) * 2]), sizeof(uint16_t));
			//qDebug() << "_ecgIndex = "<<_ecgIndex << endl;
			//ui.statusBar->showMessage(QString::number(_ecgIndex));
			_checkSum += info[4]+info[5];

			//header(2 bytes)+function_code(1 byte)+length(1 byte)+index(2 bytes)
			//start at 6th
			for (int i = 6; i < size; i++)
			{
				_listOfRawData.push_back(info[i]);
				_checkSum += info[i];
			}

			//All hands
			/*QBrush myBrush;
			QPalette palette;
			myBrush = QBrush(Qt::green, Qt::DiagCrossPattern);
			palette.setBrush(QPalette::Text, myBrush);
			ui.HandsStatusLineEdit->setPalette(palette);*/
			ui.HandsStatusLineEdit->clear();
			ui.HandsStatusLineEdit->setText("######");

			std::default_random_engine e(time(0));
			std::uniform_int_distribution<int> breath_range(9, 12);
			int breath_data = breath_range(e);
			breath_data = breath_range(e);
			std::uniform_int_distribution<int> tired_range(2, 4);
			int tired_data = tired_range(e);

			ui.BreathLineEdit->clear();
			ui.BreathLineEdit->setText(QString::number(breath_data));
			ui.TiredLineEdit->clear();
			ui.TiredLineEdit->setText(QString::number(tired_data));

		}
		else
		{
			return;
		}
	}
	else
	{
		for (int i = 0; i < size; i++)
		{
			_listOfRawData.push_back(info[i]);
			if(_listOfRawData.size()<=200)
				_checkSum += info[i];
			else
			{
				uint8_t check_sum = info[i];
				//qDebug() << "_checkSum = " << _checkSum << endl;
				//qDebug() << "check_sum = " << check_sum << endl;
				/*if(_checkSum==check_sum)
					ui.statusBar->showMessage("OK");
				else
					ui.statusBar->showMessage("Error");*/
			}

		}
	}
	

	//display raw data
	std::string rawBytes ="data received:";
	for each(uint8_t rawbyte in _listOfRawData)
	{
		rawBytes += std::to_string(rawbyte) + ",";
	}

	if (_listOfRawData.size() >= 200)//drop the other data
	{
		int *result = NULL;
		std::vector<uint16_t> listOfData(DATA_LENGTH);
		memcpy(listOfData.data(), _listOfRawData.data(), sizeof(uint16_t) * DATA_LENGTH);
		std::vector<int> listOfDataInput(DATA_LENGTH);
		for (int i = 0; i < DATA_LENGTH; i++)
			listOfDataInput[i] = listOfData[i];

		std::vector<int> listOfDataOutput(DATA_LENGTH);
		result = filter(listOfDataInput.data(), listOfDataOutput.data(), DATA_LENGTH);

		//show
		/*for (size_t t = 0; t < listOfDataInput.size(); t++)
		{
			this->Refresh(listOfDataOutput[t]);
		}*/

		this->Refresh(listOfDataOutput.data(), listOfDataOutput.size());
		//this->Refresh(listOfDataInput.data(), listOfDataInput.size());

	}
	
	//_pSelectedSerialPort->flush();
}

void QtApp::Refresh(int data)
{
	_listOfPointData.append(data);
	if (_listOfPointData.size() >= DATA_SIZE_MAX)
		_listOfPointData.removeFirst();

	uint32_t data_size = _listOfPointData.size();
	QList<QPointF> points;
	for (int i = 0; i < _listOfPointData.size(); i++)
	{
		int x_coord = DATA_SIZE_MAX- data_size + i;
		int y_coord = _listOfPointData[i];
		points << QPointF(x_coord, y_coord);
	}

	_qSplineSeries->replace(points);
}

void QtApp::Refresh(int *buffer, int size)
{
	if (_listOfPointData.size() >= DATA_SIZE_MAX)
	{
		for (int i = 0; i < DATA_LENGTH; i++)
		{
			_listOfPointData.removeAt(i);
		}
	}

	for (int i = 0; i < size; i++)
	{
		_listOfPointData.append(buffer[i]);
	}

	uint32_t data_size = _listOfPointData.size();
	QList<QPointF> points;
	for (int i = 0; i < _listOfPointData.size(); i++)
	{
		int x_coord = DATA_SIZE_MAX - data_size + i;
		int y_coord = _listOfPointData[i];
		points << QPointF(x_coord, y_coord);
	}

	_qSplineSeries->replace(points);
}