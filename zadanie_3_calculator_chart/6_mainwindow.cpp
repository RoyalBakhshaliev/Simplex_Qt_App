#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QLineSeries>
#include <QChart>
#include <QChartView>
#include <QValueAxis>

QT_CHARTS_USE_NAMESPACE

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_knopkaPlyus_clicked() {
    double a = ui->vvodChisla1->text().toDouble();
    double b = ui->vvodChisla2->text().toDouble();

    double resultat = moyKalkulyator.summirovat(a, b);

    this->setWindowTitle("Результат: " + QString::number(resultat));
}

void MainWindow::on_knopkaGrafika_clicked() {
    QList<double> dannie = moyKalkulyator.poluchitIstoriyu();

    if (dannie.isEmpty()) {
        QMessageBox::warning(this, "Предупреждение", "Сначала сложите числа!");
        return;
    }

    QLineSeries *seriya = new QLineSeries();
    seriya->setName("Сумма");
    seriya->setColor(QColor("red"));

    for (int i = 0; i < dannie.size(); ++i) {
        seriya->append(i + 1, dannie[i]);
    }

    QChart *grafik = new QChart();
    grafik->addSeries(seriya);
    grafik->setTitle("График Суммы");

    QValueAxis *osX = new QValueAxis();
    osX->setTitleText("Номер Измерения");
    osX->setRange(1, dannie.size());
    osX->setTickCount(dannie.size());
    osX->setLabelFormat("%d");
    grafik->addAxis(osX, Qt::AlignBottom);
    seriya->attachAxis(osX);

    QValueAxis *osY = new QValueAxis();
    osY->setTitleText("Суммы");
    grafik->addAxis(osY, Qt::AlignLeft);
    seriya->attachAxis(osY);

    QChartView *oknoGrafika = new QChartView(grafik);
    oknoGrafika->setWindowTitle("График полученных сумм");
    oknoGrafika->resize(600, 450);
    oknoGrafika->setAttribute(Qt::WA_DeleteOnClose);
    oknoGrafika->show();
}
