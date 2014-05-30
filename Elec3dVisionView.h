
// Elec3dVisionView.h : CElec3dVisionView 类的接口
//
#include "MFC_OSG.h"  
#pragma once


class CElec3dVisionView : public CView
{
protected: // 仅从序列化创建
	CElec3dVisionView();
	DECLARE_DYNCREATE(CElec3dVisionView)

// 特性
public:
	CElec3dVisionDoc* GetDocument() const;

// 操作
public:
	cOSG *mOSG;  
	HANDLE mThreadHandle;


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
	virtual ~CElec3dVisionView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	virtual void OnInitialUpdate();
	afx_msg void OnDestroy();
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
};

#ifndef _DEBUG  // Elec3dVisionView.cpp 中的调试版本
inline CElec3dVisionDoc* CElec3dVisionView::GetDocument() const
   { return reinterpret_cast<CElec3dVisionDoc*>(m_pDocument); }
#endif

