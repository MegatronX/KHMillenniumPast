#include "khmptoolswindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    KHMPToolsWindow w;
    w.show();
    
    return a.exec();
}
