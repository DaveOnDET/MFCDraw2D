
// MFCD2DView.h: CMFCD2DView 类的接口
//

#pragma once


class CMFCD2DView : public CView
{
protected: // 仅从序列化创建
	CMFCD2DView() noexcept;
	DECLARE_DYNCREATE(CMFCD2DView)

// 特性
public:
	CMFCD2DDoc* GetDocument() const;

// 操作
public:

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 实现
public:
	virtual ~CMFCD2DView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()

private:
	//direct2d api对象
	CD2DTextFormat* m_pTextFormat;
	CD2DSolidColorBrush* m_pBlackBrush;
	CD2DLinearGradientBrush* m_pLinearGradientBrush;
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
protected:
	afx_msg LRESULT OnAfxWmDraw2d(WPARAM wParam, LPARAM lParam);
};

#ifndef _DEBUG  // MFCD2DView.cpp 中的调试版本
inline CMFCD2DDoc* CMFCD2DView::GetDocument() const
   { return reinterpret_cast<CMFCD2DDoc*>(m_pDocument); }
#endif
