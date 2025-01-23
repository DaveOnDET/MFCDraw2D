#include "pch.h"
#include "RectEditor.h"
#include "../Shapes/ShapeMap.h"
#include "../Shapes/RectShape.h"


RectEditor::RectEditor(ShapeMap* pMap) :BaseEditor(pMap)
{
	m_bClickFirst = false;
}

int RectEditor::onMouseEditing(int msg, CPoint point)
{
	if (m_bCreating) {
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
			m_size = m_bClickFirst ? point-m_firstPt : m_size;
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

int RectEditor::onEndEdit()
{
	if (m_state == EditState::eComplete) {
		if (m_bCreating) {
			auto aRect = calcRect();
			auto shape = new RectShape(aRect);
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

void RectEditor::onDraw(CDC* pDC)
{
	if (m_bClickFirst) {		
		CRect aRect = calcRect();
		if (!m_bCreating) {
			aRect.OffsetRect(m_curPoint - m_beginPoint);
		}		
	    pDC->Rectangle(&aRect);
	}
}

void RectEditor::onLoadShape()
{
	auto rect = m_selectShape->GetRect();
	m_firstPt = rect.TopLeft();
	m_size = rect.Size();
	//add handlers
	m_Handlers.RemoveAll();
	m_Handlers.Add(CPoint(rect.left, rect.top));
	m_Handlers.Add(CPoint(rect.right, rect.top));
	m_Handlers.Add(CPoint(rect.left, rect.bottom));
	m_Handlers.Add(CPoint(rect.right, rect.bottom));
}

CRect RectEditor::calcRect()
{
	// 创建一个矩形
	CRect aRect(m_firstPt, m_size);
	if (aRect.left > aRect.right)
		aRect.SwapLeftRight();
	if (aRect.top > aRect.bottom)
	{
		int bot = aRect.bottom;
		aRect.bottom = aRect.top;
		aRect.top = bot;
	}
	return aRect;
}
