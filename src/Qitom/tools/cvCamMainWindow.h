#pragma once

#include <QMainWindow>
#include "ui_cvCamMainWindow.h"

class cvCamMainWindow : public QMainWindow
{
	Q_OBJECT

public:
	cvCamMainWindow(QWidget *parent = nullptr);
	~cvCamMainWindow();

private:
	Ui::cvCamMainWindowClass ui;
};
