#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>

void Message(QString title, QString str)
{
    QMessageBox msgBox;
    msgBox.setWindowTitle(title);
    msgBox.setText(str);
    msgBox.exec();
}


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    Message("Подсказка", "Добро пожаловать,\n Эта программа предназначена для посиска индекса символа в строке\n Введите в первое поле n-ое количиство символов (до 30!!!). ");
    ui->lineEdit_index->setEnabled(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}

bool checkNotNull(QString str)
{
    int len = str.size();
    if (len == 0) return false;
    return true;
}

QString findChar(QString string, QString strChar)
{
    QString result = "Искомый символ ";
    QString result2 = "находится по индексу: ";
    QString result3 = "не найден";
    bool absent = true;

    for (int count = 0; count < string.length(); count++) {
        if (string[count] == strChar) {
            if (absent) {
                absent = false;
                result += result2 + QString::number(count);
            } else {
                result += ", " + QString::number(count);
            }
        }
    }
    if (absent) result += result3;
    result += ".";
    return result;
}

void MainWindow::on_pushButton_clicked()
{
    QString string = ui->lineEdit_string->text();
    QString strChar = ui->lineEdit_index->text();

    bool checkString = checkNotNull(string);
    bool checkChar = checkNotNull(strChar);

    if (checkString && checkChar) {
        ui->lineEdit_string->setText("");
        ui->lineEdit_index->setText("");

        QString result = findChar(string, strChar);
        ui->label_char->setText(result);
    } else if (checkString && !checkChar) {
        Message("Ошибка","Заполните символ!");
    } else if (!checkString && checkChar) {
        Message("Ошибка","Заполните символ!");
    } else {
        Message("Ошибка","Заполните строку и символ!");
    }
}

void MainWindow::on_lineEdit_string_textChanged(const QString &arg1)
{
    if (arg1.length() == 0)
    {
       ui->lineEdit_index->setEnabled(false);
    } else {
       ui->lineEdit_index->setEnabled(true);
    }
    ui->label_char->setText("");
}

void MainWindow::on_lineEdit_index_textChanged(const QString &arg1)
{
    ui->label_char->setText("");
}
