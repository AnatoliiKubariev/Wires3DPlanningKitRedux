#pragma once

#include <QPoint>

struct ModelSocket
{
    //ModelSocket();
    ModelSocket(const QPoint& coordinates, const int hight = 1);

    QPoint m_coordinates;
    int m_hight;
};