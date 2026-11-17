#include "drob.h"
#include <cmath>
#include <stdexcept>

long long Drob::nod(long long a, long long b) {
    while (b != 0) {
        long long temp = b;
        b = a % b;
        a = temp;
    }
    return std::abs(a);
}

void Drob::sokratit() {
    if (znamenatel == 0) return;
    long long g = nod(chislitel, znamenatel);
    chislitel /= g;
    znamenatel /= g;
    if (znamenatel < 0) {
        chislitel = -chislitel;
        znamenatel = -znamenatel;
    }
}

Drob::Drob() : chislitel(0), znamenatel(1) {}

Drob::Drob(long long ch) : chislitel(ch), znamenatel(1) {}

Drob::Drob(long long ch, long long zn) : chislitel(ch), znamenatel(zn) {
    if (znamenatel == 0) znamenatel = 1;
    sokratit();
}

Drob::Drob(double chislo) {
    if (std::abs(chislo) < 1e-9) {
        chislitel = 0;
        znamenatel = 1;
        return;
    }

    long long sign = (chislo < 0) ? -1 : 1;
    chislo = std::abs(chislo);

    double eps = 1e-6;
    double startChislo = chislo;
    long long n0 = std::floor(chislo);

    long long p0 = n0, q0 = 1;
    long long p1 = 1, q1 = 0;

    long long p_tek = p0;
    long long q_tek = q0;

    double ost = chislo - n0;
    int max_iter = 10;

    while (std::abs(startChislo - (double)p_tek / q_tek) > eps && max_iter > 0) {
        if (std::abs(ost) < eps) break;
        ost = 1.0 / ost;
        long long n = std::floor(ost);
        ost = ost - n;

        long long p_nov = n * p0 + p1;
        long long q_nov = n * q0 + q1;

        p1 = p0; q1 = q0;
        p0 = p_nov; q0 = q_nov;

        p_tek = p0;
        q_tek = q0;
        max_iter--;
    }

    chislitel = p_tek * sign;
    znamenatel = q_tek;
    sokratit();
}

Drob Drob::operator+(const Drob& drugaya) const {
    return Drob(chislitel * drugaya.znamenatel + drugaya.chislitel * znamenatel, znamenatel * drugaya.znamenatel);
}

Drob Drob::operator-(const Drob& drugaya) const {
    return Drob(chislitel * drugaya.znamenatel - drugaya.chislitel * znamenatel, znamenatel * drugaya.znamenatel);
}

Drob Drob::operator*(const Drob& drugaya) const {
    return Drob(chislitel * drugaya.chislitel, znamenatel * drugaya.znamenatel);
}

Drob Drob::operator/(const Drob& drugaya) const {
    return Drob(chislitel * drugaya.znamenatel, znamenatel * drugaya.chislitel);
}

bool Drob::operator==(const Drob& drugaya) const { return chislitel == drugaya.chislitel && znamenatel == drugaya.znamenatel; }
bool Drob::operator<(const Drob& drugaya) const { return this->toDouble() < drugaya.toDouble(); }
bool Drob::operator>(const Drob& drugaya) const { return this->toDouble() > drugaya.toDouble(); }
bool Drob::operator<=(const Drob& drugaya) const { return this->toDouble() <= drugaya.toDouble(); }

double Drob::toDouble() const { return (double)chislitel / znamenatel; }

QString Drob::toQStringDrob() const {
    if (znamenatel == 1) return QString::number(chislitel);
    return QString("%1/%2").arg(chislitel).arg(znamenatel);
}

QString Drob::toQStringDecimal() const {
    return QString::number(toDouble(), 'f', 2);
}
