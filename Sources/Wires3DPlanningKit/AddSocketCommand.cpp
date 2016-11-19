#include "AddSocketCommand.h"
#include "GraphicsScene.h"
#include "Model.h"

#include <utility>

#include <QGraphicsItem>

AddSocketCommand::~AddSocketCommand()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////

AddSocketCommand::AddSocketCommand(GraphicsScene& scene,
                                   Model& model,
                                   QGraphicsEllipseItem* graphics_socket)
    : m_scene(scene)
    , m_model(model)
    , m_box(graphics_socket->rect().toRect())
    , m_graphics_socket(graphics_socket)
{
    m_model.AddSocket(ModelSocket(m_box));
    m_socket_index = model.GetSocketsNumber() - 1;
}
///////////////////////////////////////////////////////////////////////////////////////////////////

void AddSocketCommand::Redo()
{
    if(m_graphics_socket)
    {
        return;
    }
    m_graphics_socket = new QGraphicsEllipseItem(m_box);
    m_scene.addItem(m_graphics_socket);
    m_model.AddSocket(ModelSocket(m_box));
}
///////////////////////////////////////////////////////////////////////////////////////////////////

void AddSocketCommand::Undo()
{
    m_model.RemoveSocket(m_socket_index);
    m_scene.removeItem(m_graphics_socket); // removeItem dont delete data - the ownership of item is passed on to the caller 
    std::unique_ptr<QGraphicsEllipseItem> to_del(m_graphics_socket);
    m_graphics_socket = nullptr;
}
///////////////////////////////////////////////////////////////////////////////////////////////////