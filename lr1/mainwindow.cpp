#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QString>
#include <QChar>
#include <QMessageBox>

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

// функция проверки отсутствия посторонних символов
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

void ErrorMessager(QString str, Ui::MainWindow* ui)
{
    ui->lineEdit_4->setText(" ");
    ui->label_error->setText(" ");
    QMessageBox msgBox;
    msgBox.setWindowTitle("Ошибка");
    msgBox.setText(str);
    msgBox.exec();

}

void MainWindow::on_pushButton_clicked()
{
    float x, y, sum;
    QString error;

    // Получаю значения полей (тип строка)
    QString operator_1 = ui->lineEdit->text();
    QString operator_2 = ui->lineEdit_3->text();
    bool check = checkIsNumber(operator_1) == 1 && checkIsNumber(operator_2) == 1;

    QString error_mes1 = "Операция не возможна!!!\n";
    QString error_mes2 = "содержит недопустимые символы!!!\n";
    QString error_mes3 = "Исправте ошибку.\n";
    QString error_mes4 = "не содержит данные.\n";

    QString error_din2 = "Первый оператор (Op1) ";
    QString error_din1 = "Второй оператор (Op2) ";
    QString error_din3 = "Оба оператора (Op1 & Op2) ";

    if (check)
    {


        // Перевожу значение в тип float(вещественное), можно переводить в целое toInt(),
        // тогда на 20 строке при инициализации переменных им тоже следует задать тип int вместо float
        x = operator_1.toFloat();
        y = operator_2.toFloat();

        // Складываю числа, если бы мы не перевели их в числовой тип, а оставили строками, то 1+3 стало бы 13
        sum = x + y;
        error = "Операция проведена успешно. Результат вычисления " + QString::number(sum);
        // Заполняю поле результата
        ui->lineEdit_4->setText(QString::number(sum));
        ui->label_error->setStyleSheet("color: #2F4F2F");
        ui->label_error->setText(error);

    } else if (checkIsNumber(operator_1) == 0 && checkIsNumber(operator_2) == 0) {
        error = error_mes1 + error_din3 + error_mes2 + error_mes3;        
        ErrorMessager(error, ui);

    } else if (checkIsNumber(operator_2) == 0 && checkIsNumber(operator_1) == 1){
        error = error_mes1 + error_din1 + error_mes2 + error_mes3;        
        ErrorMessager(error, ui);

    } else if (checkIsNumber(operator_2) == 0 && checkIsNumber(operator_1) == 2){
        error = error_mes1 + error_din1 + error_mes2 + error_din2 + error_mes4 + error_mes3;       
        ErrorMessager(error, ui);

    } else if (checkIsNumber(operator_2) == 1 && checkIsNumber(operator_1) == 0){
        error = error_mes1 + error_din2 + error_mes2 + error_mes3;        
        ErrorMessager(error, ui);

    } else if (checkIsNumber(operator_2) == 2 && checkIsNumber(operator_1) == 0){
        error = error_mes1 + error_din2 +error_mes2 + error_din1 + error_mes4 + error_mes3;        
        ErrorMessager(error, ui);

    } else if (checkIsNumber(operator_2) == 2 && checkIsNumber(operator_1) == 2){
        error = error_mes1  + error_din3 + error_mes4 + error_mes3;       
        ErrorMessager(error, ui);

    } else if (checkIsNumber(operator_2) == 1 && checkIsNumber(operator_1) == 2){
        error = error_mes1 + error_din2 + error_mes4 + error_mes3;       
        ErrorMessager(error, ui);

    }else {
        error = error_mes1 + error_din1 + error_mes4 + error_mes3;        
        ErrorMessager(error, ui);
    }

}
