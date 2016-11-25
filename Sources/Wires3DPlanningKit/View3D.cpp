#include "View3D.h"

#include "Controller.h"

View3D::View3D(Controller& controller, QWidget* parent)
	: QWidget(parent)
	, m_controller(controller)
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////