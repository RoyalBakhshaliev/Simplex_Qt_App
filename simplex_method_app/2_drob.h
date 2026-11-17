#ifndef DROB_H
#define DROB_H

#include <QString>

class Drob {
private:
    long long chislitel;
    long long znamenatel;

    long long nod(long long a, long long b);
    void sokratit();

public:
    Drob();
    Drob(long long ch);
    Drob(long long ch, long long zn);
    Drob(double chislo);

    Drob operator+(const Drob& drugaya) const;
    Drob operator-(const Drob& drugaya) const;
    Drob operator*(const Drob& drugaya) const;
    Drob operator/(const Drob& drugaya) const;

    bool operator==(const Drob& drugaya) const;
    bool operator<(const Drob& drugaya) const;
    bool operator>(const Drob& drugaya) const;
    bool operator<=(const Drob& drugaya) const;

    QString toQStringDrob() const;
    QString toQStringDecimal() const;
    double toDouble() const;
};

#endif // DROB_H
