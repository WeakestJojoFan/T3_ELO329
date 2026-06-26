#include <QApplication>
#include <QFileDialog>
#include <iostream>

#include "Territory.h"
#include "TerritoryView.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QString fileName = QFileDialog::getOpenFileName(
        nullptr,
        "Select Config File",
        QDir::homePath(),
        "Text Files (*.txt)"
    );

    if (fileName.isEmpty()){
        return 0;
    }

    Territory territory;
    if (!territory.loadConfiguration(fileName)) {
        std::cerr << "Error al cargar el archivo de configuracion." << std::endl;
        return -1;
    }

    TerritoryView territoryView(&territory);

    territoryView.show();

    return QApplication::exec();
}