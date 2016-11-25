#pragma once

class Model;
struct ModelSocket;
struct ModelWall;
class View2D;
class SecondView2D;

class Controller
{
public:
    ~Controller();

    //Controller(Model& model);

    // temp constructor
    Controller(Model& model, View2D& view_2d, SecondView2D& second_view_2d);

    //void LoadViews();

    void AddWall(const ModelWall& model_wall);
    void AddSocket(const ModelSocket& model_socket);

    void RemoveWall(const size_t wall_index);
    void RemoveSocket(const size_t socket_index);

    size_t GetWallsNumber();
    size_t GetSocketsNumber();

    void Update(ModelSocket& socket);
    void Remove(ModelSocket& socket);

private:
    Model& m_model;
    View2D& m_view_2d;
    SecondView2D& m_second_view_2d;
};