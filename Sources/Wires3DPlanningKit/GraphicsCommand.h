#pragma once

class GraphicsScene;
class Model;

class GraphicsCommand
{
public:
    virtual ~GraphicsCommand() = 0;

    virtual void Redo() = 0;
    virtual void Undo() = 0;
};