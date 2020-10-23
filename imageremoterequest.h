#ifndef IMAGEREMOTEREQUEST_H
#define IMAGEREMOTEREQUEST_H

#include <QByteArray>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QObject>
#include <QUrl>
class ImageRemoteRequest : public QObject {
  Q_OBJECT
public:
  explicit ImageRemoteRequest(const QUrl &url, QObject *parent = nullptr);
  ~ImageRemoteRequest();
  static void wait(const int interval = 1500);
  void load();
  bool ready() const;
  QByteArray imageData() const;
protected slots:
  void processReply();
  void rentry();
signals:
  void scheduleDelete();

private:
  QNetworkAccessManager *manager;
  QNetworkReply *reply;
  QByteArray m_imageData;
  QUrl m_url;
  bool m_ready;
};

#endif // IMAGEREMOTEREQUEST_H
