#pragma once
#include "BaseEditor.h"
class LineEditor :
    public BaseEditor
{

public:
	LineEditor(ShapeMap* pMap);
protected:

	//�༭��
	int onMouseEditing(int msg, CPoint point)override;
	//�����༭�����ദ��
	int onEndEdit()override;
	//�ػ�
	void onDraw(CDC* pDC)override;
	//����
	void onLoadShape() override;
private:
	CPoint m_firstPt;
	CPoint m_secondPt;
};

