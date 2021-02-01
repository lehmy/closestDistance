#include "closestdistancealgorithm.h"
#include <iostream>
#include <QRandomGenerator>
#include <random>
#include <QDebug>
#include <algorithm>    // std::merge, std::sort
#include <QPoint>

//**********************************************************************
// Helper declaration
//**********************************************************************

static float calculateClothestDistanceBetween(const QPointF& p1, const std::vector<QPointF> &list);

static float distance(const QPointF& a, const QPointF& b);

//**********************************************************************
// Module implementation
//**********************************************************************

void closestDistance::print(std::vector<QPointF> const &input)
{
    for (auto it = input.cbegin(); it != input.cend(); it++)
    {
        qDebug() << *it << ' ';
    }
}

float closestDistance::calculateClothestDistance(const std::vector<QPointF> &list)
{
    auto first = list.cbegin() + 1;
    auto last = list.cend();

    std::vector<QPointF> vec(first, last);

    return calculateClothestDistanceBetween(list.at(0), vec);
}

float closestDistance::calculateClothestDistanceOptimized(const std::vector<QPointF>& list)
{
    if(list.size() <= 4)
    {
        return calculateClothestDistance(list);
    }

    auto first = list.cbegin();
    auto mid = list.cbegin() + list.size()/2;
    auto last = list.cend();
    auto leftIndex = 0;
    auto rightBound = mid;

    std::vector<QPointF> vecA(first, mid);
    std::vector<QPointF> vecB(mid, last);
    auto minDistance = std::min(calculateClothestDistanceOptimized(vecA),calculateClothestDistanceOptimized(vecB));

    for(int i = 1; i < (int)vecA.size() && (std::abs(vecA.at(vecA.size() - i - 1).x() - (*mid).x()) < minDistance); ++i)
    {
        leftIndex = i;
    }

    for (auto it = mid; it != list.cend() && ((*it).x() - (*mid).x() < minDistance); ++it)
    {
        rightBound = it + 1;
    }

    auto leftBound = mid- leftIndex - 1;
    std::vector<QPointF> vecC(leftBound, rightBound);

    if(vecC.size() >= 2)
    {
        minDistance = std::min(minDistance,calculateClothestDistance(vecC));
    }

    return minDistance;
}

//**********************************************************************
// Helper implementation
//**********************************************************************

float distance(const QPointF& a, const QPointF& b)
{
    return std::sqrt(std::pow((a.x() - b.x()),2) + std::pow((a.y() - b.y()),2));
}

float calculateClothestDistanceBetween(const QPointF& p1, const std::vector<QPointF> &list)
{
    auto d = distance(p1, list.at(0));

    for (auto it = list.begin() + 1 ; it != list.end(); ++it)
    {
        d = std::min(d,distance(p1,*it));
    }

    if(list.size() > 2)
    {
        auto first = list.cbegin() + 1;
        auto last = list.cend();

        std::vector<QPointF> vec(first, last);
        d =  std::min(d,calculateClothestDistanceBetween(list.at(0), vec));
    }
    else if(list.size() == 2)
    {
        d = std::min(d, distance(list.at(0), list.at(1)));
    }

    return d;
}
