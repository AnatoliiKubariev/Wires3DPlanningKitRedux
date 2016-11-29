#pragma once

#include "View2DState.h"

#include <memory>

#include <QGraphicsItem>

class Controller;
struct QGraphicsItemSocket;

class AddSocket2DState: public View2DState
{
public:
    ~AddSocket2DState();
    AddSocket2DState(Controller& controller, GraphicsScene& scene);

    void MousePressEvent(const QGraphicsSceneMouseEvent* mouse_event) override;
    void MouseMoveEvent(const QGraphicsSceneMouseEvent* mouse_event) override;
    void MouseReleaseEvent(const QGraphicsSceneMouseEvent* mouse_event) override;

private:
    Controller& m_controller;
    GraphicsScene& m_scene;

    std::unique_ptr<QGraphicsItemSocket> m_graphics_socket;
};
