#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_QtApp.h"
#include "QChart.h"
#include "QChartView.h"
#include "QSplineSeries.h"
#include <QSerialPort>
#include <vector>

struct comm_data_t
{
	uint16_t header;
	uint8_t  function_code;
	uint8_t  length;
	uint8_t  check_sum;
    uint16_t index;
	uint16_t finger_status;
};

struct calc_data_t
{
    int hr;
	int fatigue;
	int breathe;
};

QT_CHARTS_USE_NAMESPACE

class QtApp : public QMainWindow
{
	Q_OBJECT

public:
	QtApp(QWidget *parent = Q_NULLPTR);
	~QtApp();

	void ClosePort();

	void Refresh(int data);

	void Refresh(int *buffer, int size);

public Q_SLOTS:

	void ConnectCOM();

	void filter_result(const int *filterResult, const int size);

	void receiveInfo();

private:
	Ui::QtAppClass ui;

	QChart *_qChart;
	QChartView *_qChartView;
	QSplineSeries *_qSplineSeries;
	QSerialPort *_pSelectedSerialPort;

	std::vector<uint8_t> _listOfRawData;
	uint8_t _checkSum;
	comm_data_t _commData;
	calc_data_t _calcData;

	QList<int> _listOfPointData;
};
