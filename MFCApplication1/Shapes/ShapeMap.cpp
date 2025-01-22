#include "pch.h"
#include "ShapeMap.h"

IMPLEMENT_SERIAL(ShapeMap, BaseShape, 1)

ShapeMap::~ShapeMap()
{
    Clear();
}

void ShapeMap::Serialize(CArchive& ar)
{
    CObject::Serialize(ar);
    if (ar.IsStoring())
    {
        ar << m_shapeList.GetCount();
        POSITION pos = m_shapeList.GetHeadPosition();
        while (pos != NULL)
        {
            BaseShape* shape = m_shapeList.GetNext(pos);
            ar << shape;
        }
    }
    else
    {
        Clear();
        int shapeSize = 0;
        ar >> shapeSize;
        for (int i = 0; i < shapeSize; i++){
            CObject* child = nullptr;
            ar >> child;
            auto shape = dynamic_cast<BaseShape*>(child);
            InsertShape(shape);
        }
    }
}

void ShapeMap::OnDraw(CDC* pDC)
{
    POSITION pos = m_shapeList.GetHeadPosition();
    while (pos != NULL)
    {
        m_shapeList.GetNext(pos)->Draw(pDC);
    }
}

void ShapeMap::Clear()
{
    POSITION pos = m_shapeList.GetHeadPosition();
    while (pos != NULL)
    {
        auto shape = m_shapeList.GetNext(pos);
        delete shape;
    }
    m_shapeList.RemoveAll();
}

void ShapeMap::InsertShape(BaseShape* shape)
{
    auto pos = m_shapeList.Find(shape);
    if (pos == NULL)
        m_shapeList.AddTail(shape);
}

void ShapeMap::RemoveShape(BaseShape* shape)
{
    auto pos = m_shapeList.Find(shape);
    if (pos != NULL)
        m_shapeList.RemoveAt(pos);
}

BaseShape* ShapeMap::Absorb(const CPoint& pt, CPoint* ptNear, float tol)
{
    POSITION pos = m_shapeList.GetHeadPosition();
    while (pos != NULL)
    {
        auto shape = m_shapeList.GetNext(pos);
        if (shape->Absorb(pt, ptNear, tol))
            return shape;
    }
    return nullptr;
}

CRect ShapeMap::GetRect()
{
    CRect rc;
    rc.SetRectEmpty();
    POSITION pos = m_shapeList.GetHeadPosition();
    while (pos != NULL)
    {
        auto shape = m_shapeList.GetNext(pos);       
    }
    return rc;
}
