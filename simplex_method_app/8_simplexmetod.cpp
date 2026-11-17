#include "simplexmetod.h"

SimplexMetod::SimplexMetod() : kolIshodPeremennih(0), kolOgranicheniy(0), isMax(true) {}

void SimplexMetod::inicializaciya(const QVector<Drob>& koeffFunkcii,
                                  const QVector<QVector<Drob>>& matricaA,
                                  const QStringList& znaki,
                                  const QVector<Drob>& svobodChleni,
                                  bool max)
{
    kolIshodPeremennih = koeffFunkcii.size();
    kolOgranicheniy = matricaA.size();
    isMax = max;
    vsiShagi.clear();
    bazis.clear();

    int dopPeremennih = kolOgranicheniy;
    int obsheeKolPeremennih = kolIshodPeremennih + dopPeremennih;

    tablica.resize(kolOgranicheniy + 1);
    tablica.fill(QVector<Drob>(obsheeKolPeremennih + 1, Drob()));
    bazis.resize(kolOgranicheniy);

    for (int i = 0; i < kolOgranicheniy; ++i) {
        Drob znakMnojitel(1LL);
        if (svobodChleni[i] < Drob(0LL)) {
            znakMnojitel = Drob(-1LL);
        }

        for (int j = 0; j < kolIshodPeremennih; ++j) {
            tablica[i][j] = matricaA[i][j] * znakMnojitel;
        }

        tablica[i][obsheeKolPeremennih] = svobodChleni[i] * znakMnojitel;

        QString tekZnak = znaki[i];
        if (znakMnojitel == Drob(-1LL)) {
            if (tekZnak == "<=") tekZnak = ">=";
            else if (tekZnak == ">=") tekZnak = "<=";
        }

        int indeksDopPeremennoy = kolIshodPeremennih + i;
        if (tekZnak == "<=" || tekZnak == "=") {
            tablica[i][indeksDopPeremennoy] = Drob(1LL);
        } else {
            tablica[i][indeksDopPeremennoy] = Drob(-1LL);
        }

        bazis[i] = indeksDopPeremennoy;
    }

    for (int j = 0; j < kolIshodPeremennih; ++j) {
        if (isMax) {
            tablica[kolOgranicheniy][j] = Drob(0LL) - koeffFunkcii[j];
        } else {
            tablica[kolOgranicheniy][j] = koeffFunkcii[j];
        }
    }
    tablica[kolOgranicheniy][obsheeKolPeremennih] = Drob(0LL);

    SimplexShag nShag;
    nShag.matrica = tablica;
    nShag.tekBazis = bazis;
    nShag.rStroka = -1;
    nShag.rStolbec = -1;
    nShag.opisanie = "Построена начальная симплекс-таблица. Искусственных переменных нет.";
    vsiShagi.append(nShag);
}

bool SimplexMetod::reshit() {
    int obsheeKolPeremennih = tablica[0].size() - 1;
    int iteraciya = 0;

    while (iteraciya < 50) {
        iteraciya++;

        int razreshStolbec = -1;
        Drob ekstremalniyKoeff(0LL);

        for (int j = 0; j < obsheeKolPeremennih; ++j) {
            if (tablica[kolOgranicheniy][j] < ekstremalniyKoeff) {
                ekstremalniyKoeff = tablica[kolOgranicheniy][j];
                razreshStolbec = j;
            }
        }

        if (razreshStolbec == -1) {
            SimplexShag optShag;
            optShag.matrica = tablica;
            optShag.tekBazis = bazis;
            optShag.rStroka = -1;
            optShag.rStolbec = -1;
            optShag.opisanie = "Оптимальный план успешно найден! Критерий оптимальности выполнен.";
            vsiShagi.append(optShag);
            return true;
        }

        int razreshStroka = -1;
        Drob minOtnoshenie;
        bool perviyFlag = true;

        for (int i = 0; i < kolOgranicheniy; ++i) {
            if (tablica[i][razreshStolbec] > Drob(0LL)) {
                Drob tekOtnoshenie = tablica[i][obsheeKolPeremennih] / tablica[i][razreshStolbec];
                if (perviyFlag || tekOtnoshenie < minOtnoshenie) {
                    minOtnoshenie = tekOtnoshenie;
                    razreshStroka = i;
                    perviyFlag = false;
                }
            }
        }

        if (razreshStroka == -1) {
            SimplexShag errShag;
            errShag.matrica = tablica;
            errShag.tekBazis = bazis;
            errShag.rStroka = -1;
            errShag.rStolbec = -1;
            errShag.opisanie = "Ошибка: Задача не имеет решения. Функция не ограничена!";
            vsiShagi.append(errShag);
            return false;
        }

        vsiShagi.last().rStroka = razreshStroka;
        vsiShagi.last().rStolbec = razreshStolbec;
        vsiShagi.last().opisanie += QString(" Ведущий столбец: x%1, ведущая строка: %2 (базис s%3), ведущий элемент: %4.")
                                        .arg(razreshStolbec + 1)
                                        .arg(razreshStroka + 1)
                                        .arg(bazis[razreshStroka] + 1)
                                        .arg(tablica[razreshStroka][razreshStolbec].toQStringDrob());

        bazis[razreshStroka] = razreshStolbec;
        pererschitatTablicu(razreshStroka, razreshStolbec);

        SimplexShag sledShag;
        sledShag.matrica = tablica;
        sledShag.tekBazis = bazis;
        sledShag.rStroka = -1;
        sledShag.rStolbec = -1;
        sledShag.opisanie = QString("Шаг %1 выполнен. Таблица пересчитана.").arg(iteraciya);
        vsiShagi.append(sledShag);
    }
    return false;
}

void SimplexMetod::pererschitatTablicu(int razreshStroka, int razreshStolbec) {
    int obsheeKolPeremennih = tablica[0].size() - 1;
    Drob razreshElement = tablica[razreshStroka][razreshStolbec];

    for (int j = 0; j <= obsheeKolPeremennih; ++j) {
        tablica[razreshStroka][j] = tablica[razreshStroka][j] / razreshElement;
    }

    for (int i = 0; i <= kolOgranicheniy; ++i) {
        if (i != razreshStroka) {
            Drob mnojitel = tablica[i][razreshStolbec];
            for (int j = 0; j <= obsheeKolPeremennih; ++j) {
                tablica[i][j] = tablica[i][j] - (mnojitel * tablica[razreshStroka][j]);
            }
        }
    }
}

QVector<Drob> SimplexMetod::poluchitOptimalniyPlan() const {
    QVector<Drob> plan(kolIshodPeremennih, Drob(0LL));
    int obsheeKolPeremennih = tablica[0].size() - 1;
    for (int i = 0; i < kolOgranicheniy; ++i) {
        if (bazis[i] < kolIshodPeremennih) {
            plan[bazis[i]] = tablica[i][obsheeKolPeremennih];
        }
    }
    return plan;
}

Drob SimplexMetod::poluchitOptimalnoeZnachenie() const {
    int obsheeKolPeremennih = tablica[0].size() - 1;
    Drob rez = tablica[kolOgranicheniy][obsheeKolPeremennih];
    if (isMax) return rez;
    else return Drob(0LL) - rez;
}
