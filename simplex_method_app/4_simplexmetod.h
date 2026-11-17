#ifndef SIMPLEXMETOD_H
#define SIMPLEXMETOD_H

#include <QVector>
#include <QStringList>
#include <QString>
#include "drob.h"

struct SimplexShag {
    QVector<QVector<Drob>> matrica;
    QVector<int> tekBazis;
    int rStroka;
    int rStolbec;
    QString opisanie;
};

class SimplexMetod
{
private:
    int kolIshodPeremennih;
    int kolOgranicheniy;
    bool isMax;

    QVector<QVector<Drob>> tablica;
    QVector<int> bazis;
    QVector<SimplexShag> vsiShagi;
    void pererschitatTablicu(int razreshStroka, int razreshStolbec);

public:
    SimplexMetod();

    void inicializaciya(const QVector<Drob>& koeffFunkcii,
                        const QVector<QVector<Drob>>& matricaA,
                        const QStringList& znaki,
                        const QVector<Drob>& svobodChleni,
                        bool max);
    bool reshit();

    QVector<Drob> poluchitOptimalniyPlan() const;
    Drob poluchitOptimalnoeZnachenie() const;
    QVector<SimplexShag> poluchitShagi() const { return vsiShagi; }
};
#endif // SIMPLEXMETOD_H
