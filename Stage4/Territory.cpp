#include "Territory.h"
#include "Cellular.h"
#include "Tablet.h"
#include "EloTelTag.h"
#include "ETNube.h"
#include <QFile>
#include <QTextStream>
#include <QFileInfo>
#include <QDir>
#include <QDebug>
#include <utility>
#include <QImage>

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

    m_backgroundImagePath = configDir.absoluteFilePath(imageName);

    QImage imagen(m_backgroundImagePath);

    if (imagen.isNull()) {
        qWarning() << "Error: No se obtener las dimensiones de la imagen:" << m_backgroundImagePath;
        m_width = 800;
        m_height = 600;
    } else {
        m_width = imagen.width();
        m_height = imagen.height();

        qDebug() << "Plano inicializado exitosamente con dimensiones:" << m_width << "x" << m_height<< "y.";
    }

    if (!in.atEnd()) in >> m_deltaTime;

    if (!in.atEnd()) in >> m_numberOfPeople;


    m_cloud = new ETNube(); //creamos la nube para entregarsela a los celulares.


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

        Cellular* cell = new Cellular(name, m_cloud, cx, cy, cSpeed, cAngle, cDeltaAngle);
        m_cellulars.append(cell);


        if (in.atEnd()) break;

        lineBuffer = in.readLine();
        QTextStream tagStream(&lineBuffer);

        QString itemName;

        for (int i = 0 ; i < numTags; ++i){
            tagStream >> itemName >> cx >> cy >> cSpeed >> cAngle >> cDeltaAngle;

            EloTelTag* tag = new EloTelTag(name, itemName, cx, cy, cSpeed, cAngle, cDeltaAngle);
            m_tags.append(tag);
        }

        if (hasTablet == 1  && !in.atEnd()){
            if (in.atEnd()) break;
            lineBuffer = in.readLine();
            QTextStream tabletStream(&lineBuffer);
            tabletStream >> cx >> cy >> cSpeed >> cAngle >> cDeltaAngle;

            Tablet* tablet = new Tablet(name, cx, cy, cSpeed, cAngle, cDeltaAngle);
            m_tablets.append(tablet);
        }
    }

    file.close();

    return true;
}

void Territory::stepSim(){
    for (Cellular* cell : std::as_const(m_cellulars)) {
        if (cell->getX()<0 || cell->getX()>m_width){
            cell->reboteX();
        }else if(cell->getY()<0 || cell->getY() > m_height){
            cell->reboteY();
        }
        cell->updatePosition(m_deltaTime);
    }

    for (Tablet* tablet : std::as_const(m_tablets)) {
        if (tablet->getX()<0 || tablet->getX()>m_width){
            tablet->reboteX();
        }else if(tablet->getY()<0 || tablet->getY() > m_height){
            tablet->reboteY();
        }
        tablet->updatePosition(m_deltaTime, m_cellulars);
    }

    for (EloTelTag* tag : std::as_const(m_tags)) {
        if (tag->getX()<0 || tag->getX()>m_width){
            tag->reboteX();
        }else if(tag->getY()<0 || tag->getY() > m_height){
            tag->reboteY();
        }
        tag->updatePosition(m_deltaTime, m_cellulars);
    }
}

double Territory::getDeltaTime() const{
    return m_deltaTime;
}

QString Territory::getBackgroundImagePath() const { return m_backgroundImagePath;}

QVector<Cellular*> Territory::getCellulars() const {return m_cellulars;}

QVector<Tablet*> Territory::getTablets() const {return m_tablets;}

QVector<EloTelTag*> Territory::getTags() const {return m_tags;}

ETNube* Territory::getCloud() const {return m_cloud;}