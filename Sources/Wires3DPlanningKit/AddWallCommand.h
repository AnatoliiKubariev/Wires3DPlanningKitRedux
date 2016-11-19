#pragma once

#include "GraphicsCommand.h"
#include "ModelWall.h"

class QGraphicsLineItem;

class AddWallCommand: public GraphicsCommand
{
public:
    ~AddWallCommand();
    AddWallCommand(GraphicsScene& scene,
                   Model& model,
                   QGraphicsLineItem* graphics_line);

    void Redo() override;
    void Undo() override;

private:
    GraphicsScene& m_scene;
    Model& m_model;
    QLine m_line;
    size_t m_wall_index;

    QGraphicsLineItem* m_graphics_line;
};