#include "khmptoolswindow.h"
#include "ui_khmptoolswindow.h"

KHMPToolsWindow::KHMPToolsWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::KHMPToolsWindow)
{
    ui->setupUi(this);
}

KHMPToolsWindow::~KHMPToolsWindow()
{
    delete ui;
}
