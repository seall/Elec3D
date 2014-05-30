
// Elec3dVisionView.h : CElec3dVisionView ��Ľӿ�
//
#include "MFC_OSG.h"  
#pragma once


class CElec3dVisionView : public CView
{
protected: // �������л�����
	CElec3dVisionView();
	DECLARE_DYNCREATE(CElec3dVisionView)

// ����
public:
	CElec3dVisionDoc* GetDocument() const;

// ����
public:
	cOSG *mOSG;  
	HANDLE mThreadHandle;


// ��д
public:
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// ʵ��
public:
	virtual ~CElec3dVisionView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	virtual void OnInitialUpdate();
	afx_msg void OnDestroy();
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
};

#ifndef _DEBUG  // Elec3dVisionView.cpp �еĵ��԰汾
inline CElec3dVisionDoc* CElec3dVisionView::GetDocument() const
   { return reinterpret_cast<CElec3dVisionDoc*>(m_pDocument); }
#endif

