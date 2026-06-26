#ifndef TERRITORY_H
#define TERRITORY_H

#include <QString>
#include <QVector>
#include "Cellular.h"

class Territory {
public:
    Territory();
    ~Territory();

    bool loadConfiguration(const QString &filePath);

    QString getBackgroundImagePath() const;
    double getDeltaTime() const;
    QVector<Cellular*> getCellulars() const;

    void updatePositions();


private:
    QString m_backgroundImagePath;
    double m_deltaTime;
    int m_numberOfPeople;

    QVector<Cellular*> m_cellulars;
};

#endif // TERRITORY_H
