#include "SecondView2D.h"

#include "Controller.h"
#include "Model.h"
#include "Wires3DPlanningKit.h"

SecondView2D::SecondView2D(Controller& controller, UndoRedoStack& commands, QWidget* parent)
    : QWidget(parent)
    , m_scene(controller, commands)
{
    m_ui.setupUi(this);

    m_ui.GraphicsView->setScene(&m_scene);
}
///////////////////////////////////////////////////////////////////////////////////////////////////

void SecondView2D::Update(ModelSocket& socket)
{
    m_scene.Update(socket);
}
///////////////////////////////////////////////////////////////////////////////////////////////////

void SecondView2D::Remove(ModelSocket& socket)
{
    m_scene.Remove(socket);
}
///////////////////////////////////////////////////////////////////////////////////////////////////