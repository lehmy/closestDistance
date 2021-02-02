#include <QDebug>
#include <QApplication>
#include <QQmlApplicationEngine>
#include <algorithm>    // std::merge, std::sort
#include <generator.h>
#include "closestdistancealgorithm.h"
#include "datamodel.h"
#include "modelviewcontroller.h"
#include <QQmlContext>


int main(int argc, char *argv[])
{
    Q_UNUSED(argc);
    Q_UNUSED(argv);

    std::vector<QPointF> myVector = Generator::getSortedRandomVector(1000);
    auto start = std::chrono::system_clock::now();
    auto min = closestDistance::calculateClothestDistance(myVector);
    auto end = std::chrono::system_clock::now();
    std::chrono::duration<double> duartionBruteForce = end-start;

    start = std::chrono::system_clock::now();
    auto minOptimized = closestDistance::calculateClothestDistanceOptimized(myVector);
    end = std::chrono::system_clock::now();
    std::chrono::duration<double> durationOptimized = end-start;

    qDebug() << "Closest Distance brute force: " << min << " " << "Duration: " << duartionBruteForce.count() << " s";
    qDebug() << "Closest Distance optimized: " << minOptimized << " " << "Duration: " << durationOptimized.count() << " s";

    if(min != minOptimized || (min < 0.0f))
    {
        // generate some debug output first
        closestDistance::print(myVector);
        Q_ASSERT(false);
    }

    QList<QPointF> myList;
    myList.reserve(myVector.size());
    std::copy(myVector.begin(), myVector.end(), std::back_inserter(myList));

    ModelViewController myController(myList);
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);


    QApplication  app(argc, argv);
    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);

    QQmlContext* context = engine.rootContext();

    context->setContextProperty("myController", &myController);
    engine.load(url);

    return app.exec();

}

