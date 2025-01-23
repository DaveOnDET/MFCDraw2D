#pragma once
#include "BaseShape.h"
class RectShape :
    public BaseShape
{
public:
    RectShape();
    RectShape(CRect rect);
public:
    void Serialize(CArchive& ar)override;
    BaseShape* Absorb(const CPoint& pt, CPoint* ptNear, float tol)override;
    void Translate(int dx, int dy, int handle) override;
    CRect GetRect() override { return m_rect; }
protected:
    DECLARE_SERIAL(RectShape)
    void OnDraw(CDC* pDC) override;
private:
    CRect m_rect;
};

