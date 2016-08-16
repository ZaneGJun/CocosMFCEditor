#ifndef __MFC_GLVIEW_H__
#define __MFC_GLVIEW_H__

#include "base/CCRef.h"
#include "platform/CCCommon.h"
#include "platform/CCGLView.h"
#include "glfw3.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
#ifndef GLFW_EXPOSE_NATIVE_WIN32
#define GLFW_EXPOSE_NATIVE_WIN32
#endif
#ifndef GLFW_EXPOSE_NATIVE_WGL
#define GLFW_EXPOSE_NATIVE_WGL
#endif
#include "glfw3native.h"
#endif /* (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) */
#include "cocos2d.h"

NS_CC_BEGIN

class MFCGLView : public GLView
{
public:
	static MFCGLView* createWithRect(const std::string& viewName, Rect size, HWND  handle, float frameZoomFactor = 1.0f);

	bool initWithRect(const std::string& viewName, Rect rect, HWND  handle, float frameZoomFactor);

	void onGLFWError(int errorID, const char* errorDesc);

	/* override functions */
	virtual bool isOpenGLReady() override;
	virtual void end() override;
	virtual void swapBuffers() override;
	virtual void setIMEKeyboardState(bool bOpen) override;

	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	HWND getWin32Window() { return m_hWnd; }
#endif /* (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) */

protected:

	MFCGLView();
	virtual ~MFCGLView();

	bool initGlew();

	void initNormalOpenGL(Rect rect);
	void initWithOpenGlSmaple(Rect rect, int sample);

	std::string _glfwError;
	float _frameZoomFactor;
	HDC  m_hDC;
	HGLRC m_hRC;
	HWND m_hWnd;

	bool _captured;
};

NS_CC_END   // end of namespace   cocos2d

#endif