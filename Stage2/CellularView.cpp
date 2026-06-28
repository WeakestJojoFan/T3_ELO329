#include "CellularView.h"
#include <QPainter>
#include <cmath>

CellularView::CellularView(Cellular* model, QWidget* parent): QWidget(parent), m_model(model) {
    setFixedSize(100, 100); //tamaño de los bordes
    m_sizeX = 15;
    m_sizeY = 30; //dimensiones del dibujo

    updatePosition();
}

void CellularView::updatePosition() {
    if (m_model) {
        move(static_cast<int>(std::round(m_model->getX())) - m_sizeX/2 , static_cast<int>(std::round(m_model->getY())) - m_sizeY/2); //centramos el dibujo respecto a la posicion de cellular
    }
}

void CellularView::paintEvent(QPaintEvent*){ //dibujamos el cellular
    QPainter painter(this);

    painter.setRenderHint(QPainter::Antialiasing);

    int grosorBorde = 2;

    painter.setBrush(QColor(35, 145, 240));
    painter.setPen(QPen(Qt::blue, grosorBorde));

    painter.drawRoundedRect(grosorBorde/2,grosorBorde/2, m_sizeX, m_sizeY, 5, 5);

    painter.setPen(Qt::black);
    painter.drawText(QRect(0,m_sizeY, 100, 20), Qt::AlignLeft, m_model->getName());
}
