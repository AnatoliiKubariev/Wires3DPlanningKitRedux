#include "AddSocket2DState.h"

#include "AddSocketCommand.h"
#include "Controller.h"
#include "GraphicsScene.h"
#include "UndoRedoStack.h"
#include "QGraphicsItemSocket.h"

AddSocket2DState::~AddSocket2DState()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////

AddSocket2DState::AddSocket2DState(Controller& controller, UndoRedoStack& commands, GraphicsScene& scene)
    : m_controller(controller)
    , m_commands(commands)
    , m_scene(scene)
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////

void AddSocket2DState::MousePressEvent(const QGraphicsSceneMouseEvent* mouse_event)
{
    const QPoint coord = mouse_event->scenePos().toPoint();

    QRect socket_box(coord.x() - hight / 2, coord.y() - width / 2, hight, width);
    ModelSocket model_socket(coord);
    m_graphics_socket = std::make_unique<QGraphicsItemSocket>(socket_box, model_socket);

    m_scene.addItem(m_graphics_socket.get());
}
///////////////////////////////////////////////////////////////////////////////////////////////////

void AddSocket2DState::MouseMoveEvent(const QGraphicsSceneMouseEvent* mouse_event)
{
    if(!m_graphics_socket)
    {
        return;
    }
    const QPointF coord = mouse_event->scenePos().toPoint();
    m_graphics_socket->setPos({coord.x() - hight / 2, coord.y() - width / 2});
    m_graphics_socket->m_model_socket.m_coordinates = coord.toPoint();
}
///////////////////////////////////////////////////////////////////////////////////////////////////

void AddSocket2DState::MouseReleaseEvent(const QGraphicsSceneMouseEvent* mouse_event)
{
    if(!m_graphics_socket)
    {
        return;
    }
    const QPoint coord = mouse_event->scenePos().toPoint();
    auto temp_socket_command = std::make_unique<AddSocketCommand>(m_controller, m_graphics_socket->m_model_socket);

    m_commands.Register(std::move(temp_socket_command));
    m_scene.AddSocket(std::move(m_graphics_socket));
}
///////////////////////////////////////////////////////////////////////////////////////////////////