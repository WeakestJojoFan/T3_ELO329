#ifndef GFINDMY_H
#define GFINDMY_H
#include <qdialog.h>
#include <QPixmap>
#include <qpainter.h>
#include "ETNube.h"
#include "TerritoryView.h"


class gFindMy: public QDialog
{
    Q_OBJECT
public:
    gFindMy(QString imagePath, ETNube* cloud,TerritoryView* viewMap, QWidget* parent = nullptr);
private:
    ETNube* m_cloud;
};

class LienzoMapa : public QWidget {
    Q_OBJECT
private:
    QPixmap m_backgroundPixmap;
    ETNube* m_cloud;
    QMap<QString, QMap<QString, QPointF>> m_smartDeviceData;
    QMap<QString, QMap<QString, QPointF>> m_tagData;
public:
    LienzoMapa(const QString& imagePath, ETNube* cloud ,QWidget* parent = nullptr) : QWidget(parent), m_cloud(cloud) {
        if (m_backgroundPixmap.load(imagePath)) {
            this->setFixedSize(m_backgroundPixmap.size());
        } else {
            qWarning() << "No se pudo cargar la imagen de fondo:" << imagePath;
        }
    }
    void updateData();
protected:
    void paintEvent(QPaintEvent*) override;
};

#endif // GFINDMY_H
