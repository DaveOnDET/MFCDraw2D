#pragma once
class CPoint;
class ShapeMap;
class BaseShape;

enum EditState {
	eFail = -2,
	eCancel = -1,
	eContinue = 0,
	eComplete = 1,
	eCopy = 2,
};

enum EditCursor {
	cARROW = 0,
	cIBEAM,
	cWAIT,
	cCROSS,
	cUPARROW,
	cSIZE,
	cICON,
	cSIZENWSE,
	cSIZENESW,
	cSIZEWE,
	cSIZENS,
	cSIZEALL
};

const LPCTSTR gCURSORS[] =
{ IDC_ARROW,
IDC_IBEAM,
IDC_WAIT,
IDC_CROSS,
IDC_UPARROW,
IDC_SIZE,
IDC_ICON,
IDC_SIZENWSE,
IDC_SIZENESW,
IDC_SIZEWE,
IDC_SIZENS,
IDC_SIZEALL
};

class BaseEditor
{
public:
	~BaseEditor();
	//鼠标编辑
	int mouseEdit(int msg, CPoint point);
	//键盘编辑
	int keyEdit(int nChar, int nRepCnt, int nFlags);
	//结束编辑
	int endEdit(int state);
	//加载形状启动编辑模式
	void loadShape(BaseShape* shape);
	BaseShape* getLoadShape() { return m_selectShape; }

	bool isCreatMode() { return m_bCreating; }

	void draw(CDC* pDC);	
protected:
	BaseEditor(ShapeMap* pMap);

	//从第一次单击左键，开始编辑
	virtual int onBeginEdit(CPoint point);
	//编辑中
	virtual int onMouseEditing(int msg,CPoint point);
	//加载
	virtual void onLoadShape() {}
	//结束编辑后，子类处理
	virtual int onEndEdit();
	//重绘
	virtual void onDraw(CDC* pDC) {}
	//设置光标
	void setCursor(EditCursor cursor);
	//绘制手柄
	void onDrawHandlers(CDC* pDC);
protected:
	bool m_bCreating;
	//是否完成第一次点击事件
	bool m_bClickFirst;

	CPoint m_beginPoint;
	CPoint m_curPoint;

	BaseShape* m_selectShape;
	int m_state;
	
	ShapeMap* m_Map;

	BaseShape* m_AbsorbShape;
	CPoint m_AbsorbPt;

	CArray<CPoint> m_Handlers;
};

