#include "QGraphicsItemSocket.h"

#include "ModelSocket.h"

const int hight = 10;
const int width = 10;

QGraphicsItemSocket::~QGraphicsItemSocket()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////

QGraphicsItemSocket::QGraphicsItemSocket(const ModelSocket& model_socket, QGraphicsItem* parent)
    : QGraphicsEllipseItem(model_socket.m_coordinates.x() - hight / 2,
                           model_socket.m_coordinates.y() - width / 2,
                           width, hight, parent)
    , m_id(model_socket.m_id)
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////