#ifndef TABLETVIEW_H
#define TABLETVIEW_H
#include "Tablet.h"
#include <QWidget>

class TabletView : public QWidget
{
    Q_OBJECT
public:
    explicit TabletView(Tablet* model, QWidget* parent = nullptr);
    void updatePosition();
protected:
    void paintEvent(QPaintEvent*) override;
private:
    Tablet* m_model;
    int m_sizeX;
    int m_sizeY;
};

#endif // TABLETVIEW_H
