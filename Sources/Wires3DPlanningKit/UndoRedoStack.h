#pragma once

#include <vector>
#include <memory>

#include "GraphicsCommand.h"

class UndoRedoStack
{
public:
    void Register(std::unique_ptr<GraphicsCommand> command);
    void Redo();
    void Undo();

    void Clear();

private:
    std::vector<std::unique_ptr<GraphicsCommand>> m_commands;
    int m_top = 0;
};