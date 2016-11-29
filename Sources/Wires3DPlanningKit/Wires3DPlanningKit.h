#pragma once

#include "Controller.h"
#include "View2D.h"
#include "UndoRedoStack.h"
#include "Model.h"
#include "ui_Wires3DPlanningKit.h"

#include "SecondView2D.h"

#include <memory>

#include <QtWidgets/QMainWindow>

class ViewState;

class Wires3DPlaningKit : public QMainWindow
{
	Q_OBJECT

public:
	Wires3DPlaningKit(QWidget *parent = 0);

private:
    void Undo();
    void Redo();

    void InitializeUndoRedo();

	Ui::Wires3DPlaningKitClass m_ui;

    View2D m_view_2d;
    View2D m_second_view_2d;

	Model m_model;
    Controller m_controller;
};