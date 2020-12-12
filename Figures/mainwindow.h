#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPainter>

#include "math.h"

#include "figure.h"
#include "representer.h"
#include "randomfigurecreator.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    void paintEvent(QPaintEvent* paint_event);
    void mousePressEvent(QMouseEvent* mouse_event);
    void resizeEvent(QResizeEvent *event);
    bool draw = false;
    QPoint curP;
    QVector<Figure *> figures;
    RandomFigureCreator figureCreator;
};
#endif // MAINWINDOW_H
