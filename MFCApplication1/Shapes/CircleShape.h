#pragma once
#include "BaseShape.h"
class CircleShape :
    public BaseShape
{
public:
    CircleShape();
    CircleShape(CRect rect);
public:
    void Serialize(CArchive& ar)override;
    BaseShape* Absorb(const CPoint& pt, CPoint* ptNear, float tol)override;
    void Translate(int dx, int dy, int handle) override;
    CRect GetRect() override { return m_rect; }
protected:
    DECLARE_SERIAL(CircleShape)
    void OnDraw(CDC* pDC) override;
private:
    CRect m_rect;
};

