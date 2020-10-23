
/*
Async image provider MCVE
The problem
QQuickImageResponse::textureFactory is not called as expected.
*/

#include "asyncimageresponse.h"
#include <QCoreApplication>
#include <QDebug>
#include <QImage>
#include <QThread>
#include <imageremoterequest.h>
AsyncImageResponse::AsyncImageResponse(const QString &id,
                                       const QSize &requestedSize,
                                       const QImage img) {
  m_id = id;
  m_requestedSize = requestedSize;
  m_Error = "";
  setAutoDelete(false);
  m_bIsCached = !img.isNull();

  if (this->m_bIsCached) {
    if (m_requestedSize.isValid()) {
      m_requestedSize = QSize(img.width(), img.height());
    }

    m_image = img.scaled(requestedSize, Qt::KeepAspectRatioByExpanding,
                         Qt::SmoothTransformation);
  }
  m_bCancelled = false;

  // prevent thread from running while the app is closed
  connect(QCoreApplication::instance(), &QCoreApplication::aboutToQuit,
          [=] { m_bCancelled = true; });
}

AsyncImageResponse::~AsyncImageResponse() {
  qDebug() << "destroying image Response ";
}

// I think this is the function causing the problem.
// According to the documentation, this function is called when the job is
// finished and the QQuickImageResponse::errorString() returns an empty string.
QQuickTextureFactory *AsyncImageResponse::textureFactory() const {

  qDebug() << "returnif fatoryr  ";
  return QQuickTextureFactory::textureFactoryForImage(m_image);
}

// Forced QQuickImageResponse::errorString to return an empty string
QString AsyncImageResponse::errorString() const { return ""; }

void AsyncImageResponse::run() {

  // check if this image is cached to prevent unnecessary network calls
  if (!m_bIsCached) {

    QSharedPointer<ImageRemoteRequest> imageRemoteRequest(
        new ImageRemoteRequest(QUrl(m_id)));
    imageRemoteRequest->load();

    while (!imageRemoteRequest->ready()) {

      if (m_bCancelled) {

        break;
      }
      ImageRemoteRequest::wait();
    }
    if (!imageRemoteRequest->imageData().isEmpty()) {
      m_image.loadFromData(imageRemoteRequest->imageData());
      emit cacheImage(m_image);
    }

    fitTosize();
  }

  emit finished();
}

void AsyncImageResponse::fitTosize() {
  if (m_requestedSize.isValid()) {
    m_requestedSize = QSize(m_image.width(), m_image.height());
  }
  if (!m_image.isNull())
    m_image = m_image.scaled(m_requestedSize, Qt::KeepAspectRatioByExpanding,
                             Qt::SmoothTransformation);
}

QByteArray AsyncImageResponse::imageData() const { return m_imageData; }

QImage AsyncImageResponse::image() const { return m_image; }
