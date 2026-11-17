#ifndef KALKULYATOR_H
#define KALKULYATOR_H

#include <QList>

class Kalkulyator {
private:
    QList<double> istoriyaSumm;

public:
    Kalkulyator();

    double summirovat(double a, double b);

    QList<double> poluchitIstoriyu() const;
};

#endif // KALKULYATOR_H
