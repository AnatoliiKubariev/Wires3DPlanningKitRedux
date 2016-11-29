#pragma once

#include "GraphicsScene.h"
#include "ui_SecondView2D.h"

#include <QWidget>

class Controller;

class SecondView2D: public QWidget
{
    Q_OBJECT

public:
    SecondView2D(Controller& controller, QWidget* parent = 0);

    void Remove(const int id);

private:
    Ui::SecondView2D m_ui;

    GraphicsScene m_scene;
};