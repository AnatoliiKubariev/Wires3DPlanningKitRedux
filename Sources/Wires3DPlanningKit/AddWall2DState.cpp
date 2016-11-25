#include "AddWall2DState.h"

#include "Controller.h"
#include "QGraphicsItemWall.h"
#include "GraphicsScene.h"
#include "AddWallCommand.h"
#include "UndoRedoStack.h"

AddWall2DState::~AddWall2DState()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////

AddWall2DState::AddWall2DState(Controller& controller, UndoRedoStack& commands, GraphicsScene& scene)
    : m_controller(controller)
    , m_commands(commands)
    , m_scene(scene)
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////

void AddWall2DState::MousePressEvent(const QGraphicsSceneMouseEvent* mouse_event)
{
//    m_start = mouse_event->scenePos().toPoint();
//
//    m_graphics_line = std::make_unique<QGraphicsLineItem>(m_start.x(), m_start.y(), m_start.x(), m_start.y());
//
//    m_scene.addItem(m_graphics_line.get());
}
///////////////////////////////////////////////////////////////////////////////////////////////////

void AddWall2DState::MouseMoveEvent(const QGraphicsSceneMouseEvent* mouse_event)
{
    //if(!m_graphics_line)
    //{
    //    return;
    //}
    //m_end = mouse_event->scenePos().toPoint();
    //m_graphics_line->setLine(m_start.x(), m_start.y(), m_end.x(), m_end.y());
}
///////////////////////////////////////////////////////////////////////////////////////////////////

void AddWall2DState::MouseReleaseEvent(const QGraphicsSceneMouseEvent* mouse_event)
{
    //if(!m_graphics_line)
    //{
    //    return;
    //}
    //auto temp_line_command = std::make_unique<AddWallCommand>(m_controller, m_graphics_line.release());
    //m_commands.Register(std::move(temp_line_command));

    //m_start = QPoint();
    //m_end = QPoint();
}
///////////////////////////////////////////////////////////////////////////////////////////////////