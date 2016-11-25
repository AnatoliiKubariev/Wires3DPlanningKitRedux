#pragma once

#include "GraphicsScene.h"
#include "ui_SecondView2D.h"

#include <QWidget>

class Controller;

class SecondView2D: public QWidget
{
    Q_OBJECT

public:
    SecondView2D(Controller& controller, UndoRedoStack& commands, QWidget* parent = 0);

    void Update(ModelSocket& socket);
    void Remove(ModelSocket& socket);

private:
    Ui::SecondView2D m_ui;

    GraphicsScene m_scene;
};