#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class QTableWidget;
class QLineEdit;
class QSpinBox;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

private slots:
    void klikDobavit();

private:
    QTableWidget* tablica;
    QLineEdit* vvodImeni;
    QSpinBox* vvodVozrasta;
};

#endif // MAINWINDOW_H
