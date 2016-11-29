#pragma once

#include <QGraphicsItem>

struct ModelSocket;

struct QGraphicsItemSocket: public QGraphicsEllipseItem
{
	~QGraphicsItemSocket();
    QGraphicsItemSocket(const ModelSocket& model_socket, QGraphicsItem* parent = 0);

    const int m_id;
};
