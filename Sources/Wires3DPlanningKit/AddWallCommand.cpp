#include "AddWallCommand.h"
#include "GraphicsScene.h"
#include "Model.h"

#include <utility>

#include <QGraphicsItem>

AddWallCommand::~AddWallCommand()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////

AddWallCommand::AddWallCommand(GraphicsScene& scene,
                               Model& model,
                               QGraphicsLineItem* graphics_line)
    : m_scene(scene)
    , m_model(model)
    , m_line(graphics_line->line().toLine())
    , m_graphics_line(graphics_line)
{
    m_model.AddWall(ModelWall(m_line.p1(), m_line.p2()));
    m_wall_index = model.GetWallsNumber() - 1;
}
///////////////////////////////////////////////////////////////////////////////////////////////////

void AddWallCommand::Redo()
{
    if(m_graphics_line)
    {
        return;
    }
    m_graphics_line = new QGraphicsLineItem(m_line);
    m_scene.addItem(m_graphics_line);
    m_model.AddWall(ModelWall(m_line.p1(), m_line.p2()));
}
///////////////////////////////////////////////////////////////////////////////////////////////////

void AddWallCommand::Undo()
{
    m_model.RemoveWall(m_wall_index);
    m_scene.removeItem(m_graphics_line); // removeItem dont delete data - the ownership of item is passed on to the caller 
    std::unique_ptr<QGraphicsLineItem> to_del(m_graphics_line);
    m_graphics_line = nullptr;
}
///////////////////////////////////////////////////////////////////////////////////////////////////