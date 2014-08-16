#ifndef SIMULATORWINDOW_H
#define SIMULATORWINDOW_H

#include <QWidget>
#include <QMessageBox>
#include <QMenu>
#include <QList>
#include "ledmatrix.h"

namespace Ui {
class SimulatorWindow;
}

class SimulatorWindow : public QWidget
{
    Q_OBJECT

    QList<SimFrame> m_animation;
    int m_currentFrame;

public:
    explicit SimulatorWindow(QWidget *parent = 0);
    ~SimulatorWindow();

private slots:
    void addFrame(void);
    void switchFrame(int dummy, int v_frameNumber);
    void storeFrame(void);
    void sumToFrame(void);
    void overlapToFrame(void);

private:
    void saveFrame(int v_frameNumber);
    void loadFrame(int v_frameNumber);

private:
    Ui::SimulatorWindow *ui;
};

#endif // SIMULATORWINDOW_H
