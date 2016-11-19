#include "ModelWall.h"

ModelWall::ModelWall()
{
}

ModelWall::ModelWall(const QPoint& start, const QPoint& end,
                     const int hight, const int width)
    : m_start(start)
    , m_end(end)
    , m_hight(hight)
    , m_width(width)
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////

ModelWall::ModelWall(const QLineF& line,
                     const int hight, const int width)
    : m_start(line.p1().toPoint())
    , m_end(line.p2().toPoint())
    , m_hight(hight)
    , m_width(width)
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////

bool operator==(const ModelWall& lhs, const ModelWall& rhs)
{
    if(lhs.m_start != rhs.m_start)
        return false;
    if(lhs.m_end != rhs.m_end)
        return false;
    if(lhs.m_hight != rhs.m_hight)
        return false;
    if(lhs.m_width != rhs.m_hight)
        return false;
    return true;

    //return &lhs == &rhs;
}
///////////////////////////////////////////////////////////////////////////////////////////////////