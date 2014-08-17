#ifndef SIMFRAME_H
#define SIMFRAME_H

#include <stdint.h>
#include "frame.h"

class SimFrame : public Frame
{
public:
    SimFrame(void);
    SimFrame & operator=(const SimFrame &v_src);
    SimFrame & operator|=(const SimFrame &v_src);
    SimFrame & operator&=(const SimFrame &v_src);
    SimFrame & operator^=(const SimFrame &v_src);
    SimFrame & invert(void);
    SimFrame & clearSimFrame(void);
    void setPixel(int v_row, int v_col, bool v_val);
    bool getPixel(int v_row, int v_col) const;
    int rows(void) const;
    int cols(void) const;
};

#endif // SIMFRAME_H
