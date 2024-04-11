#pragma once
#include "BaseEditor.h"
class CircleEditor :
    public BaseEditor
{
public:
	CircleEditor(ShapeMap* pMap);
protected:
	//编辑中
	int onMouseEditing(int msg, CPoint point)override;
	//结束编辑后，子类处理
	int onEndEdit()override;
	//重绘
	void onDraw(CDC* pDC)override;
	void onLoadShape() override;
	inline CRect calcRect();
private:
	CPoint m_firstPt;
	CSize m_size;
};

