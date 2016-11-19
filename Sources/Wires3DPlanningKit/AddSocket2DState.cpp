#include "AddSocket2DState.h"

#include "Model.h"
#include "GraphicsScene.h"
#include "AddSocketCommand.h"
#include "UndoRedoStack.h"

const int hight = 10;
const int width = 10;

AddSocket2DState::~AddSocket2DState()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////

AddSocket2DState::AddSocket2DState(GraphicsScene& scene,
                                   Model& model,
                                   UndoRedoStack& commands)
    : m_scene(scene)
    , m_model(model)
    , m_commands(commands)
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////

void AddSocket2DState::MousePressEvent(const QGraphicsSceneMouseEvent* mouse_event)
{
    const QPoint coord = mouse_event->scenePos().toPoint();
    m_socket_box = QRect(coord.x() - hight / 2, coord.y() - width / 2, hight, width);
    m_graphics_socket = std::make_unique<QGraphicsEllipseItem>(m_socket_box);

    m_scene.addItem(m_graphics_socket.get());
}
///////////////////////////////////////////////////////////////////////////////////////////////////

void AddSocket2DState::MouseMoveEvent(const QGraphicsSceneMouseEvent* mouse_event)
{
    if(!m_graphics_socket)
    {
        return;
    }
    const QPoint coord = mouse_event->scenePos().toPoint();
    m_socket_box.setTopLeft({coord.x() - hight / 2, coord.y() - width / 2});
}
///////////////////////////////////////////////////////////////////////////////////////////////////

void AddSocket2DState::MouseReleaseEvent(const QGraphicsSceneMouseEvent* mouse_event)
{
    if(!m_graphics_socket)
    {
        return;
    }
    auto temp_socket_command = std::make_unique<AddSocketCommand>(m_scene, m_model, m_graphics_socket.release());
    m_commands.Register(std::move(temp_socket_command));

    m_socket_box = QRect();
}
///////////////////////////////////////////////////////////////////////////////////////////////////