#ifndef SCENECONTROL_H
#define SCENECONTROL_H

#include <memory>
#include <QGraphicsView>
#include <QObject>
#include <QWheelEvent>
#include <QDebug>
#include <QTimer>
#include <QRect>
#include <QThread>
#include <QDateTime>
#include <QTime>
#include <QIcon>
#include <QGraphicsItem>
#include <QGraphicsPixmapItem>
#include <QPushButton>
#include <QFileDialog>
#include <QCoreApplication>
#include <utility>

#include <opencv2/tracking.hpp>
#include <opencv2/tracking/tracking_legacy.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>

#include "transform.h"
#include "trackingWrapper.h"


//Состояние выделения прямоугольника  для области отслеживания
enum stateSelect
{
    notSelect = 0,
    startSelect,
    endSelect,
};


class sceneControl: public QGraphicsView
{
    Q_OBJECT
public:
    explicit sceneControl(QWidget *parent = nullptr, QGraphicsScene *scene = nullptr);
    virtual ~sceneControl();

    //Устанавливаем тип трекера
    void setTypeTracker(typeTrack newType);

private:

    QGraphicsScene* m_scene = nullptr;

    QTimer *timerInit;//Инициализирующий таймер
    QTimer  *timerUpdate;//Таймер обновления
    QGraphicsItem *item = nullptr;
    QPushButton *setPath;         // Установка пути до файла

    bool stateTrack = false;

    //Этапы распознавания движения на видеоизображении
    cv::Mat frame1, frame2;

    //Обновляем положение элементов управления
    void updatePosElemContr();
    //Настраиваем элементы управления
    void startInitElemContr();
    //Обновляем Область отслеживания на трекере
    void updateRectTrack(QRect updateRect);
    //Автомасштабирование сцены
    void autReSize();

    void init();

    //Перевернуть прямоугольник при необходимости (до QRect::span в Qt.6.0.)
    QRect reversRectifNeed(QPoint pos1, QPoint posMove);

    //Проверка правильности выбора прямоугольника
    QRect updIfRectNull(QRect& checkRect);

    QPoint pos1,pos2;
    QGraphicsItem* itemRect  = nullptr;
    QRect rect = QRect(0,0,1,1);//Область за которой надо следить

    //Состояние выделения прямоугольника для области отслеживания
    stateSelect selectState = stateSelect::notSelect;

    cv::VideoCapture cap;

    //управление трекерами
    QSharedPointer<videoCV::TrackingWrapper> trackControl;
    QThread* trackThread;

protected:
    void resizeEvent(QResizeEvent *evt );
    void mouseMoveEvent(QMouseEvent* evt );
    void mouseReleaseEvent(QMouseEvent *evt);
    void mousePressEvent(QMouseEvent *evt);


public slots:
    void startInit();//Инициализирующие настройки
    void updVideoPlay();//Проигрывание видео

    void playVideo();
    void stopVideo();

    //Установка пути до файла
    void setNewPath();

    void updateRect(QRect newRect);

signals:
    //Обновляем значение текущей картинки и выбранного места поиска у трекера
    void initTracker(cv::Mat newImage, QRect newRect);

    void updateTracker(cv::Mat newImage);

    //Изменяем тип трекера
    void setTracker(typeTrack newType);
};

#endif // SCENECONTROL_H
