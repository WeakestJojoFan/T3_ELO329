#include "TerritoryView.h"
#include <QPainter>
#include <QDebug>
#include "Territory.h"
#include "Cellular.h"
#include "CellularView.h"
#include "Tablet.h"
#include "TabletView.h"
#include "EloTelTag.h"
#include "EloTelTagView.h"
#include <QVector>

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

    for (Tablet* tabletModel : m_model->getTablets()){
        TabletView* tabletView = new TabletView(tabletModel, this);
        tabletView->show();
    }

    for (EloTelTag* tagModel : m_model->getTags()){
        EloTelTagView* tagView = new EloTelTagView(tagModel, this);
        tagView->show();
    }
}


void TerritoryView::paintEvent(QPaintEvent *) {
    QPainter painter(this);

    if (!m_backgroundPixmap.isNull()) {
        painter.drawPixmap(0, 0, m_backgroundPixmap);
    }
}

void TerritoryView::updateView(){
    QVector<CellularView*> cellsView = this->findChildren<CellularView*>();

    for (CellularView* cellView : std::as_const(cellsView)){
        cellView->updatePosition();
    }

    QVector<TabletView*> tabletsView = this->findChildren<TabletView*>();

    for (TabletView* tabView : std::as_const(tabletsView)){
        tabView->updatePosition();
    }

    QVector<EloTelTagView*> tagsView = this->findChildren<EloTelTagView*>();

    for (EloTelTagView* tagView : std::as_const(tagsView)){
        tagView->updatePosition();
    }
}