#include "poezdka.h"

Poezdka::Poezdka() {
    rasstoyanie = 0.0;
    rashod = 0.0;
    cenaTopliva = 0.0;
}

void Poezdka::setRasstoyanie(double r) {
    rasstoyanie = r;
}

void Poezdka::setRashod(double rash) {
    rashod = rash;
}

void Poezdka::setCenaTopliva(double c) {
    cenaTopliva = c;
}

double Poezdka::rasschitatLitry() const {
    if (rasstoyanie <= 0 || rashod <= 0) return 0.0;
    return (rasstoyanie * rashod) / 100.0;
}

double Poezdka::rasschitatStoimost() const {
    return rasschitatLitry() * cenaTopliva;
}
