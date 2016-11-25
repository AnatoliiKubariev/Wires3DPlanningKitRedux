#include "Wires3DPlanningKit.h"

#include <QLayout>

Wires3DPlaningKit::Wires3DPlaningKit(QWidget *parent)
	: QMainWindow(parent)
	, m_model()
    , m_controller(m_model, m_view_2d, m_second_view_2d)
    , m_commands()
    , m_view_2d(m_controller, m_commands)
    , m_second_view_2d(m_controller, m_commands)
{
	m_ui.setupUi(this);

    QWidget* widget = new QWidget(this);
    QVBoxLayout *layout = new QVBoxLayout(widget);

    layout->addWidget(&m_view_2d);
    layout->addWidget(&m_second_view_2d);

    widget->setLayout(layout);

    setCentralWidget(widget);
}
///////////////////////////////////////////////////////////////////////////////////////////////////

void Wires3DPlaningKit::Update(const ModelSocket& socket)
{

}
///////////////////////////////////////////////////////////////////////////////////////////////////

void Wires3DPlaningKit::Remove(const ModelSocket& socket)
{

}
///////////////////////////////////////////////////////////////////////////////////////////////////

void Wires3DPlaningKit::InitializeUndoRedo()
{
    //QAction* undo_action = new QAction(this);
    //undo_action->setShortcut(QKeySequence::Undo);
    //connect(undo_action, &QAction::triggered, &m_scene, &GraphicsScene::Undo);
    //addAction(undo_action);
    //QAction* redo_action = new QAction(this);
    //redo_action->setShortcut(QKeySequence::Redo);
    //connect(redo_action, &QAction::triggered, &m_scene, &GraphicsScene::Redo);
    //addAction(redo_action);
}
///////////////////////////////////////////////////////////////////////////////////////////////////