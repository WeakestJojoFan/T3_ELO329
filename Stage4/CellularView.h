#ifndef CELLULARVIEW_H
#define CELLULARVIEW_H
#include "Cellular.h"
#include "SmartDeviceView.h"
#include "ETNube.h"

class CellularView: public SmartDeviceView
{
    Q_OBJECT
public:
    explicit CellularView(Cellular* model, ETNube* cloud, QWidget* parent = nullptr);
};

#endif // CELLULARVIEW_H
