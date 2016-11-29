#include "AddSocket2DState.h"

#include "AddSocketCommand.h"
#include "Controller.h"
#include "GraphicsScene.h"
#include "UndoRedoStack.h"
#include "Utility.h"
#include "QGraphicsItemSocket.h"

const int hight = 10;
const int width = 10;

AddSocket2DState::~AddSocket2DState()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////

AddSocket2DState::AddSocket2DState(Controller& controller, GraphicsScene& scene)
    : m_controller(controller)
    , m_scene(scene)
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////

void AddSocket2DState::MousePressEvent(const QGraphicsSceneMouseEvent* mouse_event)
{
    const QPoint coord = mouse_event->scenePos().toPoint();

    ModelSocket model_socket(GetId(), coord);
    //m_graphics_socket = std::make_unique<QGraphicsItemSocket>(model_socket);

    //m_scene.addItem(m_graphics_socket.get());
    //m_scene.AddSocket(std::move(m_graphics_socket));

    m_controller.AddSocket(model_socket);
}
///////////////////////////////////////////////////////////////////////////////////////////////////

void AddSocket2DState::MouseMoveEvent(const QGraphicsSceneMouseEvent* mouse_event)
{
    //if(!m_graphics_socket)
    //{
    //    return;
    //}
    //const QPointF coord = mouse_event->scenePos().toPoint();
    //m_graphics_socket->setPos({coord.x() - hight / 2, coord.y() - width / 2});
    //m_graphics_socket->m_model_socket.m_coordinates = coord.toPoint();
}
///////////////////////////////////////////////////////////////////////////////////////////////////

void AddSocket2DState::MouseReleaseEvent(const QGraphicsSceneMouseEvent* mouse_event)
{
    //if(!m_graphics_socket)
    //{
    //    return;
    //}
    //const QPointF coord = mouse_event->scenePos().toPoint();
    //m_graphics_socket->setPos({coord.x() - hight / 2, coord.y() - width / 2});
    //m_graphics_socket->m_model_socket.m_coordinates = coord.toPoint();
}
///////////////////////////////////////////////////////////////////////////////////////////////////