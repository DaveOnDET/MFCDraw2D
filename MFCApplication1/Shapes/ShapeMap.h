#pragma once
#include "BaseShape.h"
class ShapeMap :
    public BaseShape
{

public:
    ~ShapeMap();
    void Serialize(CArchive& ar)override;
    //insert shape
    void InsertShape(BaseShape* shape);
    void RemoveShape(BaseShape* shape);
    BaseShape* Absorb(const CPoint& pt, CPoint* ptNear,float tol = 5.f)override;

    CRect GetRect() override;
protected:
    DECLARE_SERIAL(ShapeMap)

    void OnDraw(CDC* pDC) override;
    void Clear();
private:
    CList<BaseShape*> m_shapeList;
};

