#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "poezdka.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_knopkaRascheta_clicked();

private:
    Ui::MainWindow *ui;
    Poezdka moyaPoezdka;
};

#endif // MAINWINDOW_H
