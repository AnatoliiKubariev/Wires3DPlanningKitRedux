#include "GraphicsScene.h"

#include "ModelWall.h"
#include "QGraphicsItemWall.h"
#include "UndoRedoStack.h"
#include "AddSocket2DState.h"
#include "AddWall2DState.h"

#include <QPainter>

QPoint start;

GraphicsScene::GraphicsScene(Model& model, UndoRedoStack& commands, QObject* parent)
	: QGraphicsScene(parent)
	//, m_state(std::make_unique<AddWall2DState>(*this, model, commands))
    , m_state(std::make_unique<AddSocket2DState>(*this, model, commands))
    , m_commands(commands)
{

	//m_state = std::move(std::make_unique<AddWall2DState>());
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

void GraphicsScene::Redo()
{
    m_commands.Redo();
}
///////////////////////////////////////////////////////////////////////////////////////////////////

void GraphicsScene::Undo()
{
    m_commands.Undo();
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