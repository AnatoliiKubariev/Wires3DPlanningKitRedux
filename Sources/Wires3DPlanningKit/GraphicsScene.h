#pragma once

#include "View2DState.h"
#include "QGraphicsItemWall.h"
#include "QGraphicsItemSocket.h"

#include <vector>
#include <memory>

#include <QGraphicsScene>
#include <QGraphicsItem>

class Controller;
class Model;
struct ModelSocket;
class UndoRedoStack;

class GraphicsScene: public QGraphicsScene
{
	Q_OBJECT

public:
	GraphicsScene(Controller& controller, UndoRedoStack& commands, QObject* parent = 0);

    void AddSocket(std::unique_ptr<QGraphicsItemSocket> socket);

    void Update(ModelSocket& socket);
    void Update(ModelWall& wall);

    void Remove(ModelWall& wall);
    void Remove(ModelSocket& socket);

protected:
	void mousePressEvent(QGraphicsSceneMouseEvent* mouseEvent) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent* mouseEvent) override;
	void mouseReleaseEvent(QGraphicsSceneMouseEvent* mouseEvent) override;

private:
	void _DrawGrid();

	std::unique_ptr<View2DState> m_state;
	std::vector<std::unique_ptr<QGraphicsItemWall>> m_walls;
    std::vector<std::unique_ptr<QGraphicsItemSocket>> m_sockets;
};