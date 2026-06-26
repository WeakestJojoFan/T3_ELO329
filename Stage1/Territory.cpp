#include "Territory.h"
#include "Cellular.h"
#include <QFile>
#include <QTextStream>
#include <QFileInfo>
#include <QDir>
#include <QDebug>
#include <utility>

Territory::Territory() : m_deltaTime(0.1), m_numberOfPeople(0) {}

Territory::~Territory() {
    for (Cellular* cell : std::as_const(m_cellulars)) {
        delete cell;
    }
    m_cellulars.clear();
}

bool Territory::loadConfiguration(const QString &filePath){
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)){
        qWarning() << "No se pudo abrir el archivo de configuración: " << filePath;
        return false;
    }

    QFileInfo fileInfo(filePath);
    QDir configDir = fileInfo.absoluteDir(); //obtenemos la ubicacion del archivo config

    QTextStream in(&file);

    if (in.atEnd()){
        qWarning() << "El archivo de configuracion esta vacio." << filePath;
        return false;
    }

    QString imageName;
    if (!in.atEnd()) imageName = in.readLine().trimmed();

    m_backgroundImagePath = configDir.absoluteFilePath(imageName); //guardamos la ubicacion de la imagen de fondo

    if (!in.atEnd()) in >> m_deltaTime;

    if (!in.atEnd()) in >> m_numberOfPeople;

    in.readLine();

    QString lineBuffer;

    for (int i = 0; i < m_numberOfPeople; ++i){
        if (in.atEnd()) break;

        lineBuffer = in.readLine();

        QTextStream nameStream(&lineBuffer);

        QString name;
        int numTags = 0;
        int hasTablet = 0;
        nameStream >> name >> numTags >> hasTablet;

        if (in.atEnd()) break;

        lineBuffer = in.readLine();

        QTextStream cellStream(&lineBuffer);

        double cx, cy, cSpeed, cAngle, cDeltaAngle;
        cellStream >> cx >> cy >> cSpeed >> cAngle >> cDeltaAngle;

        Cellular* cell = new Cellular(name, cx, cy, cSpeed, cAngle, cDeltaAngle);
        m_cellulars.append(cell);

        if (!in.atEnd()) in.readLine(); // Nos saltamos la linea de los tags

        if (hasTablet == 1  && !in.atEnd()){ // Nos saltamos la linea de la tablet
            in.readLine();
        }
    }

    file.close();

    return true;
}

QString Territory::getBackgroundImagePath() const { return m_backgroundImagePath;}

QVector<Cellular*> Territory::getCellulars() const {return m_cellulars;}