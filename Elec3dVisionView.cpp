
// Elec3dVisionView.cpp : CElec3dVisionView ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
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
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_KEYDOWN()
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()

// CElec3dVisionView ����/����

CElec3dVisionView::CElec3dVisionView()
{
	// TODO: �ڴ˴���ӹ������

}

CElec3dVisionView::~CElec3dVisionView()
{
}

BOOL CElec3dVisionView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CElec3dVisionView ����

void CElec3dVisionView::OnDraw(CDC* /*pDC*/)
{
	CElec3dVisionDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
}


// CElec3dVisionView ��ӡ

BOOL CElec3dVisionView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CElec3dVisionView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CElec3dVisionView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӵ�ӡ����е��������
}


// CElec3dVisionView ���

#ifdef _DEBUG
void CElec3dVisionView::AssertValid() const
{
	CView::AssertValid();
}

void CElec3dVisionView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CElec3dVisionDoc* CElec3dVisionView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CElec3dVisionDoc)));
	return (CElec3dVisionDoc*)m_pDocument;
}
#endif //_DEBUG


// CElec3dVisionView ��Ϣ�������


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
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	return TRUE;
}
