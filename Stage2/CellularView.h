#ifndef CELLULARVIEW_H
#define CELLULARVIEW_H

#include <QWidget>
#include "Cellular.h"

class CellularView: public QWidget
{
    Q_OBJECT
public:
    explicit CellularView(Cellular* model, QWidget* parent = nullptr);
    void updatePosition();
protected:
    void paintEvent(QPaintEvent*) override;
private:
    Cellular* m_model;
    int m_sizeX;
    int m_sizeY;
};

#endif // CELLULARVIEW_H
