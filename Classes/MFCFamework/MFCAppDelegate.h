#ifndef __MFC_APP_DELEGATE_H__
#define __MFC_APP_DELEGATE_H__

#include "cocos2d.h"

class MFCAppDelegate : public cocos2d::Application
{
public:
	MFCAppDelegate();
	virtual ~MFCAppDelegate();

	virtual void initGLContextAttrs();

	/**
	@brief    Implement Director and Scene init code here.
	@return true    Initialize success, app continue.
	@return false   Initialize failed, app terminate.
	*/
	virtual bool applicationDidFinishLaunching();

	/**
	@brief  The function be called when the application enter background
	@param  the pointer of the application
	*/
	virtual void applicationDidEnterBackground();

	/**
	@brief  The function be called when the application enter foreground
	@param  the pointer of the application
	*/
	virtual void applicationWillEnterForeground();

	//create view by MFC HWND
	virtual void CreateWnd(HWND hwnd);
	// run by MFC¡¡time
	virtual void Run2();

	void Resize(int width, int height);

	LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
public:
	HWND m_hwnd;
};

#endif