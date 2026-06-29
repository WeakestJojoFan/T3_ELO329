#ifndef TABLETVIEW_H
#define TABLETVIEW_H
#include "SmartDeviceView.h"
#include "Tablet.h"
#include "ETNube.h"

class TabletView : public SmartDeviceView
{
    Q_OBJECT
public:
    explicit TabletView(Tablet* model, ETNube* cloud ,QWidget* parent = nullptr);
};

#endif // TABLETVIEW_H