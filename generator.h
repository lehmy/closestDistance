#ifndef GENERATOR_H
#define GENERATOR_H

#include <QPoint>
#include <QRandomGenerator>
#include <random>

namespace Generator {

QPointF generateRandomPair();

bool comparePoints (const QPointF& i, const QPointF& j);

bool comparePointsY (const QPointF& i, const QPointF& j);

std::vector<QPointF> getSortedRandomVector(int numberOfPoints);

}

#endif // GENERATOR_H
