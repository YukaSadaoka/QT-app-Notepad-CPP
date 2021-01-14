#include "mainwindow.h"

#include <QApplication> // this takes care of the mouse moves


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec(); // This brings the application to loop while any events happens
}
