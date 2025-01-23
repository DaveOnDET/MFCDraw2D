#include "pch.h"
#include "LineEditor.h"
#include "../Shapes/ShapeMap.h"
#include "../Shapes/LineShape.h"

LineEditor::LineEditor(ShapeMap* pMap):BaseEditor(pMap)
{
}

int LineEditor::onMouseEditing(int msg, CPoint point)
{
	if (m_bCreating) {
		//create line
		switch (msg) {
		case WM_LBUTTONDOWN:
			m_bClickFirst = !m_bClickFirst;
			m_firstPt = m_bClickFirst ? point : m_firstPt;
			m_secondPt = !m_bClickFirst ? point : m_secondPt;
			if (!m_bClickFirst) {
				return endEdit(EditState::eComplete);
			}
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

int LineEditor::onEndEdit()
{
	if (m_state == EditState::eComplete) {
		if (m_bCreating) {
			//create line
			auto lineShape = new LineShape(m_firstPt, m_secondPt);
			m_Map->InsertShape(lineShape);
		}
		else {						
			m_selectShape->Translate(m_curPoint.x - m_beginPoint.x, m_curPoint.y - m_beginPoint.y);
			loadShape(m_selectShape);
		}
	}
	m_bClickFirst = false;
	return m_state;
}

void LineEditor::onDraw(CDC* pDC)
{
	if (m_bClickFirst) {
		if (m_bCreating) {
			pDC->MoveTo(m_firstPt);
			pDC->LineTo(m_curPoint);
		}
		else {
			CSize offset = m_curPoint - m_beginPoint;
			pDC->MoveTo(m_firstPt + offset);
			pDC->LineTo(m_secondPt + offset);
		}
	}
}

void LineEditor::onLoadShape()
{
	auto pshape = (LineShape*)m_selectShape;
	CList<CPoint> pts;
	pshape->GetPointList(pts);
	m_firstPt = pts.GetHead();
	m_secondPt = pts.GetTail();

	//add handlers
	m_Handlers.RemoveAll();
	m_Handlers.Add(m_firstPt);
	m_Handlers.Add(m_secondPt);
}
