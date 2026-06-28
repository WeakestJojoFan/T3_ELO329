#ifndef ELOTELTAGVIEW_H
#define ELOTELTAGVIEW_H
#include <QWidget>
#include "EloTelTag.h"

class EloTelTagView : public QWidget
{
    Q_OBJECT
public:
    explicit EloTelTagView(EloTelTag* model, QWidget* parent = nullptr);
    void updatePosition();
protected:
    void paintEvent(QPaintEvent*) override;
private:
    EloTelTag* m_model;
    int m_sizeX;
    int m_sizeY;
};

#endif // ELOTELTAGVIEW_H
