#ifndef __MFC_HELPER_H__
#define __MFC_HELPER_H__

#include <string>

class MFCHelper
{
public:
	/** ·¢ËÍÏûÏ¢ 
	 */
	static void dispatchCocosCustomEvent(const std::string& event, void* userdata = nullptr);
};

#endif