#include "Taschenrechner.h"
#include <QtWidgets/QApplication>
#include "ui_Taschenrechner.h"
#include <QPushButton>
#include <QMessageBox>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Taschenrechner w;
    w.show();
    return a.exec();
}
