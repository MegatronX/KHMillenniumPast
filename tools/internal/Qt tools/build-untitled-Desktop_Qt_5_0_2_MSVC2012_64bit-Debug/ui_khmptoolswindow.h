/********************************************************************************
** Form generated from reading UI file 'khmptoolswindow.ui'
**
** Created by: Qt User Interface Compiler version 5.0.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_KHMPTOOLSWINDOW_H
#define UI_KHMPTOOLSWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_KHMPToolsWindow
{
public:
    QAction *actionOpen_Item_Database;
    QAction *actionOpen_Character_Database;
    QWidget *centralWidget;
    QTabWidget *SaveEditorPage;
    QWidget *tab;
    QWidget *tab_2;
    QWidget *tab_3;
    QWidget *tab_4;
    QWidget *tab_5;
    QComboBox *comboBox;
    QLabel *label;
    QTabWidget *SaveGameTabs;
    QWidget *SavePlayerPartyTab;
    QWidget *SaveInventoryTab;
    QWidget *tab_8;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *KHMPToolsWindow)
    {
        if (KHMPToolsWindow->objectName().isEmpty())
            KHMPToolsWindow->setObjectName(QStringLiteral("KHMPToolsWindow"));
        KHMPToolsWindow->resize(800, 600);
        actionOpen_Item_Database = new QAction(KHMPToolsWindow);
        actionOpen_Item_Database->setObjectName(QStringLiteral("actionOpen_Item_Database"));
        actionOpen_Character_Database = new QAction(KHMPToolsWindow);
        actionOpen_Character_Database->setObjectName(QStringLiteral("actionOpen_Character_Database"));
        centralWidget = new QWidget(KHMPToolsWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        SaveEditorPage = new QTabWidget(centralWidget);
        SaveEditorPage->setObjectName(QStringLiteral("SaveEditorPage"));
        SaveEditorPage->setGeometry(QRect(0, 0, 791, 551));
        tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
        SaveEditorPage->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QStringLiteral("tab_2"));
        SaveEditorPage->addTab(tab_2, QString());
        tab_3 = new QWidget();
        tab_3->setObjectName(QStringLiteral("tab_3"));
        SaveEditorPage->addTab(tab_3, QString());
        tab_4 = new QWidget();
        tab_4->setObjectName(QStringLiteral("tab_4"));
        SaveEditorPage->addTab(tab_4, QString());
        tab_5 = new QWidget();
        tab_5->setObjectName(QStringLiteral("tab_5"));
        comboBox = new QComboBox(tab_5);
        comboBox->setObjectName(QStringLiteral("comboBox"));
        comboBox->setGeometry(QRect(110, 0, 231, 22));
        label = new QLabel(tab_5);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(20, 0, 81, 16));
        SaveGameTabs = new QTabWidget(tab_5);
        SaveGameTabs->setObjectName(QStringLiteral("SaveGameTabs"));
        SaveGameTabs->setGeometry(QRect(0, 20, 791, 511));
        SaveGameTabs->setTabPosition(QTabWidget::West);
        SavePlayerPartyTab = new QWidget();
        SavePlayerPartyTab->setObjectName(QStringLiteral("SavePlayerPartyTab"));
        SaveGameTabs->addTab(SavePlayerPartyTab, QString());
        SaveInventoryTab = new QWidget();
        SaveInventoryTab->setObjectName(QStringLiteral("SaveInventoryTab"));
        SaveGameTabs->addTab(SaveInventoryTab, QString());
        tab_8 = new QWidget();
        tab_8->setObjectName(QStringLiteral("tab_8"));
        SaveGameTabs->addTab(tab_8, QString());
        SaveEditorPage->addTab(tab_5, QString());
        KHMPToolsWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(KHMPToolsWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 800, 21));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        KHMPToolsWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(KHMPToolsWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        KHMPToolsWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(KHMPToolsWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        KHMPToolsWindow->setStatusBar(statusBar);

        menuBar->addAction(menuFile->menuAction());
        menuFile->addAction(actionOpen_Item_Database);
        menuFile->addAction(actionOpen_Character_Database);

        retranslateUi(KHMPToolsWindow);

        SaveEditorPage->setCurrentIndex(4);
        SaveGameTabs->setCurrentIndex(2);


        QMetaObject::connectSlotsByName(KHMPToolsWindow);
    } // setupUi

    void retranslateUi(QMainWindow *KHMPToolsWindow)
    {
        KHMPToolsWindow->setWindowTitle(QApplication::translate("KHMPToolsWindow", "KHMPToolsWindow", 0));
        actionOpen_Item_Database->setText(QApplication::translate("KHMPToolsWindow", "Open Item Database", 0));
        actionOpen_Character_Database->setText(QApplication::translate("KHMPToolsWindow", "Open Character Database", 0));
        SaveEditorPage->setTabText(SaveEditorPage->indexOf(tab), QApplication::translate("KHMPToolsWindow", "Tab 1", 0));
        SaveEditorPage->setTabText(SaveEditorPage->indexOf(tab_2), QApplication::translate("KHMPToolsWindow", "Tab 2", 0));
        SaveEditorPage->setTabText(SaveEditorPage->indexOf(tab_3), QApplication::translate("KHMPToolsWindow", "Page", 0));
        SaveEditorPage->setTabText(SaveEditorPage->indexOf(tab_4), QApplication::translate("KHMPToolsWindow", "Page", 0));
        label->setText(QApplication::translate("KHMPToolsWindow", "Available Saves", 0));
        SaveGameTabs->setTabText(SaveGameTabs->indexOf(SavePlayerPartyTab), QApplication::translate("KHMPToolsWindow", "Player Party", 0));
        SaveGameTabs->setTabText(SaveGameTabs->indexOf(SaveInventoryTab), QApplication::translate("KHMPToolsWindow", "Inventory", 0));
        SaveGameTabs->setTabText(SaveGameTabs->indexOf(tab_8), QApplication::translate("KHMPToolsWindow", "Page", 0));
        SaveEditorPage->setTabText(SaveEditorPage->indexOf(tab_5), QApplication::translate("KHMPToolsWindow", "Save Editor", 0));
        menuFile->setTitle(QApplication::translate("KHMPToolsWindow", "File", 0));
    } // retranslateUi

};

namespace Ui {
    class KHMPToolsWindow: public Ui_KHMPToolsWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_KHMPTOOLSWINDOW_H
