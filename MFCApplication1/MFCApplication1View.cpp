
// MFCApplication1View.cpp: CMFCApplication1View 类的实现
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "MFCApplication1.h"
#endif

#include "MFCApplication1Doc.h"
#include "MFCApplication1View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#include "Editors/Editors.h"

#include "Shapes/Shapes.h"
#include "Shapes/TestPolyLine.h"

#include <atlbase.h>
#include "../ATLProjectT/ATLProjectT_i.h"
//#import "../Debug/ATLProjectT.dll" 
// CMFCApplication1View

IMPLEMENT_DYNCREATE(CMFCApplication1View, CView)

BEGIN_MESSAGE_MAP(CMFCApplication1View, CView)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_KEYDOWN()

	ON_COMMAND(ID_PAINT_LINE, &CMFCApplication1View::OnLineToolBtn)
	ON_COMMAND(ID_PAINT_RECT, &CMFCApplication1View::OnRectToolBtn)
	ON_COMMAND(ID_PAINT_ARC, &CMFCApplication1View::OnArcToolBtn)
END_MESSAGE_MAP()

void TestComFunciton(){

	//测试com
	CoInitialize(NULL);
	CComPtr<IATLShape> pshape;
	if (SUCCEEDED(pshape.CoCreateInstance(OLESTR("Shape.import")))) {

		LONG cood[360];
		auto rs = pshape->SplitCirclePolygon180(50, 100, 100, cood);
		if (SUCCEEDED(rs)) {
			MessageBox(NULL,_T("com 调用成功"), _T("提示"),MB_OK);
		}
	}
	CoUninitialize();
}
// CMFCApplication1View 构造/析构

CMFCApplication1View::CMFCApplication1View() noexcept
{
	// TODO: 在此处添加构造代码
	m_Editor = nullptr;
	m_Map = nullptr;
}

CMFCApplication1View::~CMFCApplication1View()
{
	if (m_Editor) {
		delete m_Editor;
		m_Editor = nullptr;
	}

	m_Map = nullptr;
}

BOOL CMFCApplication1View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CMFCApplication1View 绘图


void CMFCApplication1View::OnInitialUpdate()
{
	CView::OnInitialUpdate();

	auto doc = GetDocument();
	m_Map = doc->GetShapeMap();
	assert(m_Map);
}

void CMFCApplication1View::OnDraw(CDC* pDC)
{
	CMFCApplication1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc|| m_Map==nullptr)
		return;
	m_Map->Draw(pDC);

	if (m_Editor) {
		m_Editor->draw(pDC);
	}
}

/*
void CMFCApplication1View::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint)
{// The document has informed this view that some data has changed.
	if (pHint != NULL)
	{
		if (pHint->IsKindOf(RUNTIME_CLASS(CStroke)))
		{
			// The hint is that a stroke as been added (or changed).
			// So, invalidate its rectangle.
			CStroke* pStroke = (CStroke*)pHint;
			CClientDC dc(this);
			OnPrepareDC(&dc);
			CRect rectInvalid = pStroke->GetBoundingRect();
			dc.LPtoDP(&rectInvalid);
			InvalidateRect(&rectInvalid);
			return;
		}
	}
	// We can't interpret the hint, so assume that anything might
	// have been updated.
	Invalidate(TRUE);
	return;
}*/

void CMFCApplication1View::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CMFCApplication1View::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CMFCApplication1View 诊断

#ifdef _DEBUG
void CMFCApplication1View::AssertValid() const
{
	CView::AssertValid();
}

void CMFCApplication1View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

void CMFCApplication1View::setEditor(BaseEditor* editor)
{
	if (m_Editor) {
		delete m_Editor;
		m_Editor = nullptr;
	}
	m_Editor = editor;
}

CMFCApplication1Doc* CMFCApplication1View::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMFCApplication1Doc)));
	return (CMFCApplication1Doc*)m_pDocument;
}
#endif //_DEBUG


// CMFCApplication1View 消息处理程序

void CMFCApplication1View::OnLineToolBtn()
{
	if (m_Map == nullptr)
		return;
	auto editor = new LineEditor(m_Map);
	setEditor(editor);
}

void CMFCApplication1View::OnRectToolBtn()
{
	if (m_Map == nullptr)
		return;
	auto editor = new RectEditor(m_Map);
	setEditor(editor);
}

void CMFCApplication1View::OnArcToolBtn()
{
	if (m_Map == nullptr)
		return;
	auto editor = new CircleEditor(m_Map);
	setEditor(editor);
}


void CMFCApplication1View::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	//通过框架获取状态栏
	auto wnd =AfxGetMainWnd()->GetDescendantWindow(AFX_IDW_STATUS_BAR);
	CMFCStatusBar* bar = dynamic_cast<CMFCStatusBar*>(wnd);
	if (bar != nullptr) {
		//显示坐标信息到状态栏
		CString str;
		//bar->SetPaneInfo(1, IDS_TEST_BAR, SBPS_POPOUT, 150);
		str.Format(_T("X:%d,Y:%d"), point.x, point.y);
		bar->SetPaneText(0, str);
		bar->SetPaneText(1, _T("ffffffffff"));
	}
	if (m_Editor)
	{
		CClientDC dc(this);
		//OnPrepareDC(&dc);
		//dc.DPtoLP(&point);
		m_Editor->mouseEdit(WM_MOUSEMOVE, point);
		Invalidate();
	}
	else
		CView::OnMouseMove(nFlags, point);
}


void CMFCApplication1View::OnLButtonDown(UINT nFlags, CPoint point)
{
	//拾取测试编辑器
	if (!m_Map)
		return;
	//创建模式
	if (m_Editor&& m_Editor->isCreatMode()) {
		m_Editor->mouseEdit(WM_LBUTTONDOWN, point);		
		return;
	}
	setEditor(nullptr);
	BaseShape* bShape = m_Map->Absorb(point, nullptr);
	BaseEditor* edtor = nullptr;
	if (bShape && bShape->IsKindOf(LineShape::GetThisClass())) {
		//创建编辑器
		edtor = new LineEditor(m_Map);
	}
	else if (bShape && bShape->IsKindOf(CircleShape::GetThisClass())) {
		//创建编辑器
		edtor = new CircleEditor(m_Map);
	}
	else if (bShape && bShape->IsKindOf(RectShape::GetThisClass())) {
		//创建编辑器
		edtor = new RectEditor(m_Map);
	}
	if (edtor) {
		edtor->loadShape(bShape);
		setEditor(edtor);
		edtor->mouseEdit(WM_LBUTTONDOWN, point);
		Invalidate();
	}
	else
		CView::OnLButtonDown(nFlags, point);

}


void CMFCApplication1View::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (m_Editor) {
		m_Editor->mouseEdit(WM_LBUTTONUP, point);
		Invalidate();
	}
	else
		CView::OnLButtonUp(nFlags, point);
}


void CMFCApplication1View::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (m_Editor) {
		// 判断特定的按键
		if (nChar == VK_ESCAPE)
		{
			// 用户按下了esc
			TRACE(_T("ESC键被按下\n"));
			m_Editor->endEdit(EditState::eCancel);
			setEditor(nullptr);
			Invalidate();
		}
		// 判断特定的按键
		else if (!m_Editor->isCreatMode() && nChar == VK_DELETE)
		{
			// 用户按下了删除键
			TRACE(_T("删除键\n"));
			m_Map->RemoveShape(m_Editor->getLoadShape());
			setEditor(nullptr);
			Invalidate();
		}
		else
			m_Editor->keyEdit(nChar, nRepCnt, nFlags);
	}
	else
		CView::OnKeyDown(nChar, nRepCnt, nFlags);
}
