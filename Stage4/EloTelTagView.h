#ifndef ELOTELTAGVIEW_H
#define ELOTELTAGVIEW_H
#include "SmartDeviceView.h"
#include "EloTelTag.h"

class EloTelTagView : public SmartDeviceView
{
    Q_OBJECT
public:
    explicit EloTelTagView(EloTelTag* model, QWidget* parent = nullptr);
};

#endif // ELOTELTAGVIEW_H
