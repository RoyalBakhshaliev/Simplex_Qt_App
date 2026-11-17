#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QComboBox>
#include <QTableWidgetItem>
#include <QVBoxLayout>

#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts/QValueAxis>
#include <QtCharts/QChart>

QT_CHARTS_USE_NAMESPACE

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , tekIndeksShaga(0)
{
    ui->setupUi(this);

    ui->spinPeremennie->setMinimum(2);
    ui->spinPeremennie->setMaximum(10);
    ui->spinOgranicheniya->setMinimum(1);
    ui->spinOgranicheniya->setMaximum(10);

    ui->comboKriteriy->clear();
    ui->comboKriteriy->addItems(QStringList() << "Максимизация (MAX)" << "Минимизация (MIN)");

    obnovitTablicuVvoda();
}
MainWindow::~MainWindow() {
    delete ui;
}
void MainWindow::on_spinPeremennie_valueChanged(int arg1) {
    Q_UNUSED(arg1);
    obnovitTablicuVvoda();
}
void MainWindow::on_spinOgranicheniya_valueChanged(int arg1) {
    Q_UNUSED(arg1);
    obnovitTablicuVvoda();
}
void MainWindow::obnovitTablicuVvoda() {
    int per = ui->spinPeremennie->value();
    int ogr = ui->spinOgranicheniya->value();

    ui->tableVvod->setColumnCount(per + 2);
    ui->tableVvod->setRowCount(ogr + 1);

    QStringList headers;
    for (int i = 1; i <= per; ++i) {
        headers << QString("X%1").arg(i);
    }
    headers << "Знак" << "B (Своб. член)";
    ui->tableVvod->setHorizontalHeaderLabels(headers);

    QStringList rowHeaders;
    for (int i = 1; i <= ogr; ++i) {
        rowHeaders << QString("Огр. %1").arg(i);
    }
    rowHeaders << "F(X) ->";
    ui->tableVvod->setVerticalHeaderLabels(rowHeaders);

    for (int i = 0; i < ui->tableVvod->rowCount(); ++i) {
        ui->tableVvod->removeCellWidget(i, per);
        ui->tableVvod->removeCellWidget(i, per + 1);
    }
    for (int i = 0; i < ogr; ++i) {
        QComboBox *comboZnak = new QComboBox();
        comboZnak->addItems(QStringList() << "<=" << ">=" << "=");
        ui->tableVvod->setCellWidget(i, per, comboZnak);
        ui->tableVvod->setItem(i, per + 1, new QTableWidgetItem(""));
    }
    ui->tableVvod->setItem(ogr, per, new QTableWidgetItem(""));
    ui->tableVvod->item(ogr, per)->setFlags(Qt::NoItemFlags);
    ui->tableVvod->setItem(ogr, per + 1, new QTableWidgetItem(""));
    ui->tableVvod->item(ogr, per + 1)->setFlags(Qt::NoItemFlags);

    ui->tableVvod->resizeColumnsToContents();
}
void MainWindow::pokazatShag(int indeks) {
    auto shagi = reshatel.poluchitShagi();
    if (indeks < 0 || indeks >= shagi.size()) return;

    const auto& shag = shagi[indeks];
    ui->lblOpisanie->setText(QString("Шаг %1 из %2\n%3").arg(indeks + 1).arg(shagi.size()).arg(shag.opisanie));

    int rows = shag.matrica.size();
    int cols = shag.matrica[0].size();
    ui->tableShag->setRowCount(rows);
    ui->tableShag->setColumnCount(cols);

    QStringList hLabels;
    for(int j = 0; j < cols - 1; ++j) {
        hLabels << QString("x%1").arg(j + 1);
    }
    hLabels << "RHS";
    ui->tableShag->setHorizontalHeaderLabels(hLabels);

    QStringList vLabels;
    for(int i = 0; i < rows - 1; ++i) {
        vLabels << QString("Базис s%1").arg(shag.tekBazis[i] + 1);
    }
    vLabels << "Индекс F";
    ui->tableShag->setVerticalHeaderLabels(vLabels);

    for(int i = 0; i < rows; ++i) {
        for(int j = 0; j < cols; ++j) {
            QTableWidgetItem *item = new QTableWidgetItem(shag.matrica[i][j].toQStringDrob());

            if (i == shag.rStroka && j == shag.rStolbec) {
                item->setBackground(QColor(255, 105, 180));
            } else if (i == shag.rStroka) {
                item->setBackground(QColor(255, 235, 156));
            } else if (j == shag.rStolbec) {
                item->setBackground(QColor(198, 239, 206));
            }
            ui->tableShag->setItem(i, j, item);
        }
    }
    ui->tableShag->resizeColumnsToContents();

    QLayoutItem *child;
    if(ui->chartContainer->layout()) {
        while ((child = ui->chartContainer->layout()->takeAt(0)) != nullptr) {
            delete child->widget();
            delete child;
        }
    } else {
        new QVBoxLayout(ui->chartContainer);
    }
    QChart *chart = new QChart();
    chart->setTitle("Геометрическая интерпретация (ОДР)");

    for (int i = 0; i < ui->spinOgranicheniya->value(); ++i) {
        QLineSeries *series = new QLineSeries();
        series->setName(QString("Огр. %1").arg(i + 1));

        bool ok1 = false, ok2 = false, ok3 = false;
        double a = 0.0, b = 0.0, c = 0.0;

        if(ui->tableVvod->item(i, 0)) a = ui->tableVvod->item(i, 0)->text().toDouble(&ok1);
        if(ui->tableVvod->item(i, 1)) b = ui->tableVvod->item(i, 1)->text().toDouble(&ok2);
        if(ui->tableVvod->item(i, ui->tableVvod->columnCount()-1)) c = ui->tableVvod->item(i, ui->tableVvod->columnCount()-1)->text().toDouble(&ok3);

        if(ok1 && ok2 && ok3) {
            if (b != 0) series->append(0, c / b);
            if (a != 0) series->append(c / a, 0);
            chart->addSeries(series);
        }
    }
    chart->createDefaultAxes();
    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    ui->chartContainer->layout()->addWidget(chartView);
}
void MainWindow::on_btnReshit_clicked() {
    int per = ui->spinPeremennie->value();
    int ogr = ui->spinOgranicheniya->value();

    QVector<Drob> koeffFunkcii;
    for (int j = 0; j < per; ++j) {
        if(ui->tableVvod->item(ogr, j)) {
            double val = ui->tableVvod->item(ogr, j)->text().toDouble();
            koeffFunkcii.append(Drob(static_cast<long long>(val)));
        } else {
            koeffFunkcii.append(Drob(0LL));
        }
    }

    QVector<QVector<Drob>> matricaA(ogr, QVector<Drob>(per));
    QStringList znaki;
    QVector<Drob> svobodChleni;

    for (int i = 0; i < ogr; ++i) {
        for (int j = 0; j < per; ++j) {
            if(ui->tableVvod->item(i, j)) {
                double val = ui->tableVvod->item(i, j)->text().toDouble();
                matricaA[i][j] = Drob(static_cast<long long>(val));
            }
        }
        QComboBox *combo = qobject_cast<QComboBox*>(ui->tableVvod->cellWidget(i, per));
        znaki.append(combo ? combo->currentText() : "<=");

        if(ui->tableVvod->item(i, per + 1)) {
            double val = ui->tableVvod->item(i, per + 1)->text().toDouble();
            svobodChleni.append(Drob(static_cast<long long>(val)));
        } else {
            svobodChleni.append(Drob(0LL));
        }
    }
    bool max = (ui->comboKriteriy->currentText().contains("MAX"));
    reshatel.inicializaciya(koeffFunkcii, matricaA, znaki, svobodChleni, max);
    reshatel.reshit();

    tekIndeksShaga = 0;
    pokazatShag(tekIndeksShaga);
}
void MainWindow::on_btnNazad_clicked() {
    if (tekIndeksShaga > 0) {
        tekIndeksShaga--;
        pokazatShag(tekIndeksShaga);
    }
}
void MainWindow::on_btnVpered_clicked() {
    if (tekIndeksShaga < reshatel.poluchitShagi().size() - 1) {
        tekIndeksShaga++;
        pokazatShag(tekIndeksShaga);
    }
}
