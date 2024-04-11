#pragma once
#include "LineShape.h"
class TestPolyLine :
    public LineShape
{
public:
    TestPolyLine(LONG* coords,int npt);
protected:
    void OnDraw(CDC* pDC) override;
};

