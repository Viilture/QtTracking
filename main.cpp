#include "mainwindow.h"
#include <signal.h>
#include <QApplication>
#include <QTextCodec>
#include <QDebug>
#include <QStyleFactory>
#include <QDir>
#include <QMessageBox>
#include <QSettings>


int main( int argc, char ** argv )
{
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("Utf8"));
    QApplication a(argc, argv);
    QApplication::setStyle(QStyleFactory::create("Fusion"));
    MainWindow w;
    w.show();
    w.setWindowTitle("Tracking and Resolution");

    return a.exec();
}
