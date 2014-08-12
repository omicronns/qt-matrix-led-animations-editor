#ifndef LEDMATRIX_H
#define LEDMATRIX_H

#include <QTableWidget>
#include <QTableWidgetItem>

#define CELL_WIDTH  15
#define CELL_HEIGHT 15

#define X_RESOLUTION 80
#define Y_RESOLUTION 8

class LedMatrix : public QTableWidget
{
    Q_OBJECT
private:
    QColor m_offColor;
    QColor m_onColor;

public slots:
    void setDiode(int row, int col, bool state);
    void toggleDiode(int row, int col);

public:
    LedMatrix(QWidget *parent);
    LedMatrix(int rows, int cols, QWidget *parent);
    void setGridSize(int width, int height);
    void createDiodes(void);
};

#endif // LEDMATRIX_H
