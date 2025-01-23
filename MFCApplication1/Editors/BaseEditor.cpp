#include "pch.h"
#include "BaseEditor.h"
#include "../Shapes/ShapeMap.h"
#include "../Shapes/BaseShape.h"

int BaseEditor::mouseEdit(int msg, CPoint point)
{
    setCursor(EditCursor::cCROSS);
    //当前点
    m_curPoint = point;
    if (msg==WM_LBUTTONDOWN&& m_state != EditState::eContinue) {
        m_beginPoint = point;
        m_bClickFirst = true;
        TRACE("BEGIN edit\n");
        return onBeginEdit(point);
    }
    //开启吸附
    m_AbsorbShape = m_Map->Absorb(point, &m_AbsorbPt);
    if (m_AbsorbShape == nullptr)
        m_AbsorbPt = point;

    return onMouseEditing(msg, m_AbsorbPt);
}

int BaseEditor::endEdit(int state)
{
    m_state = state;
    return onEndEdit();
}

void BaseEditor::loadShape(BaseShape* shape)
{
    m_bCreating = false;
    m_selectShape = shape;
    onLoadShape();
}

void BaseEditor::draw(CDC* pDC)
{
    // Make a couple of pens.
    CPen penRed;
    penRed.CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
    CPen* pOldPen = pDC->SelectObject(&penRed);
    //绘制吸附点
    const int MarkRadius = 5;
    CRect absRect(m_AbsorbPt.x - MarkRadius, m_AbsorbPt.y - MarkRadius, m_AbsorbPt.x + MarkRadius, m_AbsorbPt.y + MarkRadius);
    pDC->Ellipse(absRect);
    if (m_AbsorbShape != nullptr)
    {
        m_AbsorbShape->DrawSelect(pDC);
    }
    // 创建一个透明画刷，用于内部不被填充    
    CBrush* pOldBrush = (CBrush*)pDC->SelectStockObject(NULL_BRUSH); // 选择画刷到设备上下文，并保存旧画刷    
    onDraw(pDC);
    pDC->SelectObject(pOldPen);
    pDC->SelectObject(pOldBrush);
    //绘制手柄
    onDrawHandlers(pDC);
}

int BaseEditor::keyEdit(int nChar, int nRepCnt, int nFlags)
{
    // 判断特定的按键
    if (nChar == VK_ESCAPE)
    {
        // 用户按下了左箭头键
        TRACE(_T("ESC键被按下\n"));
        return endEdit(EditState::eCancel);
    }  
    return  m_state = EditState::eContinue;
}

BaseEditor::BaseEditor(ShapeMap* pMap)
{
    m_bClickFirst = false;
    m_Map = pMap; 
    m_selectShape = nullptr;
    m_bCreating = true; 
    m_state = EditState::eCancel;
    m_AbsorbShape = nullptr;
}

BaseEditor::~BaseEditor()
{
    m_selectShape = nullptr;
    m_AbsorbShape = nullptr;
    setCursor(EditCursor::cARROW);
}

int BaseEditor::onBeginEdit(CPoint point)
{
    return m_state = EditState::eContinue;
}
int BaseEditor::onMouseEditing(int msg, CPoint point)
{
    //move line
    switch (msg) {
    case WM_LBUTTONUP:
        return endEdit(EditState::eComplete);
    default:
        break;
    }
    return m_bClickFirst ? m_state = EditState::eContinue : m_state;
}
int BaseEditor::onEndEdit()
{
    return m_state;
}

void BaseEditor::setCursor(EditCursor id)
{
    auto hcur=AfxGetApp()->LoadStandardCursor(gCURSORS[id]);
    SetCursor(hcur);
}

void BaseEditor::onDrawHandlers(CDC* pDC)
{ // Make a couple of pens.
    CPen penGrey;
    penGrey.CreatePen(PS_SOLID, 1, RGB(125, 125, 125));
    CPen* pOldPen = pDC->SelectObject(&penGrey);
    const int MarkRadius = 5;
    for (int i = 0; i < m_Handlers.GetCount(); i++)
    {
        CRect absRect(m_Handlers[i].x - MarkRadius, m_Handlers[i].y - MarkRadius, m_Handlers[i].x + MarkRadius, m_Handlers[i].y + MarkRadius);
        pDC->Ellipse(absRect);
    }
    pDC->SelectObject(pOldPen);
}
