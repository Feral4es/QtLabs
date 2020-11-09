#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QString>
#include <QRegExp>
#include <QtCore>
#include <QRegExpValidator>
#include <QMessageBox>
#include <QtMath>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->lineEdit_index->setValidator(new QRegExpValidator(QRegExp("^[0-9]{0,4}$"), this));
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

bool checkNotNull(QString str)
{
    int len = str.size();
    if (len == 0) return false;
    return true;
}

QString declOfNum(int n, QString text_forms[3]) {
    n = n % 100;
    int n1 = n % 10;
    if (n > 10 && n < 20) { return text_forms[2]; }
    if (n1 > 1 && n1 < 5) { return text_forms[1]; }
    if (n1 == 1) { return text_forms[0]; }
    return text_forms[2];
}

void MainWindow::on_pushButton_clicked()
{
    QString string = ui->lineEdit_string->text();
    QString index = ui->lineEdit_index->text();

    bool checkString = checkNotNull(string);
    bool checkIndex = checkNotNull(index);

    if (checkString && checkIndex) {
        int id = index.toInt();
        int strLength = string.length();

        if (strLength > id) {
            ui->label_char->setText("Ваш символ: " + QString(string[id]));

            ui->lineEdit_string->setText("");
            ui->lineEdit_index->setText("");
        } else {
            QString arr[3] = {" символ", " символа", " символов"};
            QString charDecl = declOfNum(2, arr);
            QString error1 = "В строке содержится ";
            QString error2 = ".\nВыберите индекс от 0 до ";

            ErrorMessage(error1 + QString::number(strLength) + charDecl + error2 + QString::number(strLength - 1));
        }
    } else if (checkString && !checkIndex) {
        ErrorMessage("Заполните строку!");
    } else if (!checkString && checkIndex) {
        ErrorMessage("Заполните индекс!");
    } else {
        ErrorMessage("Заполните строку и индекс!");
    }
}

void MainWindow::on_lineEdit_index_textChanged(const QString &arg1)
{
    ui->label_char->setText("");
}

void MainWindow::on_lineEdit_string_textChanged(const QString &arg1)
{
    ui->label_char->setText("");
}
