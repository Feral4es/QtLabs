#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QString>
#include <QMessageBox>
#include <QRadioButton>
#include <QtMath>

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

void Clean(Ui::MainWindow* ui)
{
    ui->label_result->setText("");
    ui->lineEdit_op2->setText("");
    ui->lineEdit_op1->setText("");
}

void Op2_enabled(Ui::MainWindow* ui)
{
    Clean(ui);
    ui->lineEdit_op2->setEnabled(true);
}

void Op2_disabled(Ui::MainWindow* ui)
{
    Clean(ui);
    ui->lineEdit_op2->setEnabled(false);
}

void ErrorMessage(QString str)
{
    QMessageBox msgBox;
    msgBox.setWindowTitle("Ошибка");
    msgBox.setText(str);
    msgBox.exec();
}

int checkIsNumber(QString str)
{
    int len = str.size();
    if (len == 0) return 2;
    for (int i = 0; i < len; i++)
    {
        QString ch = str.data()[i];
        if (!(ch == "0" || (ch.toInt() > 0 && ch.toInt() <= 9) || ch == "." || ch == "-"))
        {
            return 0;
        }
    }
    return 1;
}

void onError(int check1, int check2)
{
    QString error_mes1 = "Операция не возможна!!!\n";
    QString error_mes2 = "содержит недопустимые символы!!!\n";
    QString error_mes3 = "Исправте ошибку.\n";
    QString error_mes4 = "не содержит данные.\n";

    QString error_din2 = "Первый оператор (Op1) ";
    QString error_din1 = "Второй оператор (Op2) ";
    QString error_din3 = "Оба оператора (Op1 & Op2) ";

    QString error = error_mes1;

    if (check2 == 0 && check1 == 0) error += error_din3 + error_mes2;
    if (check2 == 0 && check1 == 1) error += error_din1 + error_mes2;
    if (check2 == 0 && check1 == 2) error += error_din1 + error_mes2 + error_din2 + error_mes4;
    if (check2 == 1 && check1 == 0) error += error_din2 + error_mes2;
    if (check2 == 2 && check1 == 0) error += error_din2 + error_mes2 + error_din1 + error_mes4;
    if (check2 == 2 && check1 == 2) error += error_din3 + error_mes4;
    if (check2 == 1 && check1 == 2) error += error_din2 + error_mes4;
    if (check2 == 2 && check1 == 1) error += error_din1 + error_mes4;

    error += error_mes3;

    ErrorMessage(error);
}

void operations(QString operator_1, QString operator_2, Ui::MainWindow* ui)
{
    float x, y, result;

    x = operator_1.toFloat();
    y = operator_2.toFloat();

    bool plus = ui->radioButton_plus->isChecked();
    bool min = ui->radioButton_min->isChecked();
    bool div = ui->radioButton_div->isChecked();
    bool mult = ui->radioButton_mult->isChecked();
    bool sqrt = ui->radioButton_sqrt->isChecked();

    if (plus) result = x + y;

    if (min) result = x - y;

    if (mult) result = x * y;

    if (div)
    {
        if (y == 0)
        {
            ErrorMessage("Операция деление на 0 не возможна");
            ui->label_result->setText("");
            return;
        }
        result = x / y;
    }

    if (sqrt)
    {

        if (x <= 0)
        {
            ErrorMessage("Корень из 0 и из отрецательных извлечь нельзя!!!");
            ui->label_result->setText("");
            return;
        }
        result = qSqrt(x);
    }

    ui->label_result->setText(QString("Результат: ") + QString::number(result));
    ui->label_result->setStyleSheet("color: #2F4F2F");
}

bool isOneOp(Ui::MainWindow* ui)
{
    return ui->radioButton_sqrt->isChecked();
}

void MainWindow::on_pushButton_calc_clicked()
{
    QString operator_1 = ui->lineEdit_op1->text();
    QString operator_2 = ui->lineEdit_op2->text();

    int check1 = checkIsNumber(operator_1);
    int check2 = checkIsNumber(operator_2);
    bool oneOp = isOneOp(ui);

    if ((check1 == 1 && check2 == 1 && !oneOp) || (check1 == 1 && oneOp))
    {
        operations(operator_1, operator_2, ui);
    } else {
        ui->label_result->setText("");
        onError(check1, check2);
    }

}


void MainWindow::on_radioButton_plus_clicked()
{
    Op2_enabled(ui);
}

void MainWindow::on_radioButton_sqrt_clicked()
{
    Op2_disabled(ui);
}

void MainWindow::on_radioButton_min_clicked()
{
    Op2_enabled(ui);
}

void MainWindow::on_radioButton_div_clicked()
{
    Op2_enabled(ui);
}

void MainWindow::on_radioButton_mult_clicked()
{
    Op2_enabled(ui);
}
