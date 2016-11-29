#pragma once

#include "ModelWall.h"
#include "ModelSocket.h"

#include <vector>

class Model
{
public:
	void AddWall(const ModelWall& model_wall);
    void AddSocket(const ModelSocket& model_socket);

    void RemoveWall(const size_t wall_index);
    void RemoveSocket(const size_t socket_index);

    size_t GetWallsNumber();
    size_t GetSocketsNumber();

	std::vector<ModelWall> m_walls;
    std::vector<ModelSocket> m_sockets;
};