
// MFCGuiView.h : CMFCGuiView ��Ľӿ�
//

#pragma once

#include "MFCFamework/MFCAppDelegate.h"

class CMFCGuiView : public CView
{
protected: // �������л�����
	CMFCGuiView();
	DECLARE_DYNCREATE(CMFCGuiView)

// ����
public:
	CMFCGuiDoc* GetDocument() const;

// ����
public:
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);

protected:
	MFCAppDelegate m_app;
	bool		   m_bCreated;


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
	virtual ~CMFCGuiView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // MFCGuiView.cpp �еĵ��԰汾
inline CMFCGuiDoc* CMFCGuiView::GetDocument() const
   { return reinterpret_cast<CMFCGuiDoc*>(m_pDocument); }
#endif

