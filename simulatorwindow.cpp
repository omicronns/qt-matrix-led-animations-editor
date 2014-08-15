#include "simulatorwindow.h"
#include "ui_simulatorwindow.h"
#include <iostream>

SimulatorWindow::SimulatorWindow(QWidget *parent)
    :
    QWidget(parent),
    ui(new Ui::SimulatorWindow)
{
    ui->setupUi(this);
    ui->ledDisplay->createDiodes(8,80);
    ui->ledDisplay->setGridSize(CELL_WIDTH, CELL_HEIGHT);
}

SimulatorWindow::~SimulatorWindow()
{
    delete ui;
}

void SimulatorWindow::saveFrame()
{
    ui->ledDisplay->getSimFrame(m_frame);
}

void SimulatorWindow::loadFrame()
{
    ui->ledDisplay->setSimFrame(m_frame);
}
