#include "pch.h"
#include "CircleShape.h"
#include "../Geomotry2d/olcUTIL_Geometry2D.h"

CircleShape::CircleShape()
{
}

CircleShape::CircleShape(CRect rect)
{
	m_rect = rect;
}

void CircleShape::Serialize(CArchive& ar)
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

BaseShape* CircleShape::Absorb(const CPoint& pt, CPoint* ptNear, float tol)
{
	olc::v_2d p(pt.x, pt.y);
	auto center = m_rect.CenterPoint();
	olc::utils::geom2d::circle<int> olcCircle({center.x,center.y}, m_rect.Width() / 2);
	auto closet= olc::utils::geom2d::closest(olcCircle, p);
	if (ptNear) {
		ptNear->x = closet.x;
		ptNear->y = closet.y;
	}
	return (closet - p).mag() < tol ? this : nullptr;
}

void CircleShape::Translate(int dx, int dy, int handle)
{
	m_rect.OffsetRect(dx, dy);
}

void CircleShape::OnDraw(CDC* pDC)
{	
	if (m_rect.IsRectEmpty())
		return;
	const float m_pi = 3.141526;
	//使用180个线段构成的多边形
	const int gSegment = 180;
	int step = 360 / gSegment;
	auto center = m_rect.CenterPoint();
	float r = m_rect.Width() / 2;
	CPoint pts[gSegment];
	for (int i = 0; i < gSegment; i++) {
		float arc = i * step * m_pi / 180.0;
		pts[i] = CPoint(center.x + cosf(arc) * r, center.y + sinf(arc) * r);
	}
	pDC->Polygon(pts, gSegment);
	//pDC->Ellipse(&m_rect);
}

IMPLEMENT_SERIAL(CircleShape, BaseShape, 1)
