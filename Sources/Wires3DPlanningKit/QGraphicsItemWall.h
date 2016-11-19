#pragma once

#include <QGraphicsItem>

struct ModelWall;

struct QGraphicsItemWall: public QGraphicsLineItem
{
	~QGraphicsItemWall();
	QGraphicsItemWall(ModelWall& model_wall, QGraphicsItem* parent = 0);
	QGraphicsItemWall(ModelWall& model_wall, const QPoint& start, const QPoint& end, QGraphicsItem* parent = 0);

	ModelWall& m_model_wall;
};
