
// Elec3dVisionView.cpp : CElec3dVisionView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "Elec3dVision.h"
#endif

#include "Elec3dVisionDoc.h"
#include "Elec3dVisionView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CElec3dVisionView

IMPLEMENT_DYNCREATE(CElec3dVisionView, CView)

BEGIN_MESSAGE_MAP(CElec3dVisionView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_KEYDOWN()
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()

// CElec3dVisionView 构造/析构

CElec3dVisionView::CElec3dVisionView()
{
	// TODO: 在此处添加构造代码

}

CElec3dVisionView::~CElec3dVisionView()
{
}

BOOL CElec3dVisionView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CElec3dVisionView 绘制

void CElec3dVisionView::OnDraw(CDC* /*pDC*/)
{
	CElec3dVisionDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
}


// CElec3dVisionView 打印

BOOL CElec3dVisionView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CElec3dVisionView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CElec3dVisionView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}


// CElec3dVisionView 诊断

#ifdef _DEBUG
void CElec3dVisionView::AssertValid() const
{
	CView::AssertValid();
}

void CElec3dVisionView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CElec3dVisionDoc* CElec3dVisionView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CElec3dVisionDoc)));
	return (CElec3dVisionDoc*)m_pDocument;
}
#endif //_DEBUG


// CElec3dVisionView 消息处理程序


int CElec3dVisionView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	mOSG = new cOSG(m_hWnd);

	return 1;
}


void CElec3dVisionView::OnInitialUpdate()
{
	CView::OnInitialUpdate();

	mOSG->InitOSG("test.ive");
	mThreadHandle = (HANDLE)_beginthread(&cOSG::Render,0,mOSG);
}


void CElec3dVisionView::OnDestroy()
{
	if(mOSG != 0) delete mOSG;

	WaitForSingleObject(mThreadHandle, 1000);

	CView::OnDestroy();
}


void CElec3dVisionView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	mOSG->getViewer()->getEventQueue()->keyPress(nChar);

	// Close Window on Escape Key
	if(nChar == VK_ESCAPE)
	{
		GetParent()->SendMessage(WM_CLOSE);
	}
}


BOOL CElec3dVisionView::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	return TRUE;
}
