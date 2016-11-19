#pragma once

#include "GraphicsCommand.h"
#include "ModelWall.h"

#include <QRect>

class QGraphicsEllipseItem;

class AddSocketCommand: public GraphicsCommand
{
public:
    ~AddSocketCommand();
    AddSocketCommand(GraphicsScene& scene,
                     Model& model,
                     QGraphicsEllipseItem* graphics_socket);

    void Redo() override;
    void Undo() override;

private:
    GraphicsScene& m_scene;
    Model& m_model;
    QRect m_box;
    size_t m_socket_index;

    QGraphicsEllipseItem* m_graphics_socket;
};