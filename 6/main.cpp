#include "mainwindow.h"

#include <QApplication>
#include <QFile>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QFile qss(":/project.qss");

    if (qss.open(QFile::ReadOnly))
    {
        QString style = qss.readAll();
        a.setStyleSheet(style);

        qss.close();
    }
    else
    {
        qWarning() << "Can't open project.qss";
    }

    MainWindow w;
    w.resize(800, 600);
    w.setMinimumSize(800, 600);
    w.show();

    return QCoreApplication::exec();
}
