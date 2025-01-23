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
	//���༭
	int mouseEdit(int msg, CPoint point);
	//���̱༭
	int keyEdit(int nChar, int nRepCnt, int nFlags);
	//�����༭
	int endEdit(int state);
	//������״�����༭ģʽ
	void loadShape(BaseShape* shape);
	BaseShape* getLoadShape() { return m_selectShape; }

	bool isCreatMode() { return m_bCreating; }

	void draw(CDC* pDC);	
protected:
	BaseEditor(ShapeMap* pMap);

	//�ӵ�һ�ε����������ʼ�༭
	virtual int onBeginEdit(CPoint point);
	//�༭��
	virtual int onMouseEditing(int msg,CPoint point);
	//����
	virtual void onLoadShape() {}
	//�����༭�����ദ��
	virtual int onEndEdit();
	//�ػ�
	virtual void onDraw(CDC* pDC) {}
	//���ù��
	void setCursor(EditCursor cursor);
	//�����ֱ�
	void onDrawHandlers(CDC* pDC);
protected:
	bool m_bCreating;
	//�Ƿ���ɵ�һ�ε���¼�
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

