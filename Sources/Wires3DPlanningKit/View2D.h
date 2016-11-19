#pragma once

#include "GraphicsScene.h"
#include "ui_View2D.h"

#include <QWidget>

class View2D: public QWidget
{
	Q_OBJECT

public:
	View2D(Model& model, UndoRedoStack& commands, QWidget* parent = 0);

private:
    void InitializeUndoRedo();

	Ui::View2DClass m_ui;

	GraphicsScene m_scene;
};
