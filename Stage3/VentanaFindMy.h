#ifndef VENTANAFINDMY_H
#define VENTANAFINDMY_H

#include <QString>
#include <QDialog>
#include <QWidget>
#include "ETNube.h"

class VentanaFindMy : public QDialog
{
public:
    VentanaFindMy(const QString& name, ETNube* cloud, QWidget* parent);
};

#endif // VENTANAFINDMY_H
