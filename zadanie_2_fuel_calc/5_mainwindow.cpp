#include "mainwindow.h"
#include "ui_mainwindow.h"

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

void MainWindow::on_knopkaRascheta_clicked()
{
    double vvedenoeRasstoyanie = ui->vvodRasstoyaniya->text().toDouble();
    double vvedeniyRashod = ui->vvodRashoda->text().toDouble();
    double vvedenayaCena = ui->vvodCeny->text().toDouble();

    moyaPoezdka.setRasstoyanie(vvedenoeRasstoyanie);
    moyaPoezdka.setRashod(vvedeniyRashod);
    moyaPoezdka.setCenaTopliva(vvedenayaCena);

    double nuzhnoLitrov = moyaPoezdka.rasschitatLitry();
    double itogovayaStoimost = moyaPoezdka.rasschitatStoimost();

    QString rezultatStroka = "Для поездки потребуется: " + QString::number(nuzhnoLitrov, 'f', 2) + " л.\n" +
                             "Общая стоимость: " + QString::number(itogovayaStoimost, 'f', 2) + " руб.";

    ui->tekstRezultata->setText(rezultatStroka);
}
