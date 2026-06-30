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

    m_cloud = m_model->getCloud();
    m_deltaT = model->getDeltaTime();

    QVector<Cellular*> cells = m_model->getCellulars();
    QVector<Tablet*> tablets = m_model->getTablets();
    QVector<EloTelTag*> tags = m_model->getTags();
    m_devices = {reinterpret_cast<QVector<Equipo*>&>(cells), reinterpret_cast<QVector<Equipo*>&>(tablets), reinterpret_cast<QVector<Equipo*>&>(tags)};

    if (!m_backgroundPixmap.load(imagePath)){
        qWarning() << "No se pudo cargar la imagen de fondo:" << imagePath;
    } else {
        this->setFixedSize(m_backgroundPixmap.size());
    }

    for (Cellular* cellModel : m_model->getCellulars()){ //creamos los cellulars
        CellularView* cellView = new CellularView(cellModel, m_cloud, this);
        cellView->show();
    }

    for (Tablet* tabletModel : m_model->getTablets()){
        TabletView* tabletView = new TabletView(tabletModel, m_cloud, this);
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

    for (const auto& sublista : std::as_const(m_devices)){
        for(Equipo* device : sublista){
            if (device->isTrackingActive() && device->getHistory().size() > 1) {

                QPen pen(QColor(5, 74, 41), 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
                painter.setPen(pen);

                const QList<QPointF>& points = device->getHistory();

                for (int i = 0; i < points.size() - 1; ++i) {
                    painter.drawLine(points[i], points[i + 1]);
                }

                painter.setBrush(QColor(63, 163, 77));
                painter.drawEllipse(points.first(), 4, 4);
            }
        }
    }
}

void TerritoryView::updateView(){
    m_dataUpdateTimer += m_deltaT;

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

    if (m_dataUpdateTimer >= 1.0){
        updateData(); //actualizar ventana findMy
        m_dataUpdateTimer -= 1.0;
    }
}

const Territory* TerritoryView::getTerritory(){return m_model;}