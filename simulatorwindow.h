#ifndef SIMULATORWINDOW_H
#define SIMULATORWINDOW_H

#include <QWidget>
#include "ledmatrix.h"

namespace Ui {
class SimulatorWindow;
}

class SimulatorWindow : public QWidget
{
    Q_OBJECT

    SimFrame m_frame;

public:
    explicit SimulatorWindow(QWidget *parent = 0);
    ~SimulatorWindow();

private slots:
    void saveFrame(void);
    void loadFrame(void);

private:
    Ui::SimulatorWindow *ui;
};

#endif // SIMULATORWINDOW_H
