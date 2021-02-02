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

std::vector<QPointF> Generator::getSortedRandomVector(int numberOfPoints)
{
    std::vector<QPointF> vector;

    for(int i = 0u; i < numberOfPoints; ++i)
    {
        vector.push_back(Generator::generateRandomPair());
    }

    std::sort(vector.begin(), vector.end(), Generator::comparePoints);
    return vector;
}

bool Generator::comparePointsY(const QPointF &i, const QPointF &j)
{
    return (i.y()<j.y());

}
