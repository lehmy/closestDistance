#include "generator.h"

bool Generator::comparePoints (const QPointF &i, const QPointF &j)
{
    return (i.x()<j.x());
}

QPointF Generator::generateRandomPair()
{
    std::uniform_real_distribution<> dist(0, 1);
    return QPointF(dist(*QRandomGenerator::global()),dist(*QRandomGenerator::global()));
}
