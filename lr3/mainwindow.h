#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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
    void on_pushButton_calc_clicked();

    void on_radioButton_plus_clicked();

    void on_radioButton_sqrt_clicked();

    void on_radioButton_min_clicked();

    void on_radioButton_div_clicked();

    void on_radioButton_mult_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
