#pragma once

#include <QMainWindow>
#include "ui_hiMainWindow.h"

class hiMainWindow : public QMainWindow
{
	Q_OBJECT

public:
	hiMainWindow(QWidget *parent = nullptr);
	~hiMainWindow();

private:
	Ui::hiMainWindowClass ui;
};
