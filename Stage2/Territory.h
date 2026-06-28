#ifndef TERRITORY_H
#define TERRITORY_H
#include <QDebug>
#include <QString>
#include <QVector>
#include "Cellular.h"
#include "Tablet.h"
#include "EloTelTag.h"

class Territory {
public:
    Territory();
    ~Territory();

    bool loadConfiguration(const QString &filePath);

    QString getBackgroundImagePath() const;
    double getDeltaTime() const;
    QVector<Cellular*> getCellulars() const;
    QVector<Tablet*> getTablets() const;
    QVector<EloTelTag*> getTags() const;

    void stepSim();


private:
    QString m_backgroundImagePath;
    int m_width;
    int m_height;

    double m_deltaTime;
    int m_numberOfPeople;

    QVector<Cellular*> m_cellulars;
    QVector<Tablet*> m_tablets;
    QVector<EloTelTag*> m_tags;
};

#endif // TERRITORY_H
