#include "AddWallCommand.h"
#include "Controller.h"
#include "GraphicsScene.h"

#include <utility>

#include <QGraphicsItem>

AddWallCommand::~AddWallCommand()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////

AddWallCommand::AddWallCommand(Controller& controller, const ModelWall& wall)
    : m_controller(controller)
    , m_wall(wall)
{
    m_controller.AddWall(m_wall);
    m_wall_index = m_controller.GetWallsNumber() - 1;
}
///////////////////////////////////////////////////////////////////////////////////////////////////

void AddWallCommand::Redo()
{
    m_controller.AddWall(m_wall);
}
///////////////////////////////////////////////////////////////////////////////////////////////////

void AddWallCommand::Undo()
{
    
}
///////////////////////////////////////////////////////////////////////////////////////////////////