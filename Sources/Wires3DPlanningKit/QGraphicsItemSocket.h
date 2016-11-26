#pragma once

#include <QGraphicsItem>

struct ModelSocket;

struct QGraphicsItemSocket: public QGraphicsEllipseItem
{
	~QGraphicsItemSocket();
    QGraphicsItemSocket(ModelSocket& model_socket, QGraphicsItem* parent = 0);

    ModelSocket& m_model_socket;
};
