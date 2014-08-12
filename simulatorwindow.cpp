#include "simulatorwindow.h"
#include "ui_simulatorwindow.h"
#include <iostream>

SimulatorWindow::SimulatorWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SimulatorWindow)
{
    ui->setupUi(this);
}

SimulatorWindow::~SimulatorWindow()
{
    delete ui;
}

void SimulatorWindow::on_pushButton_clicked()
{
    std::cout << "Pressed\n";
}
