#include <QApplication>
#include <QFileDialog>
#include <iostream>

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

    return QApplication::exec();
}