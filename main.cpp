#include "mrender.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    mRender w;
    w.show();

    return a.exec();
}
