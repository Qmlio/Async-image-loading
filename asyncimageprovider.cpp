#include "asyncimageprovider.h"
#include "asyncimageresponse.h"
#include <QDebug>
#include <QImage>

QQuickImageResponse *
AsyncImageProvider::requestImageResponse(const QString &id,
                                         const QSize &requestedSize) {
  AsyncImageResponse *response = nullptr;
  if (!m_imageCache.contains(id)) {

    // image is not yet cached
    response = new AsyncImageResponse(id, requestedSize);
    m_threadPool.start(response);

    QObject::connect(response, &AsyncImageResponse::cacheImage,
                     [=](QImage v) { m_imageCache.insert(id, new QImage(v)); });

  } else {
    // image is already cached
    response = new AsyncImageResponse(id, requestedSize, *m_imageCache[id]);
    m_threadPool.start(response);
  }
  qDebug() << "my response is   " << response;

  return response;
}

AsyncImageProvider::AsyncImageProvider() {
  // tried increasing maximum thread count but still no hope
  m_threadPool.setMaxThreadCount(100);
  qDebug() << "creting prigicefefe  " << this;
}

AsyncImageProvider::~AsyncImageProvider() {
  qDebug() << "destroying provider ";
}
