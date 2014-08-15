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
    void setDiodeState(int v_row, int v_col, bool v_state);
    void toggleDiodeState(int v_row, int v_col);
    void clearDisplay(void);

private:
    void setGridSize(int v_width, int v_height);
    void createDiodes(int v_rows, int v_cols);

public:
    LedMatrix(QWidget *v_parent);
    LedMatrix(int rows, int cols, QWidget *v_parent);
    bool diodeState(int v_row, int v_col);
    bool getDiodeState(int v_row, int v_col);
    void setSimFrame(const SimFrame &v_frame);
    void getSimFrame(SimFrame &v_frame);
};

#endif // LEDMATRIX_H
