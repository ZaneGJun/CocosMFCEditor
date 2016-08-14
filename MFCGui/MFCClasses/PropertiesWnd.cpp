
#include "stdafx.h"

#include "PropertiesWnd.h"
#include "Resource.h"
#include "MainFrm.h"
#include "MFCGui.h"
#include "MFCFamework/MFCHelper.h"
#include "MyUtils.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

/////////////////////////////////////////////////////////////////////////////
// CResourceViewBar

CPropertiesWnd::CPropertiesWnd()
{
	m_nComboHeight = 0;
}

CPropertiesWnd::~CPropertiesWnd()
{
}

void CPropertiesWnd::reset()
{
	m_basePropertInfo.posX = 0.0f;
	m_basePropertInfo.posY = 0.0f;
	m_basePropertInfo.posZ = 0.0f;
	m_basePropertInfo.rotX = 0.0f;
	m_basePropertInfo.rotY = 0.0f;
	m_basePropertInfo.rotZ = 0.0f;
	m_basePropertInfo.scaleX = 1.0f;
	m_basePropertInfo.scaleY = 1.0f;
	m_basePropertInfo.scaleZ = 1.0f;

	m_modelAnimateInfo.path = "";
	m_modelAnimateInfo.rate = 24;
	m_modelAnimateInfo.startframe = 0;
	m_modelAnimateInfo.endframe = 1;

	m_modelMaterialInfo.path = "";
	m_modelMaterialInfo.technique = "";

	m_wndPropList.RemoveAll();
	InitPropList();
}

BEGIN_MESSAGE_MAP(CPropertiesWnd, CDockablePane)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_COMMAND(ID_EXPAND_ALL, OnExpandAllProperties)
	ON_UPDATE_COMMAND_UI(ID_EXPAND_ALL, OnUpdateExpandAllProperties)
	ON_COMMAND(ID_SORTPROPERTIES, OnSortProperties)
	ON_UPDATE_COMMAND_UI(ID_SORTPROPERTIES, OnUpdateSortProperties)
	ON_COMMAND(ID_PROPERTIES1, OnProperties1)
	ON_UPDATE_COMMAND_UI(ID_PROPERTIES1, OnUpdateProperties1)
	ON_COMMAND(ID_PROPERTIES2, OnProperties2)
	ON_UPDATE_COMMAND_UI(ID_PROPERTIES2, OnUpdateProperties2)
	ON_WM_SETFOCUS()
	ON_WM_SETTINGCHANGE()

	ON_REGISTERED_MESSAGE(AFX_WM_PROPERTY_CHANGED, OnPropertyChanged)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CResourceViewBar 消息处理程序

void CPropertiesWnd::AdjustLayout()
{
	if (GetSafeHwnd () == NULL || (AfxGetMainWnd() != NULL && AfxGetMainWnd()->IsIconic()))
	{
		return;
	}

	CRect rectClient;
	GetClientRect(rectClient);

	int cyTlb = 0;
	m_wndPropList.SetWindowPos(NULL, rectClient.left, rectClient.top + m_nComboHeight + cyTlb, rectClient.Width(), rectClient.Height() -(m_nComboHeight+cyTlb), SWP_NOACTIVATE | SWP_NOZORDER);
}

int CPropertiesWnd::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDockablePane::OnCreate(lpCreateStruct) == -1)
		return -1;

	CRect rectDummy;
	rectDummy.SetRectEmpty();

	if (!m_wndPropList.Create(WS_VISIBLE | WS_CHILD, rectDummy, this, 2))
	{
		TRACE0("未能创建属性网格\n");
		return -1;      // 未能创建
	}

	InitPropList();

	AdjustLayout();
	return 0;
}

void CPropertiesWnd::OnSize(UINT nType, int cx, int cy)
{
	CDockablePane::OnSize(nType, cx, cy);
	AdjustLayout();
}

void CPropertiesWnd::OnExpandAllProperties()
{
	m_wndPropList.ExpandAll();
}

void CPropertiesWnd::OnUpdateExpandAllProperties(CCmdUI* /* pCmdUI */)
{
}

void CPropertiesWnd::OnSortProperties()
{
	m_wndPropList.SetAlphabeticMode(!m_wndPropList.IsAlphabeticMode());
}

void CPropertiesWnd::OnUpdateSortProperties(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_wndPropList.IsAlphabeticMode());
}

void CPropertiesWnd::OnProperties1()
{
	// TODO: 在此处添加命令处理程序代码
}

void CPropertiesWnd::OnUpdateProperties1(CCmdUI* /*pCmdUI*/)
{
	// TODO: 在此处添加命令更新 UI 处理程序代码
}

void CPropertiesWnd::OnProperties2()
{
	// TODO: 在此处添加命令处理程序代码
}

void CPropertiesWnd::OnUpdateProperties2(CCmdUI* /*pCmdUI*/)
{
	// TODO: 在此处添加命令更新 UI 处理程序代码
}

void CPropertiesWnd::InitPropList()
{
	SetPropListFont();

	m_wndPropList.EnableHeaderCtrl(TRUE);
	m_wndPropList.EnableDescriptionArea();
	m_wndPropList.SetVSDotNetLook();
	m_wndPropList.MarkModifiedProperties();

	CMFCPropertyGridProperty* pProt= nullptr;
	std::string resourcePath = MyUtils::getCheckPath();
	std::wstring resourcePathW = MyUtils::s2w(resourcePath);
	
	//基础
	CMFCPropertyGridProperty* pBase = new CMFCPropertyGridProperty(_T("基础"));
	pProt = new CMFCPropertyGridProperty(_T("位置"), NULL, NULL);
	pProt->AddSubItem(new CMFCPropertyGridProperty(_T("posX"), (float)m_basePropertInfo.posX, _T("positon.x"), MFC_PROPERTY_BASE_POS_X));
	pProt->AddSubItem(new CMFCPropertyGridProperty(_T("posY"), (float)m_basePropertInfo.posY, _T("positon.y"), MFC_PROPERTY_BASE_POS_Y));
	pProt->AddSubItem(new CMFCPropertyGridProperty(_T("posZ"), (float)m_basePropertInfo.posZ, _T("positon.z"), MFC_PROPERTY_BASE_POS_Z));
	pBase->AddSubItem(pProt);
	pProt = new CMFCPropertyGridProperty(_T("旋转"), NULL, NULL);
	pProt->AddSubItem(new CMFCPropertyGridProperty(_T("rotX"), (float)m_basePropertInfo.rotX, _T("rotation.x"), MFC_PROPERTY_BASE_ROT_X));
	pProt->AddSubItem(new CMFCPropertyGridProperty(_T("rotY"), (float)m_basePropertInfo.rotY, _T("rotation.y"), MFC_PROPERTY_BASE_ROT_Y));
	pProt->AddSubItem(new CMFCPropertyGridProperty(_T("rotZ"), (float)m_basePropertInfo.rotZ, _T("rotation.z"), MFC_PROPERTY_BASE_ROT_Z));
	pBase->AddSubItem(pProt);
	pProt = new CMFCPropertyGridProperty(_T("缩放"), NULL, NULL);
	pProt->AddSubItem(new CMFCPropertyGridProperty(_T("scaleX"), (float)m_basePropertInfo.scaleX, _T("scale.x"), MFC_PROPERTY_BASE_SCALE_X));
	pProt->AddSubItem(new CMFCPropertyGridProperty(_T("scaleY"), (float)m_basePropertInfo.scaleY, _T("scale.y"), MFC_PROPERTY_BASE_SCALE_Y));
	pProt->AddSubItem(new CMFCPropertyGridProperty(_T("scaleZ"), (float)m_basePropertInfo.scaleZ, _T("scale.z"), MFC_PROPERTY_BASE_SCALE_Z));
	pBase->AddSubItem(pProt);
	m_wndPropList.AddProperty(pBase);

	//动作
	CMFCPropertyGridProperty* pModelAnimate = new CMFCPropertyGridProperty(_T("动作"));
	static const TCHAR szFilter[] = _T("动作文件(*.c3b;*.c3t)|*.c3b|*.c3t|所有文件(*.*)|*.*||");
	pModelAnimate->AddSubItem(new CMFCPropertyGridFileProperty(_T("动作文件"), TRUE, resourcePathW.c_str(), _T("c3b"), 0, szFilter, _T("指定模型动作"),MFC_PROPERTY_MODEL_ANIMATE_PATH));
	pModelAnimate->AddSubItem(new CMFCPropertyGridProperty(_T("rate"), (float)m_modelAnimateInfo.rate, _T("rate"), MFC_PROPERTY_MODEL_ANIMATE_RATE));
	pModelAnimate->AddSubItem(new CMFCPropertyGridProperty(_T("startFrame"), (_variant_t)(int)m_modelAnimateInfo.startframe, _T("开始帧"), MFC_PROPERTY_MODEL_ANIMATE_START_FRAME));
	pModelAnimate->AddSubItem(new CMFCPropertyGridProperty(_T("endFrame"), (_variant_t)(int)m_modelAnimateInfo.endframe, _T("结束帧"), MFC_PROPERTY_MODEL_ANIMATE_END_FRAME));
	m_wndPropList.AddProperty(pModelAnimate);

	//MATERIAL
	CMFCPropertyGridProperty* pMaterial = new CMFCPropertyGridProperty(_T("材质"));
	static const TCHAR szFilter2[] = _T("动作文件(*.material)|*.material|所有文件(*.*)|*.*||");
	pMaterial->AddSubItem(new CMFCPropertyGridFileProperty(_T("材质文件"), TRUE, resourcePathW.c_str(), _T("material"), 0, szFilter2, _T("指定模型材质"), MFC_PROPERTY_MODEL_MATERIAL_PATH));
	pMaterial->AddSubItem(new CMFCPropertyGridProperty(_T("technique"), (_variant_t)(m_modelMaterialInfo.technique.c_str()), _T("technique"), MFC_PROPERTY_MODEL_MATERIAL_TECHNIQUE));
	m_wndPropList.AddProperty(pMaterial);
}

void CPropertiesWnd::OnSetFocus(CWnd* pOldWnd)
{
	CDockablePane::OnSetFocus(pOldWnd);
	m_wndPropList.SetFocus();
}

void CPropertiesWnd::OnSettingChange(UINT uFlags, LPCTSTR lpszSection)
{
	CDockablePane::OnSettingChange(uFlags, lpszSection);
	SetPropListFont();
}

LRESULT CPropertiesWnd::OnPropertyChanged(WPARAM wParam, LPARAM lParam)
{
	CMFCPropertyGridProperty* pProp = (CMFCPropertyGridProperty*)lParam;
	int pID = pProp->GetData();

	if (pID >= MFC_PROPERTY_BASE_BEGIN && pID <= MFC_PROPERTY_BASE_END)
	{
		if (pID == MFC_PROPERTY_BASE_POS_X) { m_basePropertInfo.posX = pProp->GetValue().fltVal; }
		else if(pID == MFC_PROPERTY_BASE_POS_Y) { m_basePropertInfo.posY = pProp->GetValue().fltVal; }
		else if (pID == MFC_PROPERTY_BASE_POS_Z) { m_basePropertInfo.posZ = pProp->GetValue().fltVal; }
		else if (pID == MFC_PROPERTY_BASE_ROT_X) { m_basePropertInfo.rotX = pProp->GetValue().fltVal; }
		else if (pID == MFC_PROPERTY_BASE_ROT_Y) { m_basePropertInfo.rotY = pProp->GetValue().fltVal; }
		else if (pID == MFC_PROPERTY_BASE_ROT_Z) { m_basePropertInfo.rotZ = pProp->GetValue().fltVal; }
		else if (pID == MFC_PROPERTY_BASE_SCALE_X) { m_basePropertInfo.scaleX = pProp->GetValue().fltVal; }
		else if (pID == MFC_PROPERTY_BASE_SCALE_Y) { m_basePropertInfo.scaleY = pProp->GetValue().fltVal; }
		else if (pID == MFC_PROPERTY_BASE_SCALE_Z) { m_basePropertInfo.scaleZ = pProp->GetValue().fltVal; }

		MFCHelper::dispatchCocosCustomEvent(EVENT_MFC_PROPERTY_UPDATE_BASE, (void*)&m_basePropertInfo);
	}
	else if (pID >= MFC_PROPERTY_MODEL_ANIMATE_BEGIN && pID <= MFC_PROPERTY_MODEL_ANIMATE_END)
	{
		if (pID == MFC_PROPERTY_MODEL_ANIMATE_PATH)
		{
			std::wstring tmp(pProp->GetValue().bstrVal);
			std::string path = MyUtils::w2s(tmp);
			m_modelAnimateInfo.path = path;
		}
		else if (pID == MFC_PROPERTY_MODEL_ANIMATE_RATE) { m_modelAnimateInfo.rate = pProp->GetValue().fltVal; }
		else if (pID == MFC_PROPERTY_MODEL_ANIMATE_START_FRAME) { m_modelAnimateInfo.startframe = pProp->GetValue().intVal; }
		else if (pID == MFC_PROPERTY_MODEL_ANIMATE_END_FRAME) { m_modelAnimateInfo.endframe = pProp->GetValue().intVal; }

		MFCHelper::dispatchCocosCustomEvent(EVENT_MFC_PROPERTY_UPDATE_MODEL_ANIMATE, (void*)&m_modelAnimateInfo);
	}
	else if (pID >= MFC_PROPERTY_MODEL_MATERIAL_BEGIN && pID <= MFC_PROPERTY_MODEL_MATERIAL_END)
	{
		if (pID == MFC_PROPERTY_MODEL_MATERIAL_PATH)
		{
			std::wstring tmp(pProp->GetValue().bstrVal);
			std::string path = MyUtils::w2s(tmp);
			m_modelMaterialInfo.path = path;
		}
		else if (pID == MFC_PROPERTY_MODEL_MATERIAL_TECHNIQUE)
		{
			std::wstring tmp(pProp->GetValue().bstrVal);
			std::string t = MyUtils::w2s(tmp);
			m_modelMaterialInfo.technique = t;
		}

		MFCHelper::dispatchCocosCustomEvent(EVENT_MFC_PROPERTY_UPDATE_MODLE_MATERIAL, (void*)&m_modelMaterialInfo);
	}

	return 0;
}

void CPropertiesWnd::SetPropListFont()
{
	::DeleteObject(m_fntPropList.Detach());

	LOGFONT lf;
	afxGlobalData.fontRegular.GetLogFont(&lf);

	NONCLIENTMETRICS info;
	info.cbSize = sizeof(info);

	afxGlobalData.GetNonClientMetrics(info);

	lf.lfHeight = info.lfMenuFont.lfHeight;
	lf.lfWeight = info.lfMenuFont.lfWeight;
	lf.lfItalic = info.lfMenuFont.lfItalic;

	m_fntPropList.CreateFontIndirect(&lf);

	m_wndPropList.SetFont(&m_fntPropList);
}
