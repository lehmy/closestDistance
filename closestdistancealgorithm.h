#ifndef CLOSESTDISTANCEALGORITHM_H
#define CLOSESTDISTANCEALGORITHM_H

#include <QPoint>
#include <vector>


namespace closestDistance
{

QPointF generateRandomPair();

bool comparePoints (const QPointF& i, const QPointF& j);

void print(std::vector<QPointF> const &input);

float calculateClothestDistance(const std::vector<QPointF>& list);

float calculateClothestDistanceOptimized(const std::vector<QPointF>& list);


}

#endif // CLOSESTDISTANCEALGORITHM_H
