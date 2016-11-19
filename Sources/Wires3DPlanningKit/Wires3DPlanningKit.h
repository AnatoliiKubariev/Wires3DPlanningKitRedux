#pragma once

#include "View2D.h"
#include "UndoRedoStack.h"
#include "Model.h"
#include "ui_Wires3DPlanningKit.h"

#include <memory>

#include <QtWidgets/QMainWindow>

class ViewState;

class Wires3DPlaningKit : public QMainWindow
{
	Q_OBJECT

public:
	Wires3DPlaningKit(QWidget *parent = 0);

private:
	Ui::Wires3DPlaningKitClass m_ui;

	Model m_model;
    UndoRedoStack m_commands;
	View2D m_view_2d;
};
