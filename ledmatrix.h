#ifndef LEDMATRIX_H
#define LEDMATRIX_H

#include <QTableWidget>
#include <QTableWidgetItem>
#include "simframe.h"

#define CELL_WIDTH  15
#define CELL_HEIGHT 15

class LedMatrix : public QTableWidget
{
    Q_OBJECT
    friend class SimulatorWindow;
private:
    QColor m_offColor;
    QColor m_onColor;

public slots:
    void setDiode(int row, int col, bool state);
    void toggleDiode(int row, int col);

private:
    void setGridSize(int width, int height);
    void createDiodes(int rows, int cols);

public:
    LedMatrix(QWidget *parent);
    LedMatrix(int rows, int cols, QWidget *parent);
    void loadSimFrame(const SimFrame &v_frame);
    void readSimFrame(SimFrame &v_frame);
};

#endif // LEDMATRIX_H
