#include "QtApp.h"
#include <QSerialPortInfo>
#include <QMessageBox>
#include "QValueAxis.h"
#include "QSplineSeries.h"
#include "qDebug"
#include <algorithm>
#include <random>
#include <sstream>

#include "cppToOc.h"
#include "calc_hr_breath_fatigue.h"


#define DATA_LENGTH             100
#define DATA_SIZE_MAX           1500

#define ECG_FRAME_HEADER        0x55AA
#define ECG_FUNCTIONCODE_LEAD   0x0001
#define ECG_FUNCTIONCODE_DATA   0x0002

#define ECG_STATUS_ALL_OFF      0x0000
#define ECG_STATUS_LEFT_OFF     0x0001
#define ECG_STATUS_RIGHT_OFF    0x0002


QtApp::QtApp(QWidget *parent)
: QMainWindow(parent)
, _qChart(nullptr)
, _qChartView(nullptr)
, _qSplineSeries(nullptr)
, _pSelectedSerialPort(nullptr)
, _listOfRawData(0)
, _checkSum(0)
{
	_commData = {};
	_calcData = {};
	ui.setupUi(this);

	constexpr unsigned short com_port_vid = 0x1A86;
	constexpr unsigned short com_port_pid = 0x7523;

	//ui.InfoTableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
	//QBrush myBrush;
	//QPalette palette;
	//myBrush = QBrush(Qt::green, Qt::DiagCrossPattern);
	//palette.setBrush(QPalette::Text, myBrush);
	//ui.HRStatusLineEdit->setPalette(palette);

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
	axisY->setRange(-900, 900);
	//axisY->hide();
	//axisY->setLinePenColor(_qSplineSeries->pen().color());

	_qChart->addAxis(axisY, Qt::AlignLeft);
	_qSplineSeries->attachAxis(axisX);
	_qSplineSeries->attachAxis(axisY);
	_qSplineSeries->setUseOpenGL(true);
	_qSplineSeries->setColor(Qt::yellow);


	_qChartView = new QChartView(_qChart);
	_qChartView->setRenderHint(QPainter::Antialiasing);

	ui.verticalLayout->addWidget(_qChartView);
	//this->setCentralWidget(_qChartView);
	_qChart->setBackgroundBrush(QImage("images/background.jpg"));

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
		ui.HRStatusLineEdit->clear();
		ui.BreathLineEdit->clear();
		ui.TiredLineEdit->clear();
		_checkSum = 0;

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
		ui.HRStatusLineEdit->clear();
		ui.BreathLineEdit->clear();
		ui.TiredLineEdit->clear();
		_checkSum = 0;
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
	if (size < 7)
		return;

	uint8_t *raw_data = new uint8_t[size];
	memcpy(raw_data, info.data(), size);

	qDebug() << size << " : " << info << endl;

	//parse data
	uint16_t header(0);
	uint8_t function_code(0);
	uint8_t length(0);
	uint8_t check_sum(0);
	uint16_t index(0);
	uint16_t finger_status(0);

	header = raw_data[1] + (raw_data[0] << 8);

	if (ECG_FRAME_HEADER == header)
	{
		ui.HRStatusLineEdit->clear();
		ui.BreathLineEdit->clear();
		ui.TiredLineEdit->clear();

		_listOfRawData.clear();
		_checkSum = 0;

		//memcpy(&function_code, &(info.data()[sizeof(uint16_t)]), sizeof(uint8_t));
		//memcpy(&length, &(info.data()[sizeof(uint16_t)+sizeof(uint8_t)]), sizeof(uint8_t));
		function_code = raw_data[2];
		length = raw_data[3];

		_checkSum += 0x55+0xaa+ function_code+ length;

		//if (size < length)
		//	return;

		if (ECG_FUNCTIONCODE_LEAD == function_code)
		{
			//memcpy(&finger_status, &(info.data()[sizeof(uint16_t) + sizeof(uint8_t)*2]), sizeof(uint16_t));
			//memcpy(&check_sum, &(info.data()[sizeof(uint16_t)*2+sizeof(uint8_t)*2]), sizeof(uint8_t));
			finger_status = raw_data[5] + (raw_data[4] << 8);
			check_sum = raw_data[6];

			if (ECG_STATUS_ALL_OFF == finger_status)
			{
				ui.checkBoxBoth->setChecked(false);
				ui.checkBoxRight->setChecked(false);
				ui.checkBoxLeft->setChecked(false);
			}
			else if (ECG_STATUS_LEFT_OFF == finger_status)
			{
				ui.checkBoxBoth->setChecked(false);
				ui.checkBoxRight->setChecked(true);
				ui.checkBoxLeft->setChecked(false);
			}
			else if (ECG_STATUS_RIGHT_OFF == finger_status)
			{
				ui.checkBoxBoth->setChecked(false);
				ui.checkBoxRight->setChecked(false);
				ui.checkBoxLeft->setChecked(true);
			}
			else
			{
				//ui.radioButton_both->setChecked(true);
				//ui.handLineEdit->text = "left hand";
			}

			//fill data
			_commData.header = header;
			_commData.function_code = function_code;
			_commData.finger_status = finger_status;
			_commData.check_sum = check_sum;
			
			return;
		}
		else if (ECG_FUNCTIONCODE_DATA == function_code)
		{
			ui.statusBar->showMessage("");
			//memcpy(&index, &(info.data()[sizeof(uint16_t) + sizeof(uint8_t) * 2]), sizeof(uint16_t));
			index = raw_data[5] + (raw_data[4] << 8);
			_checkSum += (raw_data[5] + raw_data[4]);

			//header(2 bytes)+function_code(1 byte)+length(1 byte)+index(2 bytes)
			//start at 6th
			for (int i = 6; i < size; i++)
			{
				_listOfRawData.push_back(raw_data[i]);
				_checkSum += raw_data[i];
			}

			//both hands
			ui.checkBoxBoth->setChecked(true);

			//fill data
			_commData.header = header;
			_commData.function_code = function_code;
			_commData.index = index;

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
			_listOfRawData.push_back(raw_data[i]);
			if(_listOfRawData.size()<=200)
				_checkSum += raw_data[i];
			else
			{
				check_sum = raw_data[i];
				//qDebug() << "_checkSum = " << _checkSum << endl;
				//qDebug() << "check_sum = " << check_sum << endl;
				if(_checkSum==check_sum)
					ui.statusBar->showMessage("OK");
				else
					ui.statusBar->showMessage("Error");

				//fill data
				_commData.check_sum = check_sum;
			}

		}
	}
	
	delete[] raw_data;
	raw_data = NULL;

	if (_listOfRawData.size() >= 200)//drop the other data
	{

		//display raw data
		std::string rawBytes ="data received:";

		rawBytes += "head:" + std::to_string(_commData.header) + ";";
		rawBytes += "fcode:" + std::to_string(_commData.function_code) + ";";
		rawBytes += "length:" + std::to_string(_commData.length) + ";";
		rawBytes += "index:" + std::to_string(_commData.index) + ";";
		rawBytes += "fstatus:" + std::to_string(_commData.finger_status) + ";";
		rawBytes += "datasize:" + std::to_string(_listOfRawData.size() - 1) + ";";
		rawBytes += "checksum:" + std::to_string(_commData.check_sum) + ";";
		//for each(uint8_t rawbyte in _listOfRawData)
		//{
		//	rawBytes += std::to_string(rawbyte) + " ";
		//}
		//rawBytes +=  stream.str() + "\n";
		rawBytes += "\n";
		QString str = QString::fromUtf8(rawBytes.c_str());
		ui.textBrowser->append(str);

		//display chart
		int *result = NULL;
		std::vector<uint16_t> listOfData(DATA_LENGTH);
		for (uint32_t i = 0; i < DATA_LENGTH; i ++)
		{
			listOfData[i] = _listOfRawData[2*i + 1] + (_listOfRawData[2*i] << 8);
		}
		std::vector<int> listOfDataInput(DATA_LENGTH);
		for (int i = 0; i < DATA_LENGTH; i++)
			listOfDataInput[i] = listOfData[i];

		std::vector<int> listOfDataOutput(DATA_LENGTH);
		result = filter(listOfDataInput.data(), listOfDataOutput.data(), DATA_LENGTH);
		this->Refresh(listOfDataOutput.data(), listOfDataOutput.size());

		//display hr_breath_fatigue
		int *calcResult = new int[3];
		calc_result(listOfDataInput.data(), 100, calcResult);
		//printf("HR:%d, FATIGUE:%d, BREATHRATE:%d\n", calcResult[0], result[1], result[2]);

		_calcData.hr = calcResult[0];
		_calcData.fatigue = calcResult[1];
		_calcData.breathe = calcResult[2];

		//ui.BreathLineEdit->clear();
		ui.BreathLineEdit->setText(QString::number(_calcData.breathe));
		//ui.TiredLineEdit->clear();
		ui.TiredLineEdit->setText(QString::number(_calcData.fatigue));
		//ui.HRStatusLineEdit->clear();
		ui.HRStatusLineEdit->setText(QString::number(_calcData.hr));

		delete calcResult;
		//delete result;

	}
	
	//ui.checkBoxBoth->setChecked(false);
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