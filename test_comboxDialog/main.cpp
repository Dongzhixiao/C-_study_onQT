#include "dialog.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc,argv);
    Dialog *d = new Dialog();
    d->show();
    return app.exec();
}
