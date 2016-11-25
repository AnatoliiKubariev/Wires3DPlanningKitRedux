#include "QGraphicsItemWall.h"

#include "ModelWall.h"

QGraphicsItemWall::~QGraphicsItemWall()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////

QGraphicsItemWall::QGraphicsItemWall(ModelWall& model_wall, QGraphicsItem* parent)
	: QGraphicsLineItem(model_wall.m_start.x(), model_wall.m_start.y(), 
						model_wall.m_end.x(), model_wall.m_end.y(), parent)
	, m_model_wall(model_wall)
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////

QGraphicsItemWall::QGraphicsItemWall(ModelWall& model_wall, const QPoint& start, const QPoint& end, QGraphicsItem* parent)
	: QGraphicsLineItem(QLine(start, end), parent)
	, m_model_wall(model_wall)
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////