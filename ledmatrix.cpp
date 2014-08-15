#include "ledmatrix.h"



LedMatrix::LedMatrix(QWidget *v_parent)
    :
    QTableWidget(v_parent),
    m_offColor(QColor(0,0,0)),
    m_onColor(QColor(255,0,0))
{
    connect(this, SIGNAL(cellEntered(int,int)), this, SLOT(toggleDiodeState(int,int)));
    setFixedHeight(200);
}

void LedMatrix::setGridSize(int v_width, int v_height)
{
    for(int i = 0; i < rowCount(); i++)
        setRowHeight(i, v_height);
    for(int j = 0; j < columnCount(); j++)
        setColumnWidth(j, v_width);
}

void LedMatrix::createDiodes(int v_rows, int v_cols)
{
    setRowCount(v_rows);
    setColumnCount(v_cols);
    for(int i = 0; i < rowCount(); i++)
        for(int j = 0; j < columnCount(); j++)
        {
            setItem(i, j, new QTableWidgetItem());
            item(i, j)->setBackgroundColor(m_offColor);
        }
}

void LedMatrix::setDiodeState(int v_row, int v_col, bool v_state)
{
    item(v_row, v_col)->setBackgroundColor(v_state ? m_onColor : m_offColor);
}

bool LedMatrix::getDiodeState(int v_row, int v_col)
{
    return item(v_row, v_col)->backgroundColor() == m_onColor;
}

void LedMatrix::toggleDiodeState(int v_row, int v_col)
{
    if(item(v_row, v_col)->backgroundColor() == m_offColor)
        item(v_row, v_col)->setBackgroundColor(m_onColor);
    else
        item(v_row, v_col)->setBackgroundColor(m_offColor);
}

void LedMatrix::setSimFrame(const SimFrame &v_frame)
{
    for(int i = 0; i < rowCount(); i++)
        for(int j = 0; j < columnCount(); j++)
            setDiodeState(i,j,v_frame.getPixel(i,j));
}

void LedMatrix::getSimFrame(SimFrame &v_frame)
{
    for(int i = 0; i < rowCount(); i++)
        for(int j = 0; j < columnCount(); j++)
            v_frame.setPixel(i,j, getDiodeState(i,j));
}

void LedMatrix::clearDisplay()
{
    SimFrame clearFrame;
    clearFrame.clearSimFrame();
    setSimFrame(clearFrame);
}
