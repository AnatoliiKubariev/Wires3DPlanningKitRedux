#pragma once

#include "View2DState.h"

#include <memory>

#include <QGraphicsItem>


class AddSocket2DState: public View2DState
{
public:
    ~AddSocket2DState();
    AddSocket2DState(GraphicsScene& scene,
                   Model& model,
                   UndoRedoStack& commands);

    void MousePressEvent(const QGraphicsSceneMouseEvent* mouse_event) override;
    void MouseMoveEvent(const QGraphicsSceneMouseEvent* mouse_event) override;
    void MouseReleaseEvent(const QGraphicsSceneMouseEvent* mouse_event) override;

private:
    GraphicsScene& m_scene;
    Model& m_model;
    UndoRedoStack& m_commands;

    QRect m_socket_box;
    std::unique_ptr<QGraphicsEllipseItem> m_graphics_socket;
};
