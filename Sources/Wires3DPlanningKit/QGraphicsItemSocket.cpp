#include "QGraphicsItemSocket.h"

#include "ModelSocket.h"

const int hight = 10;
const int width = 10;

QGraphicsItemSocket::~QGraphicsItemSocket()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////

QGraphicsItemSocket::QGraphicsItemSocket(const QPoint& socket_box, ModelSocket& model_socket, QGraphicsItem* parent)
    : QGraphicsEllipseItem(socket_box, parent)
    , m_model_socket(model_socket)
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////