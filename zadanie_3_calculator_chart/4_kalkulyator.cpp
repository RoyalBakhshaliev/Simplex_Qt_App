#include "kalkulyator.h"

Kalkulyator::Kalkulyator() {}

double Kalkulyator::summirovat(double a, double b) {
    double summa = a + b;
    istoriyaSumm.append(summa);
    return summa;
}

QList<double> Kalkulyator::poluchitIstoriyu() const {
    return istoriyaSumm;
}
