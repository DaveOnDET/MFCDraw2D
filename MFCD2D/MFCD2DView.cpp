
// MFCD2DView.cpp: CMFCD2DView 类的实现
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "MFCD2D.h"
#endif

#include "MFCD2DDoc.h"
#include "MFCD2DView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCD2DView

IMPLEMENT_DYNCREATE(CMFCD2DView, CView)

BEGIN_MESSAGE_MAP(CMFCD2DView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CMFCD2DView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_SIZE()
	ON_REGISTERED_MESSAGE(AFX_WM_DRAW2D, &CMFCD2DView::OnAfxWmDraw2d)
END_MESSAGE_MAP()

// CMFCD2DView 构造/析构

CMFCD2DView::CMFCD2DView() noexcept
{
	// TODO: 在此处添加构造代码
	// Enable D2D support for this window:
	EnableD2DSupport();

	// Initialize D2D resources:
	m_pBlackBrush = new CD2DSolidColorBrush(
		GetRenderTarget(),
		D2D1::ColorF(D2D1::ColorF::Black));

	m_pTextFormat = new CD2DTextFormat(
		GetRenderTarget(),
		_T("Verdana"),
		50);

	m_pTextFormat->Get()->SetTextAlignment(
		DWRITE_TEXT_ALIGNMENT_CENTER);

	m_pTextFormat->Get()->SetParagraphAlignment(
		DWRITE_PARAGRAPH_ALIGNMENT_CENTER);

	D2D1_GRADIENT_STOP gradientStops[2];

	gradientStops[0].color =
		D2D1::ColorF(D2D1::ColorF::White);

	gradientStops[0].position = 0.f;
	gradientStops[1].color =
		D2D1::ColorF(D2D1::ColorF::Indigo);

	gradientStops[1].position = 1.f;

	m_pLinearGradientBrush = new CD2DLinearGradientBrush(
		GetRenderTarget(),
		gradientStops,
		ARRAYSIZE(gradientStops),
		D2D1::LinearGradientBrushProperties(
			D2D1::Point2F(0, 0),
			D2D1::Point2F(0, 0)));


	CD2DPathGeometry
}

CMFCD2DView::~CMFCD2DView()
{
}

BOOL CMFCD2DView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CMFCD2DView 绘图

void CMFCD2DView::OnDraw(CDC* /*pDC*/)
{
	CMFCD2DDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	// TODO: 在此处为本机数据添加绘制代码
}


// CMFCD2DView 打印


void CMFCD2DView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CMFCD2DView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CMFCD2DView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CMFCD2DView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}

void CMFCD2DView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CMFCD2DView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CMFCD2DView 诊断

#ifdef _DEBUG
void CMFCD2DView::AssertValid() const
{
	CView::AssertValid();
}

void CMFCD2DView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMFCD2DDoc* CMFCD2DView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMFCD2DDoc)));
	return (CMFCD2DDoc*)m_pDocument;
}
#endif //_DEBUG


// CMFCD2DView 消息处理程序


void CMFCD2DView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);
	m_pLinearGradientBrush->SetEndPoint(CPoint(cx, cy));
	// TODO: 在此处添加消息处理程序代码
}


afx_msg LRESULT CMFCD2DView::OnAfxWmDraw2d(WPARAM wParam, LPARAM lParam)
{
	CHwndRenderTarget* pRenderTarget = (CHwndRenderTarget*)lParam;
	ASSERT_VALID(pRenderTarget);

	CRect rect;
	GetClientRect(rect);

	pRenderTarget->FillRectangle(rect, m_pLinearGradientBrush);

	pRenderTarget->DrawText(
		_T("Hello, World!"),
		rect,
		m_pBlackBrush,
		m_pTextFormat);

	return TRUE;
}