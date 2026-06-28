#include "EloTelTagView.h"
#include <QPainter>
#include <cmath>

EloTelTagView::EloTelTagView(EloTelTag* model, QWidget* parent): QWidget(parent), m_model(model) {
    setFixedSize(100, 100); //tamaño de los bordes
    m_sizeX = 15;
    m_sizeY = 15; //dimensiones del dibujo

    updatePosition();
}

void EloTelTagView::updatePosition() {
    if (m_model) {
        move(static_cast<int>(std::round(m_model->getX())) - m_sizeX/2 , static_cast<int>(std::round(m_model->getY())) - m_sizeY/2); //centramos el dibujo respecto a la posicion de EloTelTag
    }
}

void EloTelTagView::paintEvent(QPaintEvent*){ //dibujamos el EloTelTag
    QPainter painter(this);

    painter.setRenderHint(QPainter::Antialiasing);

    int grosorBorde = 2;

    painter.setBrush(Qt::red);
    painter.setPen(QPen(Qt::darkRed, grosorBorde));

    painter.drawEllipse(QPointF((m_sizeX + grosorBorde)/2 ,(m_sizeY + grosorBorde)/2), m_sizeX/2, m_sizeY/2);

    painter.setPen(Qt::black);
    painter.drawText(QRect(0,m_sizeY, 100, 20), Qt::AlignLeft, m_model->getName() + " - " + m_model->getItemName());
}