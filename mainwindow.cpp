#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    scenContr = new sceneControl(this);
    ui->Video->addWidget(scenContr);

    startGraphicSettings();

}

MainWindow::~MainWindow()
{
    delete ui;
}

int MainWindow::startGraphicSettings()//Метод производящий графические настройки(Создание и инициализация Pallete и тд.)
{
    white_Palette = qApp->palette();//До сохранения исходной palette черную не устанавливать

    // Настраиваем палитру для цветовых ролей элементов интерфейса
    dark_Palette.setColor(QPalette::Window, QColor(53, 53, 53));
    dark_Palette.setColor(QPalette::WindowText, Qt::white);
    dark_Palette.setColor(QPalette::Base, QColor(25, 25, 25));
    dark_Palette.setColor(QPalette::AlternateBase, QColor(53, 53, 53));
    dark_Palette.setColor(QPalette::ToolTipBase, Qt::white);
    dark_Palette.setColor(QPalette::ToolTipText, Qt::white);
    dark_Palette.setColor(QPalette::Text, Qt::white);
    dark_Palette.setColor(QPalette::Button, QColor(53, 53, 53));
    dark_Palette.setColor(QPalette::ButtonText, Qt::white);
    dark_Palette.setColor(QPalette::BrightText, Qt::red);
    dark_Palette.setColor(QPalette::Link, QColor(42, 130, 218));
    dark_Palette.setColor(QPalette::Highlight, QColor(42, 130, 218));
    dark_Palette.setColor(QPalette::HighlightedText, Qt::black);

    setStyle(color_style::black);

    return 1;
}


bool MainWindow::setStyle(color_style style)//Метод выбор стиля
{
    switch(style)
    {
    case color_style::black:
    {   // Устанавливаем темную палитру
        qApp->setPalette(dark_Palette);
        return 1;
        break;
    }
    case color_style::white:
    {   // Устанавливаем светлую палитру
        qApp->setPalette(white_Palette);
        return 1;
        break;
    }
    default:
    {   return 0;
        break;
    }
    }
}

void MainWindow::on_comboBox_activated(int index)
{
    switch (index)
    {
    case 0: {scenContr->setTypeTracker(typeTrack::KCF);        break;}
    case 1: {scenContr->setTypeTracker(typeTrack::MIL);        break;}
    case 2: {scenContr->setTypeTracker(typeTrack::GOTURN);     break;}
    case 3: {scenContr->setTypeTracker(typeTrack::CSRT);       break;}
    case 4: {scenContr->setTypeTracker(typeTrack::DaSiamRPN);  break;}
    case 5: {scenContr->setTypeTracker(typeTrack::Nano);       break;}

    default: break;
    }
}

