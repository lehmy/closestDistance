#include <QDebug>
#include <algorithm>    // std::merge, std::sort
#include "generator.h"

void print(std::vector<QPointF> const &input)
{
    for (auto it = input.cbegin(); it != input.cend(); it++)
    {
        qDebug() << *it << ' ';
    }
}

int main(int argc, char *argv[])
{
    Q_UNUSED(argc);
    Q_UNUSED(argv);


    std::vector<QPointF> myVector;

    for(int i = 0u; i < 100; ++i)
    {
        myVector.push_back(Generator::generateRandomPair());
    }
    std::sort(myVector.begin(), myVector.end(), Generator::comparePoints);
    print(myVector);

}

