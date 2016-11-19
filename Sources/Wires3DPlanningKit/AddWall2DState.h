#pragma once

#include "View2DState.h"

#include <memory>

#include <QGraphicsItem>
#include <QPoint>

class AddWall2DState: public View2DState
{
public:
    ~AddWall2DState();
    AddWall2DState(GraphicsScene& scene,
                   Model& model,
                   UndoRedoStack& commands);

    void MousePressEvent(const QGraphicsSceneMouseEvent* mouse_event) override;
    void MouseMoveEvent(const QGraphicsSceneMouseEvent* mouse_event) override;
    void MouseReleaseEvent(const QGraphicsSceneMouseEvent* mouse_event) override;

private:
    GraphicsScene& m_scene;
    Model& m_model;
    UndoRedoStack& m_commands;

    QPoint m_start;
    QPoint m_end;
    std::unique_ptr<QGraphicsLineItem> m_graphics_line;
};