#pragma once
#include "BaseEditor.h"
class LineEditor :
    public BaseEditor
{

public:
	LineEditor(ShapeMap* pMap);
protected:

	//编辑中
	int onMouseEditing(int msg, CPoint point)override;
	//结束编辑后，子类处理
	int onEndEdit()override;
	//重绘
	void onDraw(CDC* pDC)override;
	//加载
	void onLoadShape() override;
private:
	CPoint m_firstPt;
	CPoint m_secondPt;
};

