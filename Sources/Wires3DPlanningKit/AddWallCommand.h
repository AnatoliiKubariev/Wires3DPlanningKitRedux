#pragma once

#include "GraphicsCommand.h"
#include "ModelWall.h"

class Controller;

class AddWallCommand: public GraphicsCommand
{
public:
    ~AddWallCommand();
    AddWallCommand(Controller& controller, const ModelWall& wall);

    void Redo() override;
    void Undo() override;

private:
    Controller& m_controller;
    ModelWall m_wall;
    size_t m_wall_index;
};