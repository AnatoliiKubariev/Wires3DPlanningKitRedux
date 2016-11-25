#pragma once

#include <QGraphicsItem>

struct ModelSocket;

struct QGraphicsItemSocket: public QGraphicsEllipseItem
{
	~QGraphicsItemSocket();
    QGraphicsItemSocket(const QPoint& coordinates, ModelSocket& model_socket, QGraphicsItem* parent = 0);

    ModelSocket& m_model_socket;
};
