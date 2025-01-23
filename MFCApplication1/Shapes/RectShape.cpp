#include "pch.h"
#include "RectShape.h"
#include "../Geomotry2d/olcUTIL_Geometry2D.h"

RectShape::RectShape()
{
}

RectShape::RectShape(CRect rect)
{
	m_rect = rect;
}

void RectShape::Serialize(CArchive& ar)
{
	CObject::Serialize(ar);
	if (ar.IsStoring())
	{
		ar << m_rect;
	}
	else
	{
		ar >> m_rect;
	}
}

BaseShape* RectShape::Absorb(const CPoint& pt, CPoint* ptNear, float tol)
{
	olc::v_2d p(pt.x, pt.y);
	auto tlp = m_rect.TopLeft();
	olc::utils::geom2d::rect<int> olcRect({ tlp.x,tlp.y },{m_rect.Width(),m_rect.Height()});
	auto closet= olc::utils::geom2d::closest(olcRect, p);
	if (ptNear) {
		ptNear->x = closet.x;
		ptNear->y = closet.y;
	}
	return (closet - p).mag() < tol ? this : nullptr;
}

void RectShape::Translate(int dx, int dy, int handle)
{
	m_rect.OffsetRect(dx, dy);
}

void RectShape::OnDraw(CDC* pDC)
{	
	if (m_rect.IsRectEmpty())
		return;
	pDC->Rectangle(m_rect);
}

IMPLEMENT_SERIAL(RectShape, BaseShape, 1)
