#include "pch.h"
#include "CircleEditor.h"
#include "../Shapes/ShapeMap.h"
#include "../Shapes/CircleShape.h"

inline int Distance(const CPoint& p0, const CPoint& p1) {
	auto size = p1 - p0;
	return (int)sqrt(size.cx * size.cx + size.cy * size.cy);
}

CircleEditor::CircleEditor(ShapeMap* pMap) :BaseEditor(pMap)
{
	m_bClickFirst = false;
}

int CircleEditor::onMouseEditing(int msg, CPoint point)
{
	if (m_bCreating) {
		int r = m_size.cx;
		switch (msg) {
		case WM_LBUTTONDOWN:
			m_size = !m_bClickFirst ? CSize() : m_size;
			m_bClickFirst = !m_bClickFirst;
			m_firstPt = m_bClickFirst ? point : m_firstPt;
			if (!m_bClickFirst) {
				return endEdit(EditState::eComplete);
			}
			break;
		case WM_MOUSEMOVE:
			r = m_bClickFirst ? Distance(point, m_firstPt) : r;
			m_size = m_bClickFirst ? CSize(r, r) : m_size;
			break;
		default:
			break;
		}
		return m_state = EditState::eContinue;
	}
	else {
		return m_state = BaseEditor::onMouseEditing(msg, point);
	}
}

int CircleEditor::onEndEdit()
{
	if (m_state == EditState::eComplete) {
		if (m_bCreating) {
			//create line
			auto circleRect = calcRect();
			auto shape = new CircleShape(circleRect);
			m_Map->InsertShape(shape);
		}
		else {
			m_selectShape->Translate(m_curPoint.x - m_beginPoint.x, m_curPoint.y - m_beginPoint.y);
			loadShape(m_selectShape);
		}
	}
	m_bClickFirst = false;
	return m_state;
}

void CircleEditor::onDraw(CDC* pDC)
{
	if (m_bClickFirst) {		
		CRect circleRect = calcRect();
		if (!m_bCreating) {
			circleRect.OffsetRect(m_curPoint - m_beginPoint);
		}
	    pDC->Ellipse(&circleRect);
	}
}

void CircleEditor::onLoadShape()
{
	auto rect = m_selectShape->GetRect();
	m_firstPt = rect.CenterPoint();
	m_size = CSize(rect.Width() / 2, rect.Height() / 2);	
	//add handlers
	m_Handlers.RemoveAll();
	m_Handlers.Add(CPoint(rect.left, m_firstPt.y));
	m_Handlers.Add(CPoint(rect.right, m_firstPt.y));
	m_Handlers.Add(CPoint(m_firstPt.x, rect.top));
	m_Handlers.Add(CPoint(m_firstPt.x, rect.bottom));
}

CRect CircleEditor::calcRect()
{
	// 创建一个矩形，该矩形的宽度和高度相等，以定义圆的边界  
	CRect circleRect(m_firstPt.x - m_size.cx, m_firstPt.y - m_size.cy, m_firstPt.x + m_size.cx, m_firstPt.y + m_size.cy);
	return circleRect;
}
