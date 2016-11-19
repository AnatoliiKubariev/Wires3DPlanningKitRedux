#pragma once

#include "View2DState.h"

#include <vector>
#include <memory>

#include <QGraphicsScene>
#include <QGraphicsItem>

class Model;
class UndoRedoStack;

class GraphicsScene: public QGraphicsScene
{
	Q_OBJECT

public:
	GraphicsScene(Model& model, UndoRedoStack& commands, QObject* parent = 0);

    void Redo();
    void Undo();

protected:
	void mousePressEvent(QGraphicsSceneMouseEvent* mouseEvent) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent* mouseEvent) override;
	void mouseReleaseEvent(QGraphicsSceneMouseEvent* mouseEvent) override;

private:
	void _DrawGrid();

	std::unique_ptr<View2DState> m_state;
    UndoRedoStack& m_commands;
	std::vector<std::unique_ptr<QGraphicsItem>> m_walls;
};