#include <QDebug>
#include <QApplication>
#include <QQmlApplicationEngine>
#include <algorithm>    // std::merge, std::sort
#include "generator.h"
#include "closestdistancealgorithm.h"
#include "datamodel.h"
#include "modelviewcontroller.h"
#include <QQmlContext>
#include <QtCharts/QScatterSeries>
#include <QtCharts/QLineSeries>

std::vector<QPointF> getSortedRandomVector(int numberOfPoints)
{
    std::vector<QPointF> vector;

    for(int i = 0u; i < numberOfPoints; ++i)
    {
        vector.push_back(Generator::generateRandomPair());
    }

    std::sort(vector.begin(), vector.end(), Generator::comparePoints);
    return vector;

}

int main(int argc, char *argv[])
{
    Q_UNUSED(argc);
    Q_UNUSED(argv);
    std::vector<QPointF> myVector;


    myVector = getSortedRandomVector(100);
    qDebug() << myVector.size();
    auto min = closestDistance::calculateClothestDistance(myVector);
    auto minOptimized = closestDistance::calculateClothestDistanceOptimized(myVector);
    qDebug() << "Closest Distance : " << min;
    qDebug() << "Closest Distance : " << minOptimized;

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

