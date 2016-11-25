#include "Controller.h"

#include "ModelSocket.h"
#include "ModelWall.h"
#include "Model.h"
#include "View2D.h"
#include "SecondView2D.h"

Controller::~Controller()
{
}

//Controller::Controller(Model& model)
//    :m_model(model)
//{
//}

Controller::Controller(Model& model, View2D& view_2d, SecondView2D& second_view_2d)
    : m_model(model)
    , m_view_2d(view_2d)
    , m_second_view_2d(second_view_2d)
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////

void Controller::AddWall(const ModelWall& model_wall)
{
    m_model.AddWall(model_wall);
}
///////////////////////////////////////////////////////////////////////////////////////////////////

void Controller::AddSocket(const ModelSocket& model_socket)
{
    m_model.AddSocket(model_socket);
}
///////////////////////////////////////////////////////////////////////////////////////////////////

void Controller::RemoveWall(const size_t wall_index)
{
    m_model.RemoveWall(wall_index);
}
///////////////////////////////////////////////////////////////////////////////////////////////////

void Controller::RemoveSocket(const size_t socket_index)
{
    m_model.RemoveSocket(socket_index);
}
///////////////////////////////////////////////////////////////////////////////////////////////////

size_t Controller::GetWallsNumber()
{
    return m_model.GetWallsNumber();
}
///////////////////////////////////////////////////////////////////////////////////////////////////

size_t Controller::GetSocketsNumber()
{
    return m_model.GetSocketsNumber();
}
///////////////////////////////////////////////////////////////////////////////////////////////////

void Controller::Update(ModelSocket& socket)
{
    m_second_view_2d.Update(socket);
    //m_view_2d.Update(socket);
}
///////////////////////////////////////////////////////////////////////////////////////////////////

void Controller::Remove(ModelSocket& socket)
{
    m_view_2d.Remove(socket);
}
///////////////////////////////////////////////////////////////////////////////////////////////////