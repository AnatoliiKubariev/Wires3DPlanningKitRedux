#pragma once

#include <QPoint>

struct ModelSocket
{
    //ModelSocket();
    ModelSocket(const int id, const QPoint& coordinates, const int hight = 1);

    int m_id;

    QPoint m_coordinates;
    int m_hight;
};