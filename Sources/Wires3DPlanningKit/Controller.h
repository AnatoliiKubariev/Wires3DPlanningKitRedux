#pragma once

#include "UndoRedoStack.h"
#include "View2D.h"

#include <vector>

class Model;
struct ModelSocket;
struct ModelWall;

class Controller
{
public:
    ~Controller();

    //Controller(Model& model);

    // temp constructor
    Controller(Model& model);

    //void LoadViews();
    void AddView(View2D* view_2d);

    void Undo();
    void Redo();

    void AddWall(const ModelWall& model_wall);
    void AddSocket(const ModelSocket& model_socket);

    size_t GetWallsNumber();
    size_t GetSocketsNumber();

    void Update(const ModelSocket& model_socket);
    void Remove(const int id);

private:
    Model& m_model;
    UndoRedoStack m_commands;

    std::vector<View2D*> m_views_2d;
};