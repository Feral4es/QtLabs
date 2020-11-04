#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QString>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->label_result->setStyleSheet("color: #4fb700");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void ErrorMessage(QString str)
{
    QMessageBox msgBox;
    msgBox.setWindowTitle("Ошибка");
    msgBox.setText(str);
    msgBox.exec();
}

bool checkIsCompleted(int op1, int op2, int operation)
{
    if (op1 > -1 && op2 > -1 && operation > -1) return true;

    if (op1 > -1 && operation == 2) return true;

    QString error_mes1 = "Операция не возможна!!!\n";
    QString error_mes2 = "Исправте ошибку.\n";

    QString error_din1 = "Первый оператор (Op1) не выбран!!!\n";
    QString error_din2 = "Второй оператор (Op2) не выбран!!!\n";
    QString error_din3 = "Оба оператора (Op1 & Op2) не выбраны!!!\n";
    QString error_din4 = "Операция не выбрана!!!\n";

    QString error = error_mes1;

    if (op1 == -1 && op2 == -1)
    {
        error += error_din3;
    } else {
        if (op1 == -1) error += error_din1;
        if (op2 == -1) error += error_din2;
    }
    if (operation == -1) error += error_din4;

    error += error_mes2;
    ErrorMessage(error);
    return false;
}

void Clean(Ui::MainWindow* ui)
{
    ui->comboBox_op1->setCurrentIndex(0);
    ui->comboBox_op2->setCurrentIndex(0);
    ui->comboBox_operation->setCurrentIndex(0);
}

void Calculate(int op1, int op2, int operation, Ui::MainWindow* ui)
{
    bool result;
    switch (operation) {
        case 0:
            result = op1 && op2;
            break;
        case 1:
            result = op1 || op2;
            break;
        case 2:
            result = !op1;
            break;
        case 3:
            result = !(op1 == 1 && op2 == 0);
            break;
        case 4:
            result = op1 == op2;
            break;
        case 5:
            result = !(op1 == op2);
            break;
    }

    QString res_str;
    if (result)
    {
        res_str = "истина";
    } else {
        res_str = "ложь";
    }

    Clean(ui);
    ui->label_result->setText(QString("Результат: ") + res_str);
}

void MainWindow::on_pushButton_result_clicked()
{
    int op1 = ui->comboBox_op1->currentIndex() - 1;
    int op2 = ui->comboBox_op2->currentIndex() - 1;
    int operation = ui->comboBox_operation->currentIndex() - 1;

    if (checkIsCompleted(op1, op2, operation))
    {
        Calculate(op1, op2, operation, ui);
    }
}

void MainWindow::on_comboBox_operation_currentIndexChanged(int index)
{
    if (index == 3) {
        ui->comboBox_op2->setEnabled(false);
        ui->comboBox_op2->setCurrentIndex(0);
    } else {
        ui->comboBox_op2->setEnabled(true);
    }
    ui->label_result->setText("");
}

void MainWindow::on_comboBox_op1_currentIndexChanged(int index)
{
    ui->label_result->setText("");
}

void MainWindow::on_comboBox_op2_currentIndexChanged(int index)
{
    ui->label_result->setText("");
}
