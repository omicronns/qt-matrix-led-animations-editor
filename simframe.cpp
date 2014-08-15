#include "simframe.h"


SimFrame & SimFrame::operator=(const SimFrame &v_src)
{
    for(int row = 0; row < yLen; ++row)
        for(int col = 0; col < xLen; ++col)
            m_frameData[row][col] = v_src.m_frameData[row][col];
    return *this;
}


SimFrame & SimFrame::operator|=(const SimFrame &v_src)
{
    for(int row = 0; row < yLen; ++row)
        for(int col = 0; col < xLen; ++col)
            m_frameData[row][col] |= v_src.m_frameData[row][col];
    return *this;
}


SimFrame & SimFrame::operator&=(const SimFrame &v_src)
{
    for(int row = 0; row < yLen; ++row)
        for(int col = 0; col < xLen; ++col)
            m_frameData[row][col] &= v_src.m_frameData[row][col];
    return *this;
}


SimFrame & SimFrame::operator^=(const SimFrame &v_src)
{
    for(int row = 0; row < yLen; ++row)
        for(int col = 0; col < xLen; ++col)
            m_frameData[row][col] ^= v_src.m_frameData[row][col];
    return *this;
}


SimFrame & SimFrame::invert(void)
{
    for(int row = 0; row < yLen; ++row)
        for(int col = 0; col < xLen; ++col)
            m_frameData[row][col] = ~m_frameData[row][col];
    return *this;
}

SimFrame &SimFrame::clearSimFrame()
{
    for(int row = 0; row < yLen; ++row)
        for(int col = 0; col < xLen; ++col)
            m_frameData[row][col] = 0;
    return *this;
}

void SimFrame::setPixel(int v_row, int v_col, bool v_val)
{
    if(v_val)
        (*this)(v_row, v_col/8) |= (1 << (v_col % 8));
    else
        (*this)(v_row, v_col/8) &= ~(1 << (v_col % 8));
}
