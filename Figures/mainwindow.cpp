#include <QMouseEvent>
#include <QDebug>

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("MagicFigures");
}

MainWindow::~MainWindow() {
    delete ui;
    for (int i = 0; i < figures.size(); i++)
        delete figures[i];
    figures.clear();
}


void MainWindow::paintEvent(QPaintEvent* paint_event) {

    Representer r(this);
    if (draw)
    {
        Figure *newFigure = figureCreator.createNewFigure(curP, figures.size());
        if (newFigure !=nullptr)
            figures.push_back(newFigure);
    }
    else
    {
        for (int i = 0; i < figures.size(); i++)
        {
            if (figures.at(i)->contain(curP))
            {
                delete figures.takeAt(i);
                i--;
            }
        }
    }
    for (Figure *f : figures)
        f->draw(&r);
    QMainWindow::paintEvent(paint_event);
}

void MainWindow::mousePressEvent(QMouseEvent* mouse_event) {
    if (mouse_event->button() == Qt::LeftButton)
    {
        draw = true;
        curP = mouse_event->pos();
        repaint();
    }
    else if (mouse_event->button() == Qt::RightButton)
    {
        draw = false;
        curP = mouse_event->pos();
        repaint();
    }

    QMainWindow::mousePressEvent(mouse_event);
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    int maxLength = std::min(this->width(), this->height())/2;
    figureCreator.setMaxLenght(maxLength);
    QMainWindow::resizeEvent(event);
}
