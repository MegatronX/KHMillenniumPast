#pragma once
#ifndef CHARACTERWIDGET_H
#define CHARACTERWIDGET_H

#include <QWidget>

//! [0]
class CharacterWidget : public QWidget
{
    Q_OBJECT

public:
     CharacterWidget(QWidget *parent = 0);

protected:
    void paintEvent(QPaintEvent *event);
};

#endif // CHARACTERWIDGET_H
