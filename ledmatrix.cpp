#include "ledmatrix.h"

LedMatrix::LedMatrix(QWidget *parent)
    :   QTableWidget(parent),
        m_offColor(QColor(0,0,0)),
        m_onColor(QColor(255,0,0))
{
    connect(this, SIGNAL(cellPressed(int,int)), this, SLOT(toggleDiode(int,int)));
}

LedMatrix::LedMatrix(int rows, int cols, QWidget *parent)
   :    QTableWidget(rows, cols, parent),
        m_offColor(QColor(0,0,0)),
        m_onColor(QColor(255,0,0))
{
    connect(this, SIGNAL(cellPressed(int,int)), this, SLOT(toggleDiode(int,int)));
}

void LedMatrix::setGridSize(int width, int height)
{
    for(int i = 0; i < rowCount(); i++)
        setRowHeight(i, height);
    for(int j = 0; j < columnCount(); j++)
        setColumnWidth(j, width);
}

void LedMatrix::createDiodes(void)
{
    setColumnCount(X_RESOLUTION);
    setRowCount(Y_RESOLUTION);
    for(int i = 0; i < rowCount(); i++)
        for(int j = 0; j < columnCount(); j++)
        {
            setItem(i, j, new QTableWidgetItem());
            item(i, j)->setBackgroundColor(m_offColor);
        }
}

void LedMatrix::setDiode(int row, int col, bool state)
{
    item(row, col)->setBackgroundColor(state ? m_onColor : m_offColor);
}

void LedMatrix::toggleDiode(int row, int col)
{
    if(item(row, col)->backgroundColor() == m_offColor)
        item(row, col)->setBackgroundColor(m_onColor);
    else
        item(row, col)->setBackgroundColor(m_offColor);
}
