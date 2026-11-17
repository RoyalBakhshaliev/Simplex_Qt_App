#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "kalkulyator.h"

#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QValueAxis>
#include <QtCharts/QChart>
#include <QSplitter>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

QT_CHARTS_USE_NAMESPACE

    class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_knopkaPlyus_clicked();
    void on_knopkaGrafika_clicked();

private:
    Ui::MainWindow *ui;
    Kalkulyator moyKalkulyator;
};

#endif // MAINWINDOW_H
kalkulytor.cpp:#include "kalkulyator.h"

Kalkulyator::Kalkulyator() {}

double Kalkulyator::summirovat(double a, double b) {
    double summa = a + b;
    istoriyaSumm.append(summa);
    return summa;
}

QList<double> Kalkulyator::poluchitIstoriyu() const {
    return istoriyaSumm;
}
