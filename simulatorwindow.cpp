#include "simulatorwindow.h"
#include "ui_simulatorwindow.h"
#include <iostream>

SimulatorWindow::SimulatorWindow(QWidget *parent)
    :
    QWidget(parent),
    ui(new Ui::SimulatorWindow)
{
    ui->setupUi(this);
    ui->ledDisplay->createDiodes(8, 80);
    ui->ledDisplay->setGridSize(CELL_WIDTH, CELL_HEIGHT);
}

SimulatorWindow::~SimulatorWindow()
{
    delete ui;
}

void SimulatorWindow::on_debug1_clicked()
{
    std::cout << "Debug\n";
}
