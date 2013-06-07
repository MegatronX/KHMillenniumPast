#ifndef KHMPTOOLSWINDOW_H
#define KHMPTOOLSWINDOW_H

#include <QMainWindow>

namespace Ui {
class KHMPToolsWindow;
}

class KHMPToolsWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit KHMPToolsWindow(QWidget *parent = 0);
    ~KHMPToolsWindow();
    
private:
    Ui::KHMPToolsWindow *ui;
};

#endif // KHMPTOOLSWINDOW_H
