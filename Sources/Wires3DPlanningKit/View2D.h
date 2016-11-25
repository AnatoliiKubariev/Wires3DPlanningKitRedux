#pragma once

#include "GraphicsScene.h"
#include "ui_View2D.h"

#include <QWidget>

class Controller;

class View2D: public QWidget
{
    Q_OBJECT

public:
    View2D(Controller& controller, UndoRedoStack& commands, QWidget* parent = 0);

    void Update(ModelSocket& socket);
    void Remove(ModelSocket& socket);

private:
    Ui::View2DClass m_ui;

    GraphicsScene m_scene;
};
