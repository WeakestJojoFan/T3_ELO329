#include "TabletView.h"
#include <QColor>
#include <QPainter>
#include <QVariantAnimation>

TabletView::TabletView(Tablet* model, ETNube* cloud ,QWidget* parent):SmartDeviceView(model, cloud, parent) {
    m_brushColor = QColor(144, 238, 144);
    m_penColor = Qt::darkGreen;
    m_sizeX = 45;
    m_sizeY = 30; //dimensiones del dibujo
    m_rectangle = true;
}