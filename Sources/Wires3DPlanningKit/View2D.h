#pragma once

#include "GraphicsScene.h"
#include "ui_View2D.h"

#include <QWidget>

class Controller;

class View2D: public QWidget
{
    Q_OBJECT

public:
    View2D(Controller& controller, QWidget* parent = 0);

    void Update(const ModelSocket& model_socket);
    void Remove(const int id);

private:
    Ui::View2DClass m_ui;

    GraphicsScene m_scene;
};
