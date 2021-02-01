#ifndef GENERATOR_H
#define GENERATOR_H

#include <QPoint>
#include <QRandomGenerator>
#include <random>

namespace Generator {

QPointF generateRandomPair();

bool comparePoints (const QPointF& i, const QPointF& j);

}

#endif // GENERATOR_H
