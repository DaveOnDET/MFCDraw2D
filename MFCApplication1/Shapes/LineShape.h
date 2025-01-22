#pragma once
#include "BaseShape.h"
class LineShape :
    public BaseShape
{
public:
    LineShape();
    LineShape(CPoint pt1, CPoint pt2);
public:
    void Serialize(CArchive& ar)override;
    BaseShape* Absorb(const CPoint& pt, CPoint* ptNear, float tol)override;
    void Translate(int dx, int dy, int handle) override;
    //获取点数据
    void GetPointList(CList<CPoint>&pts);
    CRect GetRect() override;
protected:
    void OnDraw(CDC* pDC) override;

protected:
    DECLARE_SERIAL(LineShape)

    CList<CPoint> m_ptList;
};

