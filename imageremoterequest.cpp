#include "imageremoterequest.h"
#include <QEventLoop>
#include <QGuiApplication>
#include <QNetworkReply>
#include <QTimer>
ImageRemoteRequest::ImageRemoteRequest(const QUrl &url, QObject *parent)
    : QObject(parent) {
  this->manager = new QNetworkAccessManager(this);
  this->m_url = url;

  m_ready = false;
  connect(QCoreApplication::instance(), &QCoreApplication::aboutToQuit, [=] {
    qDebug() << " ---- 000===    is abourn tos  quicjkgr  ";
    this->m_ready = true;
  });
}

ImageRemoteRequest::~ImageRemoteRequest() {
  qDebug() << "deleting  remote image  " << this;
}

void ImageRemoteRequest::wait(const int interval) {
  QEventLoop loop;
  QTimer::singleShot(interval, &loop, &QEventLoop::quit);
  loop.exec();
}

void ImageRemoteRequest::load() {

  if (m_url.isValid()) {
    reply = manager->get(QNetworkRequest(m_url));
    connect(reply, &QNetworkReply::finished, this,
            &ImageRemoteRequest::processReply);
  }
}

bool ImageRemoteRequest::ready() const { return this->m_ready; }

QByteArray ImageRemoteRequest::imageData() const { return this->m_imageData; }

void ImageRemoteRequest::rentry() {
  if (!m_ready) {
    wait();
    load();
  }
}

void ImageRemoteRequest::processReply() {
  if (reply) {

    switch (reply->error()) {
    case QNetworkReply::NoError: {

      const QVariant redirectionTarget =
          reply->attribute(QNetworkRequest::RedirectionTargetAttribute);

      if (!redirectionTarget.isNull()) {
        qDebug() << "has redirect ";
        const QUrl redirectedUrl = m_url.resolved(redirectionTarget.toUrl());
        m_url = redirectedUrl;

        rentry();
      } else {
        m_ready = true;
        m_imageData = reply->readAll();
      }
      break;
    }
    case QNetworkReply::TimeoutError: {
      qWarning() << reply->errorString();

      rentry();
      break;
    }
    case QNetworkReply::HostNotFoundError: {
      qWarning() << reply->errorString();

      rentry();
      break;
    }
    case QNetworkReply::UnknownNetworkError: {
      qWarning() << reply->errorString();
      rentry();
      break;
    }
    }
  }
}
