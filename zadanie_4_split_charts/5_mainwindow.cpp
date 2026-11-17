#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>

using namespace QtCharts;

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

    double rezultat = moyKalkulyator.summirovat(a, b);

    this->setWindowTitle("Результат: " + QString::number(rezultat));
}

void MainWindow::on_knopkaGrafika_clicked() {
    QList<double> dannie = moyKalkulyator.poluchitIstoriyu();

    if (dannie.isEmpty()) {
        QMessageBox::warning(this, "Предупреждение", "Сначала сложите числа!");
        return;
    }

    QLineSeries *seriyaLiniya = new QLineSeries();
    seriyaLiniya->setName("Сумма");
    seriyaLiniya->setColor(QColor("red"));

    for (int i = 0; i < dannie.size(); ++i) {
        seriyaLiniya->append(i + 1, dannie[i]);
    }

    QChart *grafikLiniya = new QChart();
    grafikLiniya->addSeries(seriyaLiniya);
    grafikLiniya->setTitle("График Суммы");

    QValueAxis *axisX = new QValueAxis();
    axisX->setTitleText("Номер Измерения");
    axisX->setRange(1, dannie.size());
    axisX->setTickCount(dannie.size());
    axisX->setLabelFormat("%d");

    QValueAxis *axisY = new QValueAxis();
    axisY->setTitleText("Суммы");

    grafikLiniya->addAxis(axisX, Qt::AlignBottom);
    seriyaLiniya->attachAxis(axisX);
    grafikLiniya->addAxis(axisY, Qt::AlignLeft);
    seriyaLiniya->attachAxis(axisY);

    QChartView *vidLiniya = new QChartView(grafikLiniya);
    vidLiniya->setRenderHint(QPainter::Antialiasing);

    QBarSet *barSet = new QBarSet("Суммы");
    barSet->setColor(QColor("red"));
    for (double value : dannie) {
        *barSet << value;
    }

    QBarSeries *barSeries = new QBarSeries();
    barSeries->append(barSet);

    QChart *barChart = new QChart();
    barChart->addSeries(barSeries);
    barChart->setTitle("Столбчатая диаграмма сумм");

    QStringList categories;
    for (int i = 1; i <= dannie.size(); ++i) {
        categories << QString::number(i);
    }

    QBarCategoryAxis *barAxisX = new QBarCategoryAxis();
    barAxisX->append(categories);
    barAxisX->setTitleText("Номер измерения");

    QValueAxis *barAxisY = new QValueAxis();
    barAxisY->setTitleText("Суммы");

    barChart->addAxis(barAxisX, Qt::AlignBottom);
    barSeries->attachAxis(barAxisX);
    barChart->addAxis(barAxisY, Qt::AlignLeft);
    barSeries->attachAxis(barAxisY);

    QChartView *vidStolbci = new QChartView(barChart);
    vidStolbci->setRenderHint(QPainter::Antialiasing);

    QSplitter *splitter = new QSplitter(Qt::Horizontal);
    splitter->addWidget(vidLiniya);
    splitter->addWidget(vidStolbci);

    splitter->resize(1400, 707);
    splitter->setWindowTitle("График и столбчатая диаграмма результатов");
    splitter->show();
}
