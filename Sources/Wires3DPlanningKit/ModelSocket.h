#pragma once

#include <QRect>

struct ModelSocket
{
    ModelSocket();
    ModelSocket(const QRect& socket_box, const int hight = 1);

    QRect m_socket_box;
    int m_hight;
};