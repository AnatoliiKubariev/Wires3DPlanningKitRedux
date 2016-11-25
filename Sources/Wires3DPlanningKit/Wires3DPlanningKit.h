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

    void Update(const ModelSocket& socket);
    void Remove(const ModelSocket& socket);

private:
    void InitializeUndoRedo();

	Ui::Wires3DPlaningKitClass m_ui;

	Model m_model;
    Controller m_controller;
    UndoRedoStack m_commands;

    View2D m_view_2d;
    SecondView2D m_second_view_2d;
};