#include "AddSocketCommand.h"
#include "Controller.h"
#include "GraphicsScene.h"

#include <utility>

#include <QGraphicsItem>

AddSocketCommand::~AddSocketCommand()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////

AddSocketCommand::AddSocketCommand(Controller& controller, const ModelSocket& socket)
    : m_controller(controller)
    , m_socket(socket)
{
    controller.AddSocket(m_socket);
    m_socket_index = controller.GetSocketsNumber() - 1;
}
///////////////////////////////////////////////////////////////////////////////////////////////////

void AddSocketCommand::Redo()
{
    m_controller.AddSocket(m_socket);
}
///////////////////////////////////////////////////////////////////////////////////////////////////

void AddSocketCommand::Undo()
{
    m_controller.RemoveSocket(m_socket_index);
}
///////////////////////////////////////////////////////////////////////////////////////////////////