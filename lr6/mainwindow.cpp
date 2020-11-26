#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTableWidgetItem>
#include <QString>

int arrayForTable[10][5] = {
    {0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0},
};

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    int rowCount = ui->tableWidget->rowCount() + 1;

    for (int i=0; i<10; i++, rowCount++)
    {
        ui->tableWidget->setRowCount(rowCount);
        for (int j=0; j<5; j++)
        {
            QTableWidgetItem *item = new QTableWidgetItem();
            item->setText(QString::number(arrayForTable[i][j]));
            ui->tableWidget->setItem(i, j, item);
        }
    }

    ui->lineEdit->setValidator(new QRegExpValidator(QRegExp("^[0-9/-]{0,4}$"), this));


}

MainWindow::~MainWindow()
{
    delete ui;
}

int selectionSort(int data[], int lenD)
{
  int j = 0;
  int tmp = 0;
  for(int i=0; i<lenD; i++){
    j = i;
    for(int k = i; k<lenD; k++){
      if(data[j]>data[k]){
        j = k;
      }
    }
    tmp = data[i];
    data[i] = data[j];
    data[j] = tmp;
  }
  return data[lenD];
}

int bubbleSort(int data[], int lenD)
{
  int tmp = 0;
  for(int i = 0;i<lenD;i++){
    for(int j = (lenD-1);j>=(i+1);j--){
      if(data[j]<data[j-1]){
        tmp = data[j];
        data[j]=data[j-1];
        data[j-1]=tmp;
      }
    }
  }
  return data[lenD];
}

int insertionSort(int data[], int lenD)
{
  int key = 0;
  int i = 0;
  for(int j = 1;j<lenD;j++){
    key = data[j];
    i = j-1;
    while(i>=0 && data[i]>key){
      data[i+1] = data[i];
      i = i-1;
      data[i+1]=key;
    }
  }
  return data[lenD];
}

int merge(int merged[], int lenD, int L[], int lenL, int R[], int lenR){
  int i = 0;
  int j = 0;
  while(i<lenL||j<lenR){
    if (i<lenL & j<lenR){
      if(L[i]<=R[j]){
        merged[i+j] = L[i];
        i++;
      }
      else{
        merged[i+j] = R[j];
        j++;
      }
    }
    else if(i<lenL){
      merged[i+j] = L[i];
      i++;
    }
    else if(j<lenR){
      merged[i+j] = R[j];
      j++;
    }
  }
  return merged[sizeof(merged)/sizeof(int)];
}

int mergeSort(int data[], int lenD)
{
  if(lenD>1){
    int middle = lenD/2;
    int rem = lenD-middle;
    int* L = new int[middle];
    int* R = new int[rem];
    for(int i=0;i<lenD;i++){
      if(i<middle){
        L[i] = data[i];
      }
      else{
        R[i-middle] = data[i];
      }
    }
    mergeSort(L,middle);
    mergeSort(R,rem);
    merge(data, lenD, L, middle, R, rem);
  }
  return data[lenD];
}

int quickSort(int* data, int const len)
{
  int const lenD = len;
  int pivot = 0;
  int ind = lenD/2;
  int i,j = 0,k = 0;
  if(lenD>1){
    int* L = new int[lenD];
    int* R = new int[lenD];
    pivot = data[ind];
    for(i=0;i<lenD;i++){
      if(i!=ind){
        if(data[i]<pivot){
          L[j] = data[i];
          j++;
        }
        else{
          R[k] = data[i];
          k++;
        }
      }
    }
    quickSort(L,j);
    quickSort(R,k);
    for(int cnt=0;cnt<lenD;cnt++){
      if(cnt<j){
        data[cnt] = L[cnt];;
      }
      else if(cnt==j){
        data[cnt] = pivot;
      }
      else{
        data[cnt] = R[cnt-(j+1)];
      }
    }
  }
  return data[len];
}


void MainWindow::on_pushButton_clicked()
{
    int arr[10][5];

    for (int i=0; i<10; i++)
                for (int j=0; j<5; j++)
                {
                    QString val = ui->tableWidget->item(i, j)->text();
                    arr[i][j] = val.toInt(0, 10);
                }

    int selectionArr[10];
    int bubbleArr[10];
    int insertionArr[10];
    int mergeArr[10];
    int quickArr[10];

    for (int i=0; i<10; i++)
    {
        selectionArr[i] = arr[i][0];
        bubbleArr[i] = arr[i][1];
        insertionArr[i] = arr[i][2];
        mergeArr[i] = arr[i][3];
        quickArr[i] = arr[i][4];
    }

    selectionArr[10] = selectionSort(selectionArr, 10);
    bubbleArr[10] = bubbleSort(bubbleArr, 10);
    insertionArr[10] = insertionSort(insertionArr, 10);
    mergeArr[10] = mergeSort(mergeArr, 10);
    quickArr[10] = quickSort(quickArr, 10);

    for (int i=0; i<10; i++)
    {
        QTableWidgetItem *item1 = new QTableWidgetItem();
        item1->setText(QString::number(selectionArr[i]));
        ui->tableWidget->setItem(i, 0, item1);
        QTableWidgetItem *item2 = new QTableWidgetItem();
        item2->setText(QString::number(bubbleArr[i]));
        ui->tableWidget->setItem(i, 1, item2);
        QTableWidgetItem *item3 = new QTableWidgetItem();
        item3->setText(QString::number(insertionArr[i]));
        ui->tableWidget->setItem(i, 2, item3);
        QTableWidgetItem *item4 = new QTableWidgetItem();
        item4->setText(QString::number(mergeArr[i]));
        ui->tableWidget->setItem(i, 3, item4);
        QTableWidgetItem *item5 = new QTableWidgetItem();
        item5->setText(QString::number(quickArr[i]));
        ui->tableWidget->setItem(i, 4, item5);
    }
}

void MainWindow::on_pushButton_find_clicked()
{
    QString str = ui->lineEdit->text();
    if (str.length() < 1) {
        ui->label_number->setText(QString("Вы не ввели искомое число"));
        ui->label_number->setStyleSheet("color: red");
    } else {
        int number = str.toInt();

        QString first = ui->tableWidget->item(0, 0)->text();
        int x, y;
        int xi, yi, xj, yj;
        x = y = first.toInt();
        xi = yi = xj = yj = 0;

        bool flag = false;
        bool flag2 = false;
        bool flag3 = false;

        for (int i=0; i<10; i++)
            for (int j=0; j<5; j++)
            {
                QString val = ui->tableWidget->item(i, j)->text();
                int n = val.toInt();
                if (n == number)
                {
                    ui->tableWidget->item(i, j)->setBackground(Qt::green);
                    ui->label_number->setText(QString("Число ") + val + QString(" найдено"));
                    ui->label_number->setStyleSheet("color: green");
                    flag = true;
                } else if (n < number) {
                    ui->tableWidget->item(i, j)->setBackground(Qt::white);
                    if (number - n < abs(number - x))
                    {
                        x = n;
                        xi = i;
                        xj = j;
                        flag2 = true;
                    }
                } else {
                    ui->tableWidget->item(i, j)->setBackground(Qt::white);
                    if (n - number < abs(y - number))
                    {
                        y = n;
                        yi = i;
                        yj = j;
                        flag3 = true;
                    }
                }
            }
        if (!flag)
        {
            if (flag2 && flag3) {
                ui->label_number->setText(QString("Промежуток: [") + QString::number(x) + QString(", ") + QString::number(y) + QString("]"));
                ui->label_number->setStyleSheet("color: green");
                ui->tableWidget->item(xi, xj)->setBackground(Qt::yellow);
                ui->tableWidget->item(yi, yj)->setBackground(Qt::yellow);
            } else if (flag2) {
                ui->label_number->setText(QString("Промежуток: [") + QString::number(x) + QString(", ∞]"));
                ui->label_number->setStyleSheet("color: green");
                ui->tableWidget->item(xi, xj)->setBackground(Qt::yellow);
            } else {
                ui->label_number->setText(QString("Промежуток: [∞, ") + QString::number(y) + QString("]"));
                ui->label_number->setStyleSheet("color: green");
                ui->tableWidget->item(yi, yj)->setBackground(Qt::yellow);
            }
        }
    }
}
