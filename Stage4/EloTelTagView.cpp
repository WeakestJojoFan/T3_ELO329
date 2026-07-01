#include "EloTelTagView.h"
#include "EloTelTag.h"
#include <QPainter>
#include <QVariantAnimation>
#include <cmath>

EloTelTagView::EloTelTagView(EloTelTag* model, QWidget* parent): SmartDeviceView(model, nullptr, parent) {
    m_sizeX = 15;
    m_sizeY = 15; //dimensiones del dibujo
    m_brushColor = Qt::red;
    m_penColor = Qt::darkRed;
    m_rectangle = false; //no es un rectangulo
    this->setAttribute(Qt::WA_TransparentForMouseEvents, true);
}