#ifndef SIMULATORWINDOW_H
#define SIMULATORWINDOW_H

#include <QWidget>

namespace Ui {
class SimulatorWindow;
}

class SimulatorWindow : public QWidget
{
    Q_OBJECT

public:
    explicit SimulatorWindow(QWidget *parent = 0);
    ~SimulatorWindow();

private slots:
    void on_pushButton_clicked();

private:
    Ui::SimulatorWindow *ui;
};

#endif // SIMULATORWINDOW_H
