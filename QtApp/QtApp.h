#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_QtApp.h"
#include "QChart.h"
#include "QChartView.h"
#include "QSplineSeries.h"
#include <QSerialPort>

#include <vector>

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
	uint16_t _ecgIndex;
	uint8_t _checkSum;

	QList<int> _listOfPointData;
};
