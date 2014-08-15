#ifndef FRAME_H
#define FRAME_H

#include <stdint.h>

#define FRAME_ROWS      8
#define FRAME_COLS      80


class Frame
{
protected:
    uint8_t m_frameData[FRAME_ROWS][FRAME_COLS/8];
    static int xLen;
    static int yLen;

public:
    Frame(void) {}
    Frame(const Frame &v_src);
    uint8_t & operator()(int row, int col);
    Frame & operator=(const Frame &v_src);
};

#endif // FRAME_H
