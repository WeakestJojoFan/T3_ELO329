#include "SmartDeviceView.h"
#include <QPainter>
#include <QMouseEvent>
#include <cmath>
#include <QDebug>
#include <QMenu>
#include "VentanaFindMy.h"
#include "ETNube.h"
#include "EquipoPasivo.h"
#include "TerritoryView.h"
#include <QVariantAnimation>

SmartDeviceView::SmartDeviceView(Equipo* model, ETNube* cloud, QWidget* parent)
    : QWidget(parent), m_model(model), m_sizeX(15), m_sizeY(30), m_cloud(cloud)
{
    setFixedSize(100, 100);

    EquipoPasivo* modeloPasivo = qobject_cast<EquipoPasivo*>(m_model); //typecast
    if (modeloPasivo) {
        connect(modeloPasivo, &EquipoPasivo::scanAnimation, this, &SmartDeviceView::scanAnimation);
    }
    updatePosition();
}

void SmartDeviceView::updatePosition() {
    if (m_model) {
        move(static_cast<int>(std::round(m_model->getX())) - this->width() / 2,
             static_cast<int>(std::round(m_model->getY())) - this->height() / 2);
    }
}
void SmartDeviceView::paintEvent(QPaintEvent*) {
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    if (m_radioScan > 0) {
        QPointF centroDispositivo(this->width() / 2.0, this->height() / 2.0);

        QColor colorRelleno(35, 145, 240, 40);
        QColor colorBorde(0, 120, 240, 200);

        painter.setBrush(colorRelleno);
        painter.setPen(QPen(colorBorde, 1.5, Qt::DashLine)); // Línea segmentada para efecto de radar

        painter.drawEllipse(centroDispositivo, m_radioScan, m_radioScan);
    }

    int grosorBorde = 2;
    painter.setBrush(m_brushColor);
    painter.setPen(QPen(m_penColor, grosorBorde));
    QString label = m_model->getName();

    if (m_rectangle){
        painter.drawRoundedRect((this->width() - m_sizeX) / 2.0, (this->height() - m_sizeY) / 2.0, m_sizeX, m_sizeY, 5, 5);
    }else {
        painter.drawEllipse(QPointF(this->width()/2 , this->height()/2), m_sizeX/2, m_sizeY/2);
        label = m_model->getName() + " - " + m_model->getItemName();
    }

    painter.setPen(Qt::black);
    painter.drawText(QRect(0, (this->height() + m_sizeY) / 2.0, 100, 20), Qt::AlignCenter, label);
}

void SmartDeviceView::scanAnimation(){
    QVariantAnimation* animation= new QVariantAnimation(this);

    animation->setDuration(1000);
    animation->setStartValue(0);
    animation->setEndValue(50);
    animation->setEasingCurve(QEasingCurve::OutCurve);

    connect(animation, &QVariantAnimation::valueChanged, this, [this](const QVariant& value) {
        m_radioScan = value.toInt();
        this->update();
    });

    connect(animation, &QVariantAnimation::finished, this, [this, animation]() {
        m_radioScan = 0;
        this->update();
        animation->deleteLater();
    });

    animation->start();
}


void SmartDeviceView::mousePressEvent(QMouseEvent* event) {
    if (event->button() == Qt::LeftButton) {
        QPoint clicPos = event->pos();

        if (clicPos.x() >= (this->width() - m_sizeX)/2 && clicPos.x() <= (this->width()+ m_sizeX)/2 &&
            clicPos.y() >= (this->height() - m_sizeY)/2 && clicPos.y() <= (this->height() + m_sizeY)/2) {

            QMenu* menu = new QMenu(this);

            QAction* findMyAction = menu->addAction("FindMy");

            connect(findMyAction, &QAction::triggered, this, [this]() {
                qDebug() << "Abriendo Find My para:" << m_model->getName();

                TerritoryView* mapa = qobject_cast<TerritoryView*>(this->parentWidget());
                VentanaFindMy* window = new VentanaFindMy(m_model->getName(), m_cloud, this->window(), mapa);

                window->show();
            });

            QPoint globalPos = this->mapToGlobal(QPoint((this->width()+ m_sizeX)/2, (this->height() + m_sizeY)/2));

            menu->exec(globalPos);

            menu->deleteLater();
            return;
        } else {
            event->ignore();
            return;
        }
    }
    QWidget::mousePressEvent(event);
}
