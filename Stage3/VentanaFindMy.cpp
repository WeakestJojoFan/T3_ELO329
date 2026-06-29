#include "VentanaFindMy.h"
#include <QString>
#include <QWidget>
#include "ETNube.h"
#include <QLabel>
#include <QBoxLayout>
#include <QListWidget>

VentanaFindMy::VentanaFindMy(const QString& name, ETNube* cloud, QWidget* parent): QDialog(parent) {
    setWindowTitle("FindMy - " + name);
    resize(300,400);

    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    QVBoxLayout* upper = new QVBoxLayout();
    QVBoxLayout* lower = new QVBoxLayout();

    QLabel* deviceLabel = new QLabel(QString("Dispositivos de %1:").arg(name), this);
    deviceLabel->setStyleSheet("font-weight: bold; font-size: 14px;");
    QLabel* tagLabel = new QLabel(QString("Items de %1:").arg(name), this);
    tagLabel->setStyleSheet("font-weight: bold; font-size: 14px;");

    QListWidget *deviceList = new QListWidget(this);
    QListWidget *tagList = new QListWidget(this);

    auto datos = cloud->downloadData(name);
    QMap<QString, QPointF> smartDeviceData = datos.first;
    QMap<QString, QPointF> tagData = datos.second;

    for (auto it = smartDeviceData.constBegin(); it != smartDeviceData.constEnd(); ++it){
        QString info = QString("%1: %2 , %3").arg(it.key()).arg(it.value().x(),0, 'f', 1).arg(it.value().y(),0, 'f', 1);
        deviceList->addItem(info);
    }
    for (auto it = tagData.constBegin(); it != tagData.constEnd(); ++it){
        QString info = QString("%1: %2 , %3").arg(it.key()).arg(it.value().x(),0, 'f', 1).arg(it.value().y(),0, 'f', 1);
        tagList->addItem(info);
    }


    upper->addWidget(deviceLabel);
    upper->addWidget(deviceList);
    lower->addWidget(tagLabel);
    lower->addWidget(tagList);
    mainLayout->addLayout(upper);
    mainLayout->addLayout(lower);
}
