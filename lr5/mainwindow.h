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
    void on_lineEdit_name_editingFinished();

    void on_comboBox_sex_currentIndexChanged(int index);

    void on_comboBox_race_currentIndexChanged(int index);

    void on_comboBox_class_currentIndexChanged(int index);

    void on_pushButton_generate_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
