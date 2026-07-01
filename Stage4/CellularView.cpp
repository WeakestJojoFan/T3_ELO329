#include "CellularView.h"
#include <QColor>

CellularView::CellularView(Cellular* model, ETNube* cloud, QWidget* parent): SmartDeviceView(model, cloud, parent) {
    m_brushColor = QColor(35, 145, 240);
    m_penColor = Qt::blue;
    m_rectangle = true;
}