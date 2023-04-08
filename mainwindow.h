#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSharedPointer>

#include "scenecontrol.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

enum color_style
{
    white = 0,
    black = 1
};

class MainWindow : public QMainWindow
{
    Q_OBJECT


public:
    explicit MainWindow(QWidget *parent = nullptr);
    virtual ~MainWindow();

private slots:
    void on_comboBox_activated(int index);

private:
    Ui::MainWindow *ui;

    sceneControl* scenContr = nullptr;
    QPalette dark_Palette, white_Palette;

    int StartSetSettings();//Метод создающий необходимые классы виджеты и производящий настройку соединений между нимим

    int startGraphicSettings();//Метод производящий графические настройки(Создание и инициализация Pallete и тд.)
    bool setStyle(color_style style);


};
#endif // MAINWINDOW_H
