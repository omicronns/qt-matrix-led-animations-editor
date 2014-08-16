#include "simulatorwindow.h"
#include "ui_simulatorwindow.h"
#include <iostream>

SimulatorWindow::SimulatorWindow(QWidget *parent)
    :
    QWidget(parent),
    ui(new Ui::SimulatorWindow)
{
    ui->setupUi(this);
    ui->ledDisplay->init();
    ui->advancedStoreButton->setMenu(new QMenu(ui->advancedStoreButton));
    connect(ui->advancedStoreButton->menu()->addAction(QString("Add pixel mask to frame")),
            SIGNAL(triggered()), this, SLOT(sumToFrame()));
    connect(ui->advancedStoreButton->menu()->addAction(QString("Overlapping pixel mask to frame")),
            SIGNAL(triggered()), this, SLOT(overlapToFrame()));
}

SimulatorWindow::~SimulatorWindow()
{
    delete ui;
}

void SimulatorWindow::addFrame(void)
{
    if(ui->frameViewer->columnCount() == 0)
    {
        m_animation.append(SimFrame());
        ui->frameViewer->setColumnCount(1);
        m_currentFrame = 0;
    }
    else
    {
        m_animation.insert(++m_currentFrame, SimFrame());
        ui->frameViewer->setColumnCount(ui->frameViewer->columnCount() + 1);
    }

}

void SimulatorWindow::saveFrame(int v_frameNumber)
{
    ui->ledDisplay->getSimFrame(m_animation[v_frameNumber]);
}

void SimulatorWindow::loadFrame(int v_frameNumber)
{
    ui->ledDisplay->setSimFrame(m_animation[v_frameNumber]);
}

void SimulatorWindow::switchFrame(int dummy, int v_frameNumber)
{
    m_currentFrame = v_frameNumber;
    loadFrame(v_frameNumber);
}

void SimulatorWindow::storeFrame(void)
{
    if(ui->frameViewer->columnCount())
    {
        QModelIndexList selectedFrames = ui->frameViewer->selectedIndexesList();
        while(selectedFrames.size())
        {
            ui->ledDisplay->getSimFrame(m_animation[selectedFrames.front().column()]);
            selectedFrames.removeFirst();
        }
    }
    else
    {
        QMessageBox msg(QMessageBox::Warning, QString("Warning"), QString("No frames avalible"), QMessageBox::Ok);
        msg.exec();
    }
}

void SimulatorWindow::sumToFrame(void)
{
    if(ui->frameViewer->columnCount())
    {
        QModelIndexList selectedFrames = ui->frameViewer->selectedIndexesList();
        while(selectedFrames.size())
        {
            SimFrame toAdd;
            ui->ledDisplay->getSimFrame(toAdd);
            m_animation[selectedFrames.front().column()] |= toAdd;
            selectedFrames.removeFirst();
        }
    }
    else
    {
        QMessageBox msg(QMessageBox::Warning, QString("Warning"), QString("No frames avalible"), QMessageBox::Ok);
        msg.exec();
    }
}

void SimulatorWindow::overlapToFrame(void)
{
    if(ui->frameViewer->columnCount())
    {
        QModelIndexList selectedFrames = ui->frameViewer->selectedIndexesList();
        while(selectedFrames.size())
        {
            SimFrame toAdd;
            ui->ledDisplay->getSimFrame(toAdd);
            m_animation[selectedFrames.front().column()] &= toAdd;
            selectedFrames.removeFirst();
        }
    }
    else
    {
        QMessageBox msg(QMessageBox::Warning, QString("Warning"), QString("No frames avalible"), QMessageBox::Ok);
        msg.exec();
    }
}
