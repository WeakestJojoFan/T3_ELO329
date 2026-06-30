#ifndef SMARTDEVICEVIEW_H
#define SMARTDEVICEVIEW_H
#include <QWidget>
#include "Equipo.h"
#include <QMouseEvent>
#include "ETNube.h"
#include <QColor>

class SmartDeviceView : public QWidget {
    Q_OBJECT
public:
    explicit SmartDeviceView(Equipo* model, ETNube* cloud, QWidget* parent = nullptr);
    void updatePosition();

protected:
    void paintEvent(QPaintEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;

    Equipo* m_model;
    int m_sizeX;
    int m_sizeY;
    ETNube* m_cloud;
    QColor m_brushColor;
    QColor m_penColor;
    int m_radioScan = 0;
    bool m_rectangle;
private slots:
    void scanAnimation();
};

#endif // SMARTDEVICEVIEW_H
