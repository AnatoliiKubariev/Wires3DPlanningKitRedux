#include "Wires3DPlanningKit.h"

#include "View3D.h"

#include <QLayout>

Wires3DPlaningKit::Wires3DPlaningKit(QWidget *parent)
	: QMainWindow(parent)
	, m_model()
    , m_controller(m_model)
    , m_view_2d(m_controller, this)
    , m_second_view_2d(m_controller, this)
{
	m_ui.setupUi(this);

    InitializeUndoRedo();

    m_controller.AddView(&m_view_2d);
    m_controller.AddView(&m_second_view_2d);

    QWidget* widget = new QWidget(this);
    QVBoxLayout *layout = new QVBoxLayout(widget);

    layout->addWidget(&m_view_2d);
    layout->addWidget(&m_second_view_2d);

    widget->setLayout(layout);

    setCentralWidget(widget);

	QTOgreWindow* window3d = new QTOgreWindow();


	window3d->RenderWall(0, 0, 1, 0);
	//window3d->RenderWall(0, 0, 0, 1);
	//window3d->RenderWall(1, 0, 1, 1);

	window3d->show();
}
///////////////////////////////////////////////////////////////////////////////////////////////////

void Wires3DPlaningKit::Redo()
{
    m_controller.Redo();
}
///////////////////////////////////////////////////////////////////////////////////////////////////

void Wires3DPlaningKit::Undo()
{
    m_controller.Undo();
}
///////////////////////////////////////////////////////////////////////////////////////////////////

void Wires3DPlaningKit::InitializeUndoRedo()
{
    QAction* undo_action = new QAction(this);
    undo_action->setShortcut(QKeySequence::Undo);
    connect(undo_action, &QAction::triggered, this, &Wires3DPlaningKit::Undo);
    addAction(undo_action);

    QAction* redo_action = new QAction(this);
    redo_action->setShortcut(QKeySequence::Redo);
    connect(redo_action, &QAction::triggered, this, &Wires3DPlaningKit::Redo);
    addAction(redo_action);
}
///////////////////////////////////////////////////////////////////////////////////////////////////