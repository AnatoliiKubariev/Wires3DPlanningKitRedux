#pragma once

#include <QGraphicsSceneMouseEvent>

class GraphicsScene;
class Model;
class UndoRedoStack;

class View2DState
{
public:
    virtual ~View2DState() = 0;

    virtual void MousePressEvent(const QGraphicsSceneMouseEvent* mouseEvent);
    virtual void MouseMoveEvent(const QGraphicsSceneMouseEvent* mouse_event);
    virtual void MouseReleaseEvent(const QGraphicsSceneMouseEvent* mouseEvent);
};