#include "MainWindow.h"
#include "Territory.h"
#include "TerritoryView.h"
#include <QVBoxLayout>
#include <QMenu>
#include <QMenuBar>
#include <QAction>
#include <QTimer>

MainWindow::MainWindow(Territory* territoryModel, QWidget* parent) : QWidget(parent), m_model(territoryModel) {
    m_territoryView = new TerritoryView(m_model, this);

    m_timer = new QTimer(this);

    connect(m_timer, &QTimer::timeout, this, &MainWindow::onTimerTick);

    QMenuBar* menuBar = new QMenuBar();

    QMenu* simMenu = menuBar->addMenu(tr("&Simulation"));

    QAction* startAction = simMenu->addAction(tr("Play"));
    connect(startAction, &QAction::triggered, this, &MainWindow::onStart);

    QAction* pauseAction = simMenu->addAction(tr("Pause"));
    connect(pauseAction, &QAction::triggered, this, &MainWindow::onPause);

    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->addWidget(menuBar);
    mainLayout->addWidget(m_territoryView);

    this->adjustSize();
}

void MainWindow::onTimerTick(){
    m_model->stepSim();
    m_territoryView->updateView();
}

void MainWindow::onStart(){
    int msDelta = static_cast<int>(m_model->getDeltaTime() * 1000);

    m_timer->start(msDelta);
}

void MainWindow::onPause(){
    m_timer->stop();
}