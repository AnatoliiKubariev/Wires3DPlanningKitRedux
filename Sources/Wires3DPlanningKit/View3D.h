#pragma once

#include <QWidget>

class Model;

class View3D: public QWidget
{
	Q_OBJECT

public:
	View3D(Model& model, QWidget* parent = 0);

private:
	Model& m_model;
};