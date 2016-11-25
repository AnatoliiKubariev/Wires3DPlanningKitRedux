#pragma once

#include "GraphicsCommand.h"
#include "ModelSocket.h"

class Controller;

class AddSocketCommand: public GraphicsCommand
{
public:
    ~AddSocketCommand();
    AddSocketCommand(Controller& controller, const ModelSocket& socket);

    void Redo() override;
    void Undo() override;

private:
    Controller& m_controller;
    ModelSocket m_socket;
    size_t m_socket_index;
};