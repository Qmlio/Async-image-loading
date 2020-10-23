#ifndef ASYNCIMAGERESPONSE_H
#define ASYNCIMAGERESPONSE_H

#include <QQuickImageResponse>
#include <QRunnable>
class AsyncImageResponse : public QQuickImageResponse, public QRunnable {
  Q_OBJECT
public:
  AsyncImageResponse(const QString &id, const QSize &requestedSize,
                     const QImage = QImage());
  ~AsyncImageResponse() override;
  QQuickTextureFactory *textureFactory() const override;
  QString errorString() const override;
  void run() override;

  QImage image() const;

  QByteArray imageData() const;

signals:
  void johns(QByteArray c);
  void cacheImage(QImage image);

protected:
  void fitTosize();

private:
  QString m_id;
  QByteArray m_imageData;
  QSize m_requestedSize;
  QImage m_image;
  QString m_Error;
  bool m_bIsCached;
  bool m_bCancelled;
};

#endif // ASYNCIMAGERESPONSE_H
