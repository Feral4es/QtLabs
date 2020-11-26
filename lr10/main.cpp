#include <QCoreApplication>
#include <QString>
#include <iostream>
#include <ostream>

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
bool sim(char x)
{
    return (x == '1' || x == '2' || x == '3' || x == '4');
}


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    float x, y, result;
    char str1[5], str2[5];
        char operation;
        std::cout << "Enter first number: ";
        std::cin >> str1;
        if (!checkIsNumber(str1))
        {
            std::cout << "Error, incorrect input!!! \n";
            return 1;
        }

        x = atof(str1);
            std::cout << "Enter second number: ";
            std::cin >> str2;
            if (!checkIsNumber(str2))
            {
                std::cout << "Error, incorrect input!!! \n";
                return 2;
            }
            y = atof(str2);


    std::cout << ("Vyberite operatchiy: \n1 - '+', \n2 - '-', \n3 - '*', \n4 - '/'. \n");
    std::cin >> (operation);

    if (!sim(operation))
        {
            std::cout << "Error, no such operation!!! \n";
            return 3;
        }

    if (y == 0)
    {
        std::cout << "Error, calculation not possible \n";
                    return 4;
    }

    switch (operation) {
        case '1':
            result = x + y;
            break;
        case '2':
            result = x - y;
            break;
        case '3':
            result = x * y;
            break;
        case '4':
            result = x / y;
            break;
    }

    std::cout << ("Otvet: ");
    std::cout << (result);

    return 0;

    return a.exec();
}
