#include "trackingWrapper.h"

namespace videoCV {
//класс трекеров
TrackingWrapper::TrackingWrapper(typeTrack newType)
{
    setTracker(newType);
}

TrackingWrapper::~TrackingWrapper()
{

}

// Метод `initTracker()` принимает два аргумента: новое изображение (`newImage`) и
// прямоугольную область (`newRect`), в которой нужно искать объект.
// Если один из этих аргументов пустой, то метод возвращает управление без выполнения каких-либо действий.
void TrackingWrapper::setTracker(typeTrack newType)
{
    QMutexLocker locker(&mutex);
    //Устанавливаем новый тип трекера
    switch (newType)
    {
    case typeTrack::KCF:       {tracker = cv::TrackerKCF::create();        break;}
    case typeTrack::MIL:       {tracker = cv::TrackerMIL::create();        break;}
    case typeTrack::GOTURN:    {tracker = cv::TrackerGOTURN::create();     break;}
    case typeTrack::CSRT:      {tracker = cv::TrackerCSRT::create();       break;}
    case typeTrack::DaSiamRPN: {tracker = cv::TrackerDaSiamRPN::create();  break;}
    case typeTrack::Nano:      {tracker = cv::TrackerNano::create();       break;}

    default: {break;}
    }

    qDebug() << 1;
    if(curMat != nullptr)
    {
        try
        {
            tracker->init(*curMat, curRect);

        }
        catch (std::exception& e)
        {
                std::cout << "Произошло исключение: " << e.what() << std::endl;
                mutex.lock();
        }
    }
    qDebug() << 2;
}

// Метод `initTracker()` также обновляет значение поля `curRect`,
// используя координаты и размеры прямоугольной области из аргумента `newRect`.
// Затем метод инициализирует трекер `tracker` с помощью метода `init()` и передает ему
// новое изображение и прямоугольную область, в которой нужно искать объект. Если в процессе
// инициализации происходит исключение, то метод выводит диалоговое окно с описанием ошибки.
void TrackingWrapper::initTracker(cv::Mat newImage, QRect newRect)
{
    QMutexLocker locker(&mutex);

    if(newImage.empty() || newRect.isEmpty() || tracker.empty()) return;
    curMat = &newImage;
    curRect.x = newRect.x();
    curRect.y = newRect.y();
    curRect.width = newRect.width();
    curRect.height = newRect.height();

    try
    {
        tracker->init(*curMat, curRect);

    }
    catch (const std::exception& e)
    {
        // обработка исключения
        QMessageBox::critical(nullptr, tr("Error"), QString("Error: %1").arg(e.what()));
        return;
    }
}

// Метод `updateTracker()` принимает новое изображение (`newImage`) и
// обновляет значение поля `curRect`, используя метод `update()` трекера `tracker`.
// Если в процессе обновления происходит исключение, то метод выводит диалоговое окно с описанием ошибки.
void TrackingWrapper::updateTracker(cv::Mat newImage)
{
    QMutexLocker locker(&mutex);

    if(newImage.empty() || tracker.empty()) return;
    curMat = &newImage;

    if(tracker.empty()) return;

    try
    {
        tracker->update(*curMat, curRect);

    }
    catch (const std::exception& e)
    {
        // обработка исключения
        QMessageBox::critical(nullptr, tr("Error"), QString("Error: %1").arg(e.what()));
        return;
    }

    emit updateRect(QRect(curRect.x, curRect.y, curRect.width, curRect.height));
}

}
