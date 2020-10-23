#ifndef ASYNCIMAGEPROVIDER_H
#define ASYNCIMAGEPROVIDER_H
#include "asyncimageresponse.h"
#include <QCache>
#include <QPixmapCache>
#include <QQuickAsyncImageProvider>
#include <QThreadPool>
class AsyncImageProvider : public QQuickAsyncImageProvider {
public:
  QQuickImageResponse *
  requestImageResponse(const QString &id, const QSize &requestedSize) override;

  AsyncImageProvider();
  ~AsyncImageProvider() override;

private:
  QThreadPool m_threadPool;
  QCache<QString, QImage> m_imageCache;
  QCache<QString, int> m;
  QPixmapCache k;
  QCache<QString, QByteArray> m_imageDatas;
};

#endif // ASYNCIMAGEPROVIDER_H
