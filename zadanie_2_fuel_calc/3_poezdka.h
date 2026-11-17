#ifndef POEZDKA_H
#define POEZDKA_H

class Poezdka {
private:
    double rasstoyanie;
    double rashod;
    double cenaTopliva;

public:
    Poezdka();

    void setRasstoyanie(double r);
    void setRashod(double rash);
    void setCenaTopliva(double c);

    double rasschitatLitry() const;
    double rasschitatStoimost() const;
};

#endif // POEZDKA_H
