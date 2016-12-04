#pragma once

#include <QWidget>

class Controller;

class View3D: public QWidget
{
	Q_OBJECT

public:
	View3D(Controller& controller, QWidget* parent = 0);

private:
    Controller& m_controller;
};