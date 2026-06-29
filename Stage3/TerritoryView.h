#ifndef TERRITORYVIEW_H
#define TERRITORYVIEW_H

#include<QWidget>
#include<QPixmap>
#include "Territory.h"
#include "ETNube.h"

class TerritoryView: public QWidget {
    Q_OBJECT
public:
    explicit TerritoryView(Territory *model, QWidget *parent = nullptr);
    void updateView();

protected:
    void paintEvent(QPaintEvent*) override; // Sobreescribir para dibujar

private:
    Territory *m_model;
    QPixmap m_backgroundPixmap;
    ETNube* m_cloud;
};


#endif // TERRITORYVIEW_H
