#include "mainwindow.h"
#include <QLabel>
#include <QLineEdit>
#include <QSpinBox>
#include <QPushButton>
#include <QTableWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    QWidget* centralniyVidzhet = new QWidget;
    setCentralWidget(centralniyVidzhet);
    QHBoxLayout* glavnyMaket = new QHBoxLayout;
    centralniyVidzhet->setLayout(glavnyMaket);

    tablica = new QTableWidget;
    tablica->setColumnCount(2);
    tablica->setHorizontalHeaderLabels(QStringList() << "Имя" << "Возраст");
    glavnyMaket->addWidget(tablica);

    QVBoxLayout* vertikalnyMaket = new QVBoxLayout;
    glavnyMaket->addLayout(vertikalnyMaket);

    vertikalnyMaket->addWidget(new QLabel("Имя"));
    vvodImeni = new QLineEdit;
    vertikalnyMaket->addWidget(vvodImeni);

    vertikalnyMaket->addWidget(new QLabel("Возраст"));
    vvodVozrasta = new QSpinBox;
    vertikalnyMaket->addWidget(vvodVozrasta);

    QPushButton* knopkaDobavit = new QPushButton("Добавить");
    connect(knopkaDobavit, &QPushButton::clicked, this, &MainWindow::klikDobavit);
    vertikalnyMaket->addWidget(knopkaDobavit);

}
MainWindow::~MainWindow() = default;

void MainWindow::klikDobavit() {
    const QString imya = vvodImeni->text();
    const int vozrast = vvodVozrasta->value();

    const int kolichestvoStrok = tablica->rowCount();
    tablica->setRowCount(kolichestvoStrok + 1);
    tablica->setItem(kolichestvoStrok, 0, new QTableWidgetItem(imya));
    tablica->setItem(kolichestvoStrok, 1, new QTableWidgetItem(QString::number(vozrast)));
}
