#include "GraphicsScene.h"

#include "AddSocket2DState.h"
#include "AddWall2DState.h"
#include "Controller.h"
#include "ModelSocket.h"
#include "ModelWall.h"
#include "QGraphicsItemWall.h"
#include "UndoRedoStack.h"

#include <QPainter>

GraphicsScene::GraphicsScene(Controller& controller, UndoRedoStack& commands, QObject* parent)
    : QGraphicsScene(parent)
    //, m_state(std::make_unique<AddWall2DState>(*this, model, commands))
    , m_state(std::make_unique<AddSocket2DState>(controller, commands, *this))
{

    //m_state = std::move(std::make_unique<AddWall2DState>());
}
///////////////////////////////////////////////////////////////////////////////////////////////////

void GraphicsScene::AddSocket(std::unique_ptr<QGraphicsItemSocket> socket)
{
    m_sockets.push_back(std::move(socket));
}
///////////////////////////////////////////////////////////////////////////////////////////////////

void GraphicsScene::Update(ModelSocket& socket)
{
    auto graphics_socket = std::make_unique<QGraphicsItemSocket>(socket);

    addItem(graphics_socket.get());

    m_sockets.push_back(std::move(graphics_socket));
}
///////////////////////////////////////////////////////////////////////////////////////////////////


void GraphicsScene::Update(ModelWall& wall)
{

}
///////////////////////////////////////////////////////////////////////////////////////////////////

void GraphicsScene::Remove(ModelSocket& socket)
{
    auto it = std::find_if(m_sockets.begin(), m_sockets.end(),
                           [&socket](const std::unique_ptr<QGraphicsItemSocket>& s)
    {
        return &s.get()->m_model_socket == &socket;
    });

    m_sockets.erase(it);
}
///////////////////////////////////////////////////////////////////////////////////////////////////

void GraphicsScene::Remove(ModelWall& wall)
{

}
///////////////////////////////////////////////////////////////////////////////////////////////////

void GraphicsScene::mousePressEvent(QGraphicsSceneMouseEvent* mouseEvent)
{
    m_state->MousePressEvent(mouseEvent);
}
///////////////////////////////////////////////////////////////////////////////////////////////////

void GraphicsScene::mouseMoveEvent(QGraphicsSceneMouseEvent* mouseEvent)
{
    m_state->MouseMoveEvent(mouseEvent);
}
///////////////////////////////////////////////////////////////////////////////////////////////////

void GraphicsScene::mouseReleaseEvent(QGraphicsSceneMouseEvent* mouseEvent)
{
    m_state->MouseReleaseEvent(mouseEvent);
}
///////////////////////////////////////////////////////////////////////////////////////////////////












// Method from old version
void GraphicsScene::_DrawGrid()
{
    const qreal m_grid_size = 25;
    QPixmap pix_map(m_grid_size, m_grid_size);
    pix_map.fill(Qt::white);
    QPainter painter;
    painter.begin(&pix_map);
    painter.setPen({211, 211, 211, 150});
    painter.drawLine(0, 0, m_grid_size, 0);
    painter.drawLine(0, 0, 0, m_grid_size);
    painter.end();
    QBrush brush(pix_map);
    setBackgroundBrush(brush);
}