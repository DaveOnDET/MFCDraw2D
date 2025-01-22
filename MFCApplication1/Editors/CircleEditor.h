#pragma once
#include "BaseEditor.h"
class CircleEditor :
    public BaseEditor
{
public:
	CircleEditor(ShapeMap* pMap);
protected:
	//�༭��
	int onMouseEditing(int msg, CPoint point)override;
	//�����༭�����ദ��
	int onEndEdit()override;
	//�ػ�
	void onDraw(CDC* pDC)override;
	void onLoadShape() override;
	inline CRect calcRect();
private:
	CPoint m_firstPt;
	CSize m_size;
};

