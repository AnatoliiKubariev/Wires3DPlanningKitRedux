#include "View2D.h"

#include "Model.h"

View2D::View2D(Model& model, UndoRedoStack& commands, QWidget* parent)
	: QWidget(parent)
	, m_scene(model, commands)
{
	m_ui.setupUi(this);

	m_ui.GraphicsView->setScene(&m_scene);

    InitializeUndoRedo();
}
///////////////////////////////////////////////////////////////////////////////////////////////////

void View2D::InitializeUndoRedo()
{
    QAction* undo_action = new QAction(this);
    undo_action->setShortcut(QKeySequence::Undo);
    connect(undo_action, &QAction::triggered, &m_scene, &GraphicsScene::Undo);
    addAction(undo_action);
    QAction* redo_action = new QAction(this);
    redo_action->setShortcut(QKeySequence::Redo);
    connect(redo_action, &QAction::triggered, &m_scene, &GraphicsScene::Redo);
    addAction(redo_action);
}
///////////////////////////////////////////////////////////////////////////////////////////////////