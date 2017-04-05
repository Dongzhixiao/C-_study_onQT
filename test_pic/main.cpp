#include "dialog_test_pic.h"
#include <QApplication>
#include <QDialog>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Dialog_test_pic w;
    w.show();


    return a.exec();
}
