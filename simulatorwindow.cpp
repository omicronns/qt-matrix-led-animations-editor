#include "simulatorwindow.h"
#include "ui_simulatorwindow.h"

SimulatorWindow::SimulatorWindow(QWidget *parent)
    :
    QWidget(parent),
    m_exportFilename(""),
    m_importFilename(""),
    ui(new Ui::SimulatorWindow)
{
    ui->setupUi(this);
    ui->frameEditor->init(CELL_WIDTH, CELL_HEIGHT);
    ui->framePreview->init(CELL_WIDTH, CELL_HEIGHT);
    ui->quickPreviewWidget->init((CELL_WIDTH*9)/15, (CELL_HEIGHT*9)/15,
                                 (CELL_WIDTH*FRAME_COLS*9)/15 + 2,
                                 (CELL_HEIGHT*FRAME_ROWS*9)/15 + 2);

    ui->storeFrameButton->setMenu(new QMenu(ui->storeFrameButton));
    connect(ui->storeFrameButton->menu()->addAction(QString("OR and store")),
            SIGNAL(triggered()), this, SLOT(orWithFrame()));
    connect(ui->storeFrameButton->menu()->addAction(QString("AND and store")),
            SIGNAL(triggered()), this, SLOT(andWithFrame()));

    ui->featuresButton->setMenu(new QMenu(ui->featuresButton));
    connect(ui->featuresButton->menu()->addAction(QString("Rotate left")),
            SIGNAL(triggered()), this, SLOT(rotateFrameLeft()));
    ui->featuresButton->menu()->actions().back()->setShortcut(Qt::CTRL + Qt::Key_A);
    connect(ui->featuresButton->menu()->addAction(QString("Rotate right")),
            SIGNAL(triggered()), this, SLOT(rotateFrameRight()));
    ui->featuresButton->menu()->actions().back()->setShortcut(Qt::CTRL + Qt::Key_S);
    connect(ui->featuresButton->menu()->addAction(QString("Rotate up")),
            SIGNAL(triggered()), this, SLOT(rotateFrameUp()));
    ui->featuresButton->menu()->actions().back()->setShortcut(Qt::CTRL + Qt::Key_Q);
    connect(ui->featuresButton->menu()->addAction(QString("Rotate down")),
            SIGNAL(triggered()), this, SLOT(rotateFrameDown()));
    ui->featuresButton->menu()->actions().back()->setShortcut(Qt::CTRL + Qt::Key_W);
    connect(ui->featuresButton->menu()->addAction(QString("Quick store")),
            SIGNAL(triggered()), this, SLOT(quickStore()));
    ui->featuresButton->menu()->actions().back()->setShortcut(Qt::CTRL + Qt::Key_Z);
    connect(ui->featuresButton->menu()->addAction(QString("Quick load")),
            SIGNAL(triggered()), this, SLOT(quickLoad()));
    ui->featuresButton->menu()->actions().back()->setShortcut(Qt::CTRL + Qt::Key_X);

    ui->importButton->setMenu(new QMenu(ui->importButton));
    connect(ui->importButton->menu()->addAction(QString("Import frame")),
            SIGNAL(triggered()), this, SLOT(importFrame()));

    ui->exportButton->setMenu(new QMenu(ui->exportButton));
    connect(ui->exportButton->menu()->addAction(QString("Export frame")),
            SIGNAL(triggered()), this, SLOT(exportFrame()));
}

SimulatorWindow::~SimulatorWindow()
{
    delete ui;
}

void SimulatorWindow::removeFrame(void)
{
    if(ui->frameSelector->columnCount())
    {
        QModelIndexList selectedFrames = ui->frameSelector->selectedIndexesList();
        while(selectedFrames.size())
        {
            m_animation.removeAt(selectedFrames.front().column());
            ui->frameSelector->setColumnCount(ui->frameSelector->columnCount() - 1);
            selectedFrames.removeFirst();
        }
    }
    else
    {
        QMessageBox msg(QMessageBox::Warning, QString("Warning"), QString("No frames avalible"), QMessageBox::Ok);
        msg.exec();
    }
}

void SimulatorWindow::insertFrame(void)
{
    if(ui->frameSelector->columnCount() == 0)
    {
        m_animation.append(SimFrame());
        ui->frameSelector->setColumnCount(1);
    }
    else
    {
        QModelIndexList selectedFrames = ui->frameSelector->selectedIndexesList();
        if(selectedFrames.size())
        {
            m_animation.insert(selectedFrames.front().column() + 1, SimFrame());
            ui->frameSelector->setColumnCount(ui->frameSelector->columnCount() + 1);
        }
        else
        {
            m_animation.append(SimFrame());
            ui->frameSelector->setColumnCount(ui->frameSelector->columnCount() + 1);
        }
    }
}

void SimulatorWindow::switchFrame(int dummy, int v_frameNumber)
{
    ui->framePreview->setSimFrame(m_animation[v_frameNumber]);
}

void SimulatorWindow::loadFrameToEditor(void)
{
    SimFrame frameToLoad;
    ui->framePreview->getSimFrame(frameToLoad);
    ui->frameEditor->setSimFrame(frameToLoad);
}

void SimulatorWindow::storeFrame(void)
{
    if(ui->frameSelector->columnCount())
    {
        QModelIndexList selectedFrames = ui->frameSelector->selectedIndexesList();
        if(selectedFrames.size())
        {
            SimFrame editedFrame;
            ui->frameEditor->getSimFrame(editedFrame);
            ui->framePreview->setSimFrame(editedFrame);
            while(selectedFrames.size())
            {
                ui->frameEditor->getSimFrame(m_animation[selectedFrames.front().column()]);
                selectedFrames.removeFirst();
            }
        }
        else
        {
            QMessageBox msg(QMessageBox::Warning, QString("Warning"), QString("Select frames to store into"), QMessageBox::Ok);
            msg.exec();
        }
    }
    else
    {
        QMessageBox msg(QMessageBox::Warning, QString("Warning"), QString("No frames avalible"), QMessageBox::Ok);
        msg.exec();
    }
}

void SimulatorWindow::orWithFrame(void)
{
    if(ui->frameSelector->columnCount())
    {
        QModelIndexList selectedFrames = ui->frameSelector->selectedIndexesList();
        if(selectedFrames.size())
        {
            SimFrame editedFrame, previewFrame;
            ui->frameEditor->getSimFrame(editedFrame);
            ui->framePreview->getSimFrame(previewFrame);
            editedFrame |= previewFrame;
            ui->framePreview->setSimFrame(editedFrame);
            SimFrame toOr;
            ui->frameEditor->getSimFrame(toOr);
            while(selectedFrames.size())
            {
                m_animation[selectedFrames.front().column()] |= toOr;
                selectedFrames.removeFirst();
            }
        }
        else
        {
            QMessageBox msg(QMessageBox::Warning, QString("Warning"), QString("Select frames to store into"), QMessageBox::Ok);
            msg.exec();
        }
    }
    else
    {
        QMessageBox msg(QMessageBox::Warning, QString("Warning"), QString("No frames avalible"), QMessageBox::Ok);
        msg.exec();
    }
}

void SimulatorWindow::andWithFrame(void)
{
    if(ui->frameSelector->columnCount())
    {
        QModelIndexList selectedFrames = ui->frameSelector->selectedIndexesList();
        if(selectedFrames.size())
        {
            SimFrame editedFrame, previewFrame;
            ui->frameEditor->getSimFrame(editedFrame);
            ui->framePreview->getSimFrame(previewFrame);
            editedFrame &= previewFrame;
            ui->framePreview->setSimFrame(editedFrame);
            SimFrame toAnd;
            ui->frameEditor->getSimFrame(toAnd);
            while(selectedFrames.size())
            {
                m_animation[selectedFrames.front().column()] &= toAnd;
                selectedFrames.removeFirst();
            }
        }
        else
        {
            QMessageBox msg(QMessageBox::Warning, QString("Warning"), QString("Select frames to store into"), QMessageBox::Ok);
            msg.exec();
        }
    }
    else
    {
        QMessageBox msg(QMessageBox::Warning, QString("Warning"), QString("No frames avalible"), QMessageBox::Ok);
        msg.exec();
    }
}

void SimulatorWindow::rotateFrameLeft(void)
{
    SimFrame frameToRotate, rotatedFrame;
    ui->frameEditor->getSimFrame(frameToRotate);
    for(int row = 0; row < frameToRotate.rows(); ++row)
        for(int col = 0; col < frameToRotate.cols(); ++col)
            rotatedFrame.setPixel(row, col, frameToRotate.getPixel(row, (col + 1) % frameToRotate.cols()));
    ui->frameEditor->setSimFrame(rotatedFrame);
}

void SimulatorWindow::rotateFrameRight(void)
{
    SimFrame frameToRotate, rotatedFrame;
    ui->frameEditor->getSimFrame(frameToRotate);
    for(int row = 0; row < frameToRotate.rows(); ++row)
        for(int col = 0; col < frameToRotate.cols(); ++col)
            rotatedFrame.setPixel(row, (col + 1) % frameToRotate.cols(), frameToRotate.getPixel(row, col));
    ui->frameEditor->setSimFrame(rotatedFrame);
}

void SimulatorWindow::rotateFrameUp(void)
{
    SimFrame frameToRotate, rotatedFrame;
    ui->frameEditor->getSimFrame(frameToRotate);
    for(int row = 0; row < frameToRotate.rows(); ++row)
        for(int col = 0; col < frameToRotate.cols(); ++col)
            rotatedFrame.setPixel(row, col, frameToRotate.getPixel((row + 1) % frameToRotate.rows(), col));
    ui->frameEditor->setSimFrame(rotatedFrame);
}

void SimulatorWindow::rotateFrameDown(void)
{
    SimFrame frameToRotate, rotatedFrame;
    ui->frameEditor->getSimFrame(frameToRotate);
    for(int row = 0; row < frameToRotate.rows(); ++row)
        for(int col = 0; col < frameToRotate.cols(); ++col)
            rotatedFrame.setPixel((row + 1) % frameToRotate.rows(), col, frameToRotate.getPixel(row, col));
    ui->frameEditor->setSimFrame(rotatedFrame);
}

void SimulatorWindow::writeFrameToFile(const SimFrame v_frame, QFile &v_outFile)
{
    for(int row = 0; row < v_frame.rows(); ++row)
        for(int col = 0; col < v_frame.cols()/8; ++col)
            v_outFile.putChar(v_frame.getByte(row, col));
}

void SimulatorWindow::readFrameFromFile(SimFrame &v_frame, QFile &v_inFile)
{
    char byte;
    for(int row = 0; row < v_frame.rows(); ++row)
        for(int col = 0; col < v_frame.cols()/8; ++col)
        {
            v_inFile.getChar(&byte);
            v_frame.setByte(row, col, byte);
        }
}

void SimulatorWindow::importAnimation(void)
{
    m_importFilename = QFileDialog::getOpenFileName(this, "Open File",
                                                    "");
    if(m_importFilename != QString(""))
    {
        m_animation.clear();
        QFile inFile(m_importFilename);
        inFile.open(QIODevice::ReadOnly);
        int size;
        inFile.read((char *)(&size), 4);
        ui->frameSelector->setColumnCount(size);
        for(int i = 0; i < size; ++i)
        {
            SimFrame frame;
            readFrameFromFile(frame, inFile);
            m_animation.append(frame);
        }
        ui->framePreview->setSimFrame(m_animation.front());
        inFile.close();
    }
}

void SimulatorWindow::exportAnimation(void)
{
    m_exportFilename = QFileDialog::getSaveFileName(this, "Save File",
                                                    "");
    if(m_exportFilename != QString(""))
    {
        QFile outFile(m_exportFilename);
        outFile.open(QIODevice::WriteOnly);
        int size = m_animation.size();
        outFile.write((const char *)(&size), 4);
        for(int i = 0; i < m_animation.size(); ++i)
            writeFrameToFile(m_animation[i], outFile);
        outFile.close();
    }
}

void SimulatorWindow::importFrame(void)
{
    m_importFilename = QFileDialog::getOpenFileName(this, "Open File",
                                                    "");
    if(m_importFilename != QString(""))
    {
        QFile inFile(m_importFilename);
        inFile.open(QIODevice::ReadOnly);
        QModelIndexList selectedFrames = ui->frameSelector->selectedIndexesList();
        if(selectedFrames.size())
        {
            SimFrame inFrame;
            readFrameFromFile(inFrame, inFile);
            while(selectedFrames.size())
            {
                m_animation[selectedFrames.front().column()] = inFrame;
                selectedFrames.removeFirst();
            }
            ui->framePreview->setSimFrame(inFrame);
        }
        else
        {
            QMessageBox msg(QMessageBox::Warning, QString("Warning"), QString("Select frames to import into"), QMessageBox::Ok);
            msg.exec();
        }
        inFile.close();
    }
}

void SimulatorWindow::exportFrame(void)
{
    m_exportFilename = QFileDialog::getSaveFileName(this, "Save File",
                                                    "");
    if(m_exportFilename != QString(""))
    {
        QFile outFile(m_exportFilename);
        outFile.open(QIODevice::WriteOnly);
        SimFrame outFrame;
        ui->framePreview->getSimFrame(outFrame);
        writeFrameToFile(outFrame, outFile);
        outFile.close();
    }
}

void SimulatorWindow::quickStore(void)
{
    SimFrame frameToStore;
    ui->frameEditor->getSimFrame(frameToStore);
    ui->quickPreviewWidget->setSimFrame(frameToStore);
}

void SimulatorWindow::quickLoad(void)
{
    SimFrame frameToLoad;
    ui->quickPreviewWidget->getSimFrame(frameToLoad);
    ui->frameEditor->setSimFrame(frameToLoad);
}

