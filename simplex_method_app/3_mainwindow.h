#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "simplexmetod.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_spinPeremennie_valueChanged(int arg1);
    void on_spinOgranicheniya_valueChanged(int arg1);
    void on_btnReshit_clicked();
    void on_btnNazad_clicked();
    void on_btnVpered_clicked();

private:
    Ui::MainWindow *ui;
    SimplexMetod reshatel;
    int tekIndeksShaga;

    void obnovitTablicuVvoda();
    void pokazatShag(int indeks);
};
#endif // MAINWINDOW_H
