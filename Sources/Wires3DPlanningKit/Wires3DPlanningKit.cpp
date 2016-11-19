#include "Wires3DPlanningKit.h"

Wires3DPlaningKit::Wires3DPlaningKit(QWidget *parent)
	: QMainWindow(parent)
	, m_model()
	, m_view_2d(m_model, m_commands)
{
	m_ui.setupUi(this);

	setCentralWidget(&m_view_2d);
}
///////////////////////////////////////////////////////////////////////////////////////////////////

