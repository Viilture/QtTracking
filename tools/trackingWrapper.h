#ifndef TRACKINGCONTROL_H
#define TRACKINGCONTROL_H

#include <QObject>
#include <QRect>
#include <QDebug>
#include <QMessageBox>
#include <QMutex>
#include <exception>

#include <opencv2/tracking.hpp>
#include <opencv2/tracking/tracking_legacy.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>


//Алгоритмы поиска траекторий
enum typeTrack
{
    /*  KCF — это структура отслеживания, которая использует свойства
        циркулянтной матрицы для повышения скорости обработки.
        Этот метод отслеживания является реализацией
        Дж. Ф. Энрикес, Р. Касейро, П. Мартинс и Дж. Батиста.
        Использование циркулирующей структуры отслеживания путем обнаружения с ядрами.
        В материалах Европейской конференции по компьютерному зрению, 2012 г. */
    KCF = 1,

    /*  Алгоритм MIL обучает классификатор в режиме онлайн, чтобы отделить объект от фона.
        Многоэкземплярное обучение позволяет избежать проблемы дрейфа для надежного отслеживания. Реализация основана на
        Борис Бабенко, Мин-Сюань Ян и Серж Белонги. Визуальное отслеживание с многократным онлайн-обучением.
        В Computer Vision and Pattern Recognition, 2009. CVPR 2009. Конференция IEEE, стр. 983–990. ИИЭР, 2009. */
    MIL = 2,

    /*  трекер GOTURN (общее отслеживание объектов с использованием регрессионных сетей)
        GOTURN ( [100] ) — это своего рода трекеры, основанные на сверточных нейронных сетях (CNN).
        Используя все преимущества трекеров CNN, GOTURN работает намного быстрее благодаря офлайн-обучению
        без тонкой настройки онлайн. Трекер GOTURN решает проблему отслеживания одной цели: при наличии метки
        ограничивающей рамки объекта в первом кадре видео мы отслеживаем этот объект в остальной части видео.
        ПРИМЕЧАНИЕ. Текущий метод GOTURN не обрабатывает окклюзии; однако он довольно устойчив к изменениям точки обзора,
        изменениям освещения и деформации. Входными данными GOTURN являются два патча RGB, представляющие патчи Target и Search,
        размер которых изменен до 227x227. Выходные данные GOTURN представляют собой прогнозируемые координаты ограничивающей рамки
         относительно системы координат поля поиска в формате X1, Y1, X2, Y2. Оригинал статьи здесь:http://davheld.github.io/GOTURN/GOTURN.pdf
        При условии реализации оригинальных авторов: https://github.com/davheld/GOTURN#train-the-tracker Реализация обучающего алгоритма
        вынесена здесь отдельно в связи с Сторонние зависимости: https://github.com/Auron-X/GOTURN_Training_Toolkit Архитектура GOTURN
        goturn.prototxt и обученная модель
        goturn.caffemodel доступны в репозитории opencv_extra GitHub. */
    GOTURN = 3,

    /*  Реализация основана на Rafal Mantiuk, Karol Myszkowski, and Hans-Peter Seidel.
        A perceptual framework for contrast processing of high dynamic range images. ACM Transactions on
        Applied Perception (TAP), 3(3):286–308, 2006.
        Дискриминативном корреляционном фильтре с канальной и пространственной надежностью . */
    CSRT = 4,

    DaSiamRPN = 5,

    /*  Nano tracker — это сверхлегкое отслеживание объектов на основе dnn.
        Нано-трекер намного быстрее и очень легкий благодаря специальной структуре модели, общий размер модели составляет около 1,9 МБ.
        Нано-трекеру нужны две модели: одна для извлечения признаков (основная часть) и другая для локализации (шея).
        Ссылка для скачивания модели: https://github.com/HonglinChu/SiamTrackers/tree/master/NanoTrack/models/nanotrackv2
        Исходный репозиторий находится здесь:
        https://github.com/HonglinChu/NanoTrack Автор: HongLinChu, 16284 6434 5@qq . ком */
    Nano = 6,
};

namespace videoCV {

class TrackingWrapper: public QObject
{
    Q_OBJECT
public:
    explicit TrackingWrapper(typeTrack newType);
    virtual ~TrackingWrapper();

private:

    cv::Rect curRect = cv::Rect(0, 0, 1, 1);
    cv::Mat*  curMat = nullptr;

    cv::Ptr<cv::Tracker> tracker = nullptr;

    QMutex mutex;

public slots:

    //Обновляем значение текущей картинки и выбранного места поиска у трекера
    void initTracker(cv::Mat newImage, QRect newRectzz);

    void updateTracker(cv::Mat newImage);

    //Изменяем тип трекера
    void setTracker(typeTrack newType);

signals:

    void updateRect(QRect newRect);
};
}
#endif // TRACKINGCONTROL_H
