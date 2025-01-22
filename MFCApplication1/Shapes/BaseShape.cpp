#include "pch.h"
#include "BaseShape.h"

void BaseShape::Draw(CDC* pDC)
{
    CPen penRed;
    penRed.CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
    CPen* pOldPen = pDC->SelectObject(&penRed);
    CBrush* pOldBrush = (CBrush*)pDC->SelectStockObject(NULL_BRUSH); // ѡ��ˢ���豸�����ģ�������ɻ�ˢ    
    OnDraw(pDC);
    pDC->SelectObject(pOldPen);
    pDC->SelectObject(pOldBrush);
}

void BaseShape::DrawSelect(CDC* pDC)
{
    CPen penGreen;
    penGreen.CreatePen(PS_SOLID, 1, RGB(0, 255, 0));
    CPen* pOldPen = pDC->SelectObject(&penGreen);
    CBrush* pOldBrush = (CBrush*)pDC->SelectStockObject(NULL_BRUSH); // ѡ��ˢ���豸�����ģ�������ɻ�ˢ    
    OnDraw(pDC);
    pDC->SelectObject(pOldPen);
    pDC->SelectObject(pOldBrush);
}
