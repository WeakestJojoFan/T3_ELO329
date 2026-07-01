#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QTimer>
#include "Territory.h"
#include "TerritoryView.h"

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    explicit MainWindow(Territory* territoryModel, QWidget* parent = nullptr);
private slots:
    void onStart();
    void onPause();
    void gFindMyOpen();
    void onTimerTick();
private:
    Territory* m_model;
    TerritoryView* m_territoryView;
    QTimer* m_timer;
};

#endif // MAINWINDOW_H
