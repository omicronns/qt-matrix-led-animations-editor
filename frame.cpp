#include "frame.h"

int Frame::xLen = FRAME_COLS/8;
int Frame::yLen = FRAME_ROWS;

void Frame::setByte(int v_row, int v_col, uint8_t v_data)
{
    m_frameData[v_row][v_col] = v_data;
}

uint8_t Frame::getByte(int v_row, int v_col) const
{
    return m_frameData[v_row][v_col];
}
