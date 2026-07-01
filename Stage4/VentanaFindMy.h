#ifndef VENTANAFINDMY_H
#define VENTANAFINDMY_H

#include <QString>
#include <QDialog>
#include <QWidget>
#include <QListWidget>
#include "ETNube.h"
#include "TerritoryView.h"

class VentanaFindMy : public QDialog
{
public:
    VentanaFindMy(const QString& name, ETNube* cloud, QWidget* parent, TerritoryView* mapa);
private:
    ETNube* m_cloud;
private slots:
    void updateData();
    QListWidget* m_deviceList;
    QListWidget* m_tagList;
    QString m_user;
    TerritoryView* m_map;
};

#endif // VENTANAFINDMY_H
