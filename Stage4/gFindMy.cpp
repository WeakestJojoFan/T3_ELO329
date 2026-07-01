#include "gFindMy.h"
#include <QPainter>
#include <qboxlayout.h>
#include <QScrollArea>
#include "TerritoryView.h"

gFindMy::gFindMy(QString imagePath, ETNube* cloud, TerritoryView* viewMap, QWidget* parent): QDialog(parent) {
    setWindowTitle("GFindMy");
    setWindowIcon(QIcon(":/icon.jpg"));
    resize(500,500);
    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(0, 0, 0, 0);

    QScrollArea* scrollArea = new QScrollArea(this);
    scrollArea->setWidgetResizable(false);
    scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);

    LienzoMapa* lienzo = new LienzoMapa(imagePath, cloud, this);
    scrollArea->setWidget(lienzo);

    mainLayout->addWidget(scrollArea);
    connect(viewMap, &TerritoryView::updateData, lienzo, &LienzoMapa::updateData);
}


void LienzoMapa::updateData(){
    if (!m_cloud) return;

    auto datos = m_cloud->downloadAllData();
    m_smartDeviceData = datos.first;
    m_tagData = datos.second;

    this->update();
}

void LienzoMapa::paintEvent(QPaintEvent*) {
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    if (!m_backgroundPixmap.isNull()) {
        painter.drawPixmap(0, 0, m_backgroundPixmap);
    }

    if (!m_cloud) return;

    for (auto itUsuario = std::as_const(m_smartDeviceData).constBegin(); itUsuario != std::as_const(m_smartDeviceData).constEnd(); ++itUsuario) {
        QString nombreUsuario = itUsuario.key();
        const QMap<QString, QPointF>& listaDispositivos = itUsuario.value();

        for (auto itDevice = listaDispositivos.constBegin(); itDevice != listaDispositivos.constEnd(); ++itDevice) {
            QPointF pos = itDevice.value();

            if (itDevice.key() == "Tablet"){
                painter.setBrush(QColor(144, 238, 144));
                painter.setPen(QPen(Qt::darkGreen, 1));
                painter.drawRoundedRect(pos.x() - 15, pos.y()-10,30,20,5,5);
            }else{
                painter.setBrush(QColor(35, 145, 240));
                painter.setPen(QPen(Qt::blue, 1));
                painter.drawRoundedRect(pos.x() - 5, pos.y()-10,10,20,2,2);
            }
            painter.setPen(Qt::black);
            QString etiqueta = QString("%1 (%2)").arg(itDevice.key(), nombreUsuario);
            painter.drawText(pos + QPointF(12, 4), etiqueta);
        }
    }

    for (auto itUsuario = std::as_const(m_tagData).constBegin(); itUsuario != std::as_const(m_tagData).constEnd(); ++itUsuario) {
        QString nombreUsuario = itUsuario.key();
        const QMap<QString, QPointF>& listaTags = itUsuario.value();

        for (auto itTag = listaTags.constBegin(); itTag != listaTags.constEnd(); ++itTag) {
            QPointF pos = itTag.value();

            painter.setBrush(Qt::red);
            painter.setPen(QPen(Qt::darkRed, 1));
            painter.drawEllipse(pos, 7, 7);

            painter.setPen(Qt::black);
            QString etiqueta = QString("%1 (%2)").arg(itTag.key(), nombreUsuario);
            painter.drawText(pos + QPointF(12, 4), etiqueta);
        }
    }
}