#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <QImage>
#include <QPixmap>
#include <QDebug>
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/stitching.hpp"

namespace videoCV {

QImage  cvMatToQImage( const cv::Mat &inMat );
QPixmap cvMatToQPixmap( const cv::Mat &inMat );
cv::Mat QImageToCvMat( const QImage &inImage, bool inCloneImageData);
cv::Mat QPixmapToCvMat( const QPixmap &inPixmap, bool inCloneImageData);


}

#endif // TRANSFORM_H
