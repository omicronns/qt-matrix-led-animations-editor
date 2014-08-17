#ifndef SIMULATORWINDOW_H
#define SIMULATORWINDOW_H

#include <QWidget>
#include <QMessageBox>
#include <QFileDialog>
#include <QFile>
#include <QMenu>
#include <QList>
#include <QModelIndexList>
#include <QString>
#include "ledmatrix.h"

namespace Ui {
class SimulatorWindow;
}

class SimulatorWindow : public QWidget
{
    Q_OBJECT

    QString m_exportFilename;
    QString m_importFilename;
    QList<SimFrame> m_animation;

public:
    explicit SimulatorWindow(QWidget *parent = 0);
    ~SimulatorWindow();

private slots:
    void removeFrame(void);
    void insertFrame(void);
    void switchFrame(int dummy, int v_frameNumber);
    void loadFrameToEditor(void);
    void storeFrame(void);
    void orWithFrame(void);
    void andWithFrame(void);
    void rotateFrameLeft(void);
    void rotateFrameRight(void);
    void rotateFrameUp(void);
    void rotateFrameDown(void);
    void importAnimation(void);
    void exportAnimation(void);
    void importFrame(void);
    void exportFrame(void);
    void quickStore(void);
    void quickLoad(void);

private:
    void writeFrameToFile(const SimFrame v_frame, QFile &v_outFile);
    void readFrameFromFile(SimFrame &v_frame, QFile &v_inFile);

private:
    Ui::SimulatorWindow *ui;
};

#endif // SIMULATORWINDOW_H
