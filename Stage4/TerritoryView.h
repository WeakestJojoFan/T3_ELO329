#ifndef TERRITORYVIEW_H
#define TERRITORYVIEW_H

#include<QWidget>
#include<QPixmap>
#include<QVector>
#include "Territory.h"
#include "ETNube.h"

class TerritoryView: public QWidget {
    Q_OBJECT
public:
    explicit TerritoryView(Territory *model, QWidget *parent = nullptr);
    const Territory* getTerritory();
    void updateView();

protected:
    void paintEvent(QPaintEvent*) override; // Sobreescribir para dibujar

private:
    Territory *m_model;
    QPixmap m_backgroundPixmap;
    ETNube* m_cloud;
    QVector<QVector<Equipo*>> m_devices;
    double m_dataUpdateTimer;
    double m_deltaT;
signals:
    void updateData();
};


#endif // TERRITORYVIEW_H
