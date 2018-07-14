#include "mainwindow.h"
#include <QApplication>
#include <QFile>

int main(int argc, char *argv[])
{
    QCoreApplication::setOrganizationName("Kumbralyov");
    QCoreApplication::setApplicationName("PService");

    QApplication a(argc, argv);
    MainWindow w;
    QFile file(":/qss/def-style");
    file.open(QFile::ReadOnly);
    QString styleSheet = QLatin1String(file.readAll());
    a.setStyleSheet(styleSheet);
    w.show();

    return a.exec();
}
