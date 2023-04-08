#include "scenecontrol.h"

using namespace std;
using namespace cv;
Q_DECLARE_METATYPE(cv::Mat);
Q_DECLARE_METATYPE(typeTrack);

sceneControl::sceneControl(QWidget *parent, QGraphicsScene *scene):
    QGraphicsView(std::move(scene), std::move(parent))
{
    init();

}

sceneControl::~sceneControl()
{

}

//Устанавливаем тип трекера
void sceneControl::setTypeTracker(typeTrack newType)
{
    emit setTracker(newType);
}

void sceneControl::init()
{
    //Отключаем ScrollBar
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    //Функция масштабирования scale будет опираться на точку под курсором мыши
    setTransformationAnchor(QGraphicsView::AnchorUnderMouse);

    //Создаем сцену
    m_scene = new QGraphicsScene();
    setScene(m_scene);

    //Создаем трекер
    trackControl = QSharedPointer<videoCV::TrackingWrapper>(new videoCV::TrackingWrapper(typeTrack::Nano));
    trackThread = new QThread();
    trackControl->moveToThread(trackThread);
    trackThread->start();


    qRegisterMetaType<cv::Mat>();
    qRegisterMetaType<typeTrack>();
    connect(this, SIGNAL(initTracker(cv::Mat, QRect)), trackControl.data(), SLOT(initTracker(cv::Mat, QRect)));
    connect(this, SIGNAL(updateTracker(cv::Mat)), trackControl.data(), SLOT(updateTracker(cv::Mat)));
    //connect(this, &sceneControl::setTracker, trackControl.data(),&videoCV::TrackingWrapper::setTracker);
    connect(this, SIGNAL(setTracker(typeTrack)), trackControl.data(), SLOT(setTracker(typeTrack)));
    connect(trackControl.data(), SIGNAL(updateRect(QRect)), this, SLOT(updateRect(QRect)));

    //Настраиваем время
    timerInit = new QTimer();
    connect(timerInit, SIGNAL(timeout()), this, SLOT(startInit()));
    timerInit->setSingleShot(300);
    timerInit->start();

    startInitElemContr();

    QDir dir(QCoreApplication::applicationDirPath()); // Получаем путь к директории приложения
    dir.cdUp(); dir.cdUp(); // Переходим на уровень выше
    std::string video = dir.path().toStdString() + "/test4.mp4" ;

    cap.open(video);

    cap >> frame1;
    item = m_scene->addPixmap(videoCV::cvMatToQPixmap(frame1));
}

//Инициализирующие настройки
void sceneControl::startInit()
{
    //Таймер обновления
    timerUpdate = new QTimer();
    connect(timerUpdate, SIGNAL(timeout()), this, SLOT(updVideoPlay()));
    timerUpdate->setInterval(50);

    cap >> frame1;
    m_scene->clear(); //Обдумать улучшение!!!-----------------------
    item = m_scene->addPixmap(videoCV::cvMatToQPixmap(frame1));

    if(item != nullptr)
    { fitInView(item, Qt::KeepAspectRatio);}
}

//Обновляем положение элементов управления
void sceneControl::updatePosElemContr()
{
    //Автомасштабирование сцены
    if(setPath!=0)
        setPath->setGeometry(10, 10, 30, 30);
}

//Настраиваем элементы управления
void sceneControl::startInitElemContr()
{


    //Установка пути до файла
    setPath = new QPushButton(this);
    setPath->setMaximumSize(60, 60);
    setPath->setIcon(QIcon(QPixmap(":/img/open_i.png")));
    connect(setPath, SIGNAL(clicked()), this, SLOT(setNewPath()));


    //Обновляем положение элементов управления
    updatePosElemContr();
}

//Обновляем Область отслеживания на трекере
void sceneControl::updateRectTrack(QRect updateRect)
{
    if(!trackControl.isNull())
    {
        emit initTracker(frame1, updateRect);
        stateTrack = true;
    }
}

//Автомасштабирование сцены
void sceneControl::autReSize()
{
    if(item != nullptr)
        fitInView(item, Qt::KeepAspectRatio);
}

//Перевернуть прямоугольник при необходимости (до QRect::span в Qt.6.0.)
QRect sceneControl::reversRectifNeed(QPoint pos1, QPoint posMove)
{
    QRect accRect;
    //Аналогичнр QRect::span в Qt.6.0 устанавливает верхнюю левую точку, как первую точку QRect
    if(pos1.x()<posMove.x())
    {
        accRect.setX(pos1.x());
        accRect.setWidth(posMove.x()-pos1.x());
    }
    else
    {
        accRect.setX(posMove.x());
        accRect.setWidth(pos1.x()-posMove.x());
    }

    if(pos1.y()<posMove.y())
    {
        accRect.setY(pos1.y());
        accRect.setHeight(posMove.y()-pos1.y());
    }
    else
    {
        accRect.setY(posMove.y());
        accRect.setHeight(pos1.y()-posMove.y());
    }

    return accRect;
}

//Проверка правильности выбора прямоугольника
QRect sceneControl::updIfRectNull(QRect &checkRect)
{
    QRect updRect = std::move(checkRect);

    //Если длина и ширина прямоугольника менее 1, то изменяем её, но не выходя за рамки кадра
    if(updRect.width() < 5)
    {
        updRect.setX(updRect.center().x() - 25);
        updRect.setWidth(50);
    }


    if(updRect.height() < 2)
    {
        updRect.setY(updRect.center().y() - 25);
        updRect.setHeight(50);
    }

    return updRect;
}

//Установка пути до файла
void sceneControl::setNewPath()
{
    timerUpdate->stop();
    QDir dir(QCoreApplication::applicationDirPath()); // Получаем путь к директории приложения
    dir.cdUp(); dir.cdUp(); // Переходим на уровень выше

    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"),  dir.path(),tr("Images (*.mp4 *.avi)"));

    if(fileName != "")
    {
        cap.open(fileName.toStdString());
        timerUpdate->start();
        stateTrack = false;
    }

}


void sceneControl::resizeEvent(QResizeEvent *evt)
{
    if(item != nullptr)
        fitInView(item, Qt::KeepAspectRatio);

    //Обновляем положение элементов управления
    updatePosElemContr();

}

void sceneControl::mousePressEvent(QMouseEvent *evt)
{
    if(evt->button() == Qt::LeftButton)
    {
        timerUpdate->stop();
        //Устанавливаем 1 точку
        pos1 = mapToScene(evt->pos()).toPoint();
        //Выбираем следующий режим отслеживания
        selectState = stateSelect::endSelect;
    }
    else if(evt->button() == Qt::RightButton)
    {
        stateTrack = false;
    }
}

void sceneControl::mouseMoveEvent(QMouseEvent *evt)
{
    if((selectState == stateSelect::endSelect)&&(m_scene!=nullptr))
    {
        //Перевернуть прямоугольник при необходимости (до QRect::span в Qt.6.0.)
        rect = reversRectifNeed(pos1, mapToScene(evt->pos()).toPoint());


        //Удаляем старый и отрисовываем прямоугольника на сцене
        if(itemRect!=nullptr)
            m_scene->removeItem(itemRect);
        itemRect = m_scene->addRect(rect, QPen(QColor(Qt::green)));
    }
}

void sceneControl::mouseReleaseEvent(QMouseEvent *evt)
{

    if(selectState == stateSelect::endSelect)//Закаанчиваем выбирать область слежения
    {
        //Перевернуть прямоугольник при необходимости (до QRect::span в Qt.6.0.)
        rect = reversRectifNeed(pos1, mapToScene(evt->pos()).toPoint());
        rect = updIfRectNull(rect);

        selectState = stateSelect::notSelect;

        //Обновляем Область отслеживания на трекере
        updateRectTrack(rect);

        stateTrack = true;
        timerUpdate->start();

        //Продолжаем воспроизводить видео
        if(timerUpdate!=0) timerUpdate->start();

        if(itemRect!=nullptr)
            m_scene->removeItem(itemRect);
    }
}


//Проигрывание видео
void sceneControl::updVideoPlay()
{

    if(!cap.isOpened() || !cap.read(frame2) || !cap.read(frame1))
    {
        timerUpdate->stop();
        return;
    }

    m_scene->clear();

    item = m_scene->addPixmap(videoCV::cvMatToQPixmap(frame1));

    //Обновление положения траектории
    if(!trackControl.isNull() && stateTrack)
    {
        QTime time = QTime::currentTime();
        emit updateTracker(frame1);
        m_scene->addRect(rect, QPen(QColor(Qt::green), 10));
    }
}

//обновление положения объекта в кадре
void sceneControl::updateRect(QRect newRect)
{
    rect = newRect;

}

void sceneControl::playVideo()
{
    timerUpdate->start();
}

void sceneControl::stopVideo()
{
    timerUpdate->stop();
}
