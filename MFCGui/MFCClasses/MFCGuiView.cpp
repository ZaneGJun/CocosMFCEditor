
// MFCGuiView.cpp : CMFCGuiView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "MFCGui.h"
#endif

#include "MFCGuiDoc.h"
#include "MFCGuiView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCGuiView

IMPLEMENT_DYNCREATE(CMFCGuiView, CView)

BEGIN_MESSAGE_MAP(CMFCGuiView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CMFCGuiView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()

	ON_WM_TIMER()
	ON_WM_SIZE()
END_MESSAGE_MAP()

// CMFCGuiView 构造/析构

CMFCGuiView::CMFCGuiView() :m_bCreated(false)
{
	// TODO: 在此处添加构造代码

}

CMFCGuiView::~CMFCGuiView()
{
}

BOOL CMFCGuiView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

LRESULT CMFCGuiView::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	if (1 == m_app.WindowProc(message, wParam, lParam))
		return 1;
	return CView::WindowProc(message, wParam, lParam);
}

void CMFCGuiView::OnTimer(UINT_PTR nIDEvent)
{
	if (m_bCreated)
	{
		m_app.Run2();
	}
}

void CMFCGuiView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);

	if (cx != 0 && cy != 0)
	{

		if (!m_bCreated)
		{
			m_app.CreateWnd(m_hWnd);
			SetTimer(1, 12, NULL);
			m_bCreated = true;
		}

		m_app.Resize(cx, cy);
	}
}

// CMFCGuiView 绘制

void CMFCGuiView::OnDraw(CDC* /*pDC*/)
{
	CMFCGuiDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
}


// CMFCGuiView 打印


void CMFCGuiView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CMFCGuiView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CMFCGuiView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CMFCGuiView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}

void CMFCGuiView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CMFCGuiView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CMFCGuiView 诊断

#ifdef _DEBUG
void CMFCGuiView::AssertValid() const
{
	CView::AssertValid();
}

void CMFCGuiView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMFCGuiDoc* CMFCGuiView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMFCGuiDoc)));
	return (CMFCGuiDoc*)m_pDocument;
}
#endif //_DEBUG


// CMFCGuiView 消息处理程序
