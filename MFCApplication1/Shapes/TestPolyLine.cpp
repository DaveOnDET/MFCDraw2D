#include "pch.h"
#include "TestPolyLine.h"

TestPolyLine::TestPolyLine(LONG* coords,int npt)
{
	for (int i = 0; i < npt; i++) {
		m_ptList.AddTail(CPoint(coords[2 * i], coords[2 * i + 1]));
	}
}

void TestPolyLine::OnDraw(CDC* pDC)
{
	pDC->MoveTo(m_ptList.GetHead());
	POSITION hpos = m_ptList.GetHeadPosition();
	while (hpos != NULL)
		pDC->LineTo(m_ptList.GetNext(hpos));
	pDC->LineTo(m_ptList.GetHead());
}

