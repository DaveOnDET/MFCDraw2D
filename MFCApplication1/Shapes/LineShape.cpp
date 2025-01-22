#include "pch.h"
#include "LineShape.h"
#include "../Geomotry2d/olcUTIL_Geometry2D.h"


LineShape::LineShape()
{
}

LineShape::LineShape(CPoint pt1, CPoint pt2)
{
	m_ptList.AddTail(pt1);
	m_ptList.AddTail(pt2);
}

void LineShape::Serialize(CArchive& ar)
{
	CObject::Serialize(ar);
	if (ar.IsStoring())
	{
		ar << m_ptList.GetCount();
		POSITION pos = m_ptList.GetHeadPosition();
		while (pos != NULL)
		{
			const CPoint& pt = m_ptList.GetNext(pos);
			ar << pt;
		}
	}
	else
	{
		int npt = 0; 
		ar >> npt;
		for (int i = 0; i < npt; i++)
		{
			CPoint pt;
			ar >> pt;
			m_ptList.AddTail(pt);
		}
	}
}

BaseShape* LineShape::Absorb(const CPoint& pt, CPoint* ptNear, float tol)
{
	olc::v_2d p(pt.x, pt.y);
	auto h= m_ptList.GetHead();
	auto e = m_ptList.GetTail();
	olc::utils::geom2d::line<int> olcLine({ h.x,h.y }, { e.x,e.y });
	auto closet = olc::utils::geom2d::closest(olcLine, p);
	if (ptNear) {
		ptNear->x = closet.x;
		ptNear->y = closet.y;
	}
	return (closet - p).mag() < tol ? this : nullptr;
}

void LineShape::Translate(int dx, int dy,int handle)
{
	POSITION pos = m_ptList.GetHeadPosition();
	while (pos != NULL)
	{
		CPoint& pt = m_ptList.GetNext(pos);
		pt.Offset(dx, dy);
	}
}

void LineShape::GetPointList(CList<CPoint>& pts)
{
	POSITION hpos = m_ptList.GetHeadPosition();
	while (hpos != NULL)
		pts.AddTail(m_ptList.GetNext(hpos));
}

CRect LineShape::GetRect()
{
	CRect rc;
	rc.SetRectEmpty();
	int minx = 99999;
	int maxx = -1;
	int miny = minx;
	int maxy = maxx;
	POSITION hpos = m_ptList.GetHeadPosition();
	while (hpos != NULL)
	{
		auto pt = m_ptList.GetNext(hpos);
		minx = min(pt.x, minx);
		maxx = max(pt.x, maxx);
		miny = min(pt.y, miny);
		maxy = max(pt.y, maxy);
	}
	rc.SetRect(minx, miny, maxx, maxy);
	return rc;
}

void LineShape::OnDraw(CDC* pDC)
{
	pDC->MoveTo(m_ptList.GetHead());
	POSITION hpos = m_ptList.GetHeadPosition();
	while (hpos != NULL)
		pDC->LineTo(m_ptList.GetNext(hpos));
}

IMPLEMENT_SERIAL(LineShape, BaseShape, 1)
