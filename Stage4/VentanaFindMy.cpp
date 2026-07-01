#include "VentanaFindMy.h"
#include <QString>
#include <QWidget>
#include "ETNube.h"
#include "TerritoryView.h"
#include <QLabel>
#include <QBoxLayout>
#include <QListWidget>
#include <QPushButton>

VentanaFindMy::VentanaFindMy(const QString& name, ETNube* cloud, QWidget* parent, TerritoryView* mapa): QDialog(parent) {
    m_user = name;
    m_cloud = cloud;
    m_map = mapa;

    setWindowTitle("FindMy - " + m_user);
    setWindowIcon(QIcon(":/icon.jpg"));
    resize(300,400);

    connect(m_map, &TerritoryView::updateData, this, &VentanaFindMy::updateData);

    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    QVBoxLayout* upper = new QVBoxLayout();
    QVBoxLayout* lower = new QVBoxLayout();
    QHBoxLayout* buttons = new QHBoxLayout();

    QLabel* deviceLabel = new QLabel(QString("Dispositivos de %1:").arg(m_user), this);
    deviceLabel->setStyleSheet("font-weight: bold; font-size: 14px;");
    QLabel* tagLabel = new QLabel(QString("Items de %1:").arg(m_user), this);
    tagLabel->setStyleSheet("font-weight: bold; font-size: 14px;");

    m_deviceList = new QListWidget(this);
    m_tagList = new QListWidget(this);

    QVector<Cellular*> cells = mapa->getTerritory()->getCellulars();
    QVector<Tablet*> tablets = mapa->getTerritory()->getTablets();
    QVector<EloTelTag*> tags = mapa->getTerritory()->getTags();
    QVector<QVector<Equipo*>> devices = {reinterpret_cast<QVector<Equipo*>&>(cells), reinterpret_cast<QVector<Equipo*>&>(tablets), reinterpret_cast<QVector<Equipo*>&>(tags)};

    for (const auto& sublista : devices){
        for(Equipo* device : sublista){
            if (device->getName() == m_user){
                QPushButton* trackBtn = new QPushButton(this);
                if (device && device->isTrackingActive()) {
                    trackBtn->setText(QString("%1: Detener Rastreo").arg(device->getItemName()));
                    trackBtn->setStyleSheet("background-color: #ff3b30; color: white; font-weight: bold;");
                } else {
                    trackBtn->setText(QString("%1: Rastrear Trayectoria").arg(device->getItemName()));
                    trackBtn->setStyleSheet("background-color: #007aff; color: white; font-weight: bold;");
                }
                buttons->addWidget(trackBtn);

                connect(trackBtn, &QPushButton::clicked, this, [device, trackBtn, this]() {
                    if (!device) return;

                    bool nuevoEstado = !device->isTrackingActive();
                    device->setTracking(nuevoEstado);

                    if (nuevoEstado) {
                        trackBtn->setText(QString("%1: Detener Rastreo").arg(device->getItemName()));
                        trackBtn->setStyleSheet("background-color: #ff3b30; color: white; font-weight: bold;");
                    } else {
                        trackBtn->setText(QString("%1: Rastrear Trayectoria").arg(device->getItemName()));
                        trackBtn->setStyleSheet("background-color: #007aff; color: white; font-weight: bold;");
                    }

                    if (this->parentWidget()) {
                        this->parentWidget()->update();
                    }
                });
            }
        }
    }


    upper->addWidget(deviceLabel);
    upper->addWidget(m_deviceList);
    lower->addWidget(tagLabel);
    lower->addWidget(m_tagList);
    mainLayout->addLayout(upper);
    mainLayout->addLayout(lower);
    mainLayout->addLayout(buttons);

    updateData();
}

void VentanaFindMy::updateData() {
    auto datos = m_cloud->downloadData(m_user);
    QMap<QString, QPointF> smartDeviceData = datos.first;
    QMap<QString, QPointF> tagData = datos.second;

    m_deviceList->clear();
    m_tagList->clear();

    for (auto it = smartDeviceData.constBegin(); it != smartDeviceData.constEnd(); ++it){
        QString info = QString("%1: %2 , %3").arg(it.key()).arg(it.value().x(),0, 'f', 1).arg(it.value().y(),0, 'f', 1);
        m_deviceList->addItem(info);
    }
    for (auto it = tagData.constBegin(); it != tagData.constEnd(); ++it){
        QString info = QString("%1: %2 , %3").arg(it.key()).arg(it.value().x(),0, 'f', 1).arg(it.value().y(),0, 'f', 1);
        m_tagList->addItem(info);
    }
}