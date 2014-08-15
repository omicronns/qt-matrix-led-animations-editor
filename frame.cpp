#include "frame.h"


int Frame::xLen = FRAME_COLS/8;
int Frame::yLen = FRAME_ROWS;



uint8_t & Frame::operator()(int row, int col)
{
    return m_frameData[row][col];
}

Frame::Frame(const Frame &v_src)
{
    for(int row = 0; row < yLen; ++row)
        for(int col = 0; col < xLen; ++col)
            m_frameData[row][col] = v_src.m_frameData[row][col];
}

Frame & Frame::operator=(const Frame &v_src)
{
    for(int row = 0; row < yLen; ++row)
        for(int col = 0; col < xLen; ++col)
            m_frameData[row][col] = v_src.m_frameData[row][col];
    return *this;
}
