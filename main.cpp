#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <asyncimageprovider.h>
int main(int argc, char *argv[]) {
  QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

  QGuiApplication app(argc, argv);

  QQmlApplicationEngine engine;
  engine.addImageProvider("remote", new AsyncImageProvider);

  engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
  if (engine.rootObjects().isEmpty())
    return -1;

  return app.exec();
}
