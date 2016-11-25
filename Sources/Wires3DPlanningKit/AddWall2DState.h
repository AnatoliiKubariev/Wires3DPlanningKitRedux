#pragma once

#include "View2DState.h"

#include <memory>

#include <QGraphicsItem>
#include <QPoint>

class Controller;

class AddWall2DState: public View2DState
{
public:
    ~AddWall2DState();
    AddWall2DState(Controller& controller, UndoRedoStack& commands, GraphicsScene& scene);

    void MousePressEvent(const QGraphicsSceneMouseEvent* mouse_event) override;
    void MouseMoveEvent(const QGraphicsSceneMouseEvent* mouse_event) override;
    void MouseReleaseEvent(const QGraphicsSceneMouseEvent* mouse_event) override;

private:
    Controller& m_controller;
    UndoRedoStack& m_commands;
    GraphicsScene& m_scene;

    QPoint m_start;
    QPoint m_end;
    std::unique_ptr<QGraphicsLineItem> m_graphics_line;
};