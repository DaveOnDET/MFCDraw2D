// ATLShape.cpp: CATLShape 的实现

#include "pch.h"
#include "ATLShape.h"


// CATLShape


STDMETHODIMP CATLShape::TestAdd(FLOAT a, FLOAT b)
{
	// TODO: 在此处添加实现代码

	return S_OK;
}


STDMETHODIMP CATLShape::SplitCirclePolygon180(LONG r, LONG cx, LONG cy, LONG* pCoord)
{
	// TODO: 在此处添加实现代码
	const float m_pi = 3.141526;
	//使用180个线段构成的多边形
	const int gSegment = 180;
	int step = 360 / gSegment;
	for (int i = 0; i < gSegment; i++) {
		float arc = i * step * m_pi / 180.0f;
		pCoord[2 * i] = cx + cosf(arc) * r;
		pCoord[2 * i + 1] = cy + sinf(arc) * r;
	}
	return S_OK;
}
