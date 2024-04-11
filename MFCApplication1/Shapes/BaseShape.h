#pragma once

class BaseShape : public CObject
{
	// ...Member functions
public:
	BaseShape() {}

	//get rect of shape
	virtual CRect GetRect() { CRect rc; rc.SetRectEmpty(); return rc; }
	//convert to segments
	virtual BaseShape* Absorb(const CPoint& pt, CPoint* ptNear, float tol) { return nullptr; }
	// Implementation
	void Draw(CDC* pDC);
	// Implementation
	void DrawSelect(CDC* pDC);
	// make translate by handle(-1 body)
	virtual void Translate(int dx,int dy,int handle=-1){}
protected:
	virtual void OnDraw(CDC* pDC) {}
};