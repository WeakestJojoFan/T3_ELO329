#include "TerritoryView.h"
#include <QPainter>
#include <QDebug>
#include "Territory.h"
#include "Cellular.h"
#include "CellularView.h"

TerritoryView::TerritoryView(Territory *model, QWidget *parent): QWidget(parent), m_model(model){
    QString imagePath = m_model->getBackgroundImagePath();

    if (!m_backgroundPixmap.load(imagePath)){
        qWarning() << "No se pudo cargar la imagen de fondo:" << imagePath;
    } else {
        this->setFixedSize(m_backgroundPixmap.size());
    }

    for (Cellular* cellModel : m_model->getCellulars()){ //creamos los cellulars
        CellularView* cellView = new CellularView(cellModel, this);
        cellView->show();
    }
}


void TerritoryView::paintEvent(QPaintEvent *) {
    QPainter painter(this);

    if (!m_backgroundPixmap.isNull()) {
        painter.drawPixmap(0, 0, m_backgroundPixmap);
    }
}