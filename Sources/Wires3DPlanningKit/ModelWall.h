#pragma once

#include <QPoint>
#include <QLine>

struct ModelWall
{
    ModelWall();

	ModelWall(const QPoint& start, const QPoint& end, 
			  const int hight = 1, const int width = 1);
    ModelWall(const QLineF& line,
              const int hight = 1, const int width = 1);

	QPoint m_start;
	QPoint m_end;
	int m_hight;
	int m_width;
};

bool operator==(const ModelWall& lhr, const ModelWall& rhs);