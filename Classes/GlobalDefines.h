#ifndef __GLOBAL_DEFINES_H__
#define __GLOBAL_DEFINES_H__

#include <string>

#define EVENT_MFC_FILE_TREEVIEW_DOUBLE_CLICK_ITEM "EVENT_MFC_FILE_TREEVIEW_DOUBLE_CLICK_ITEM"				//MFC文件树视图双击某一项
#define EVENT_MFC_PROPERTY_UPDATE_BASE "EVENT_MFC_PROPERTY_UPDATE_BASE"					//基础属性修改
#define EVENT_MFC_PROPERTY_UPDATE_MODEL_ANIMATE "EVENT_MFC_PROPERTY_UPDATE_MODEL_ANIMATE"					//动作属性修改
#define EVENT_MFC_PROPERTY_UPDATE_MODLE_MATERIAL "EVENT_MFC_PROPERTY_UPDATE_MODLE_MATERIAL"					//material属性修改


#define MFC_PROPERTY_BASE_BEGIN 0
#define MFC_PROPERTY_BASE_POS_X 1
#define MFC_PROPERTY_BASE_POS_Y 2
#define MFC_PROPERTY_BASE_POS_Z 3
#define MFC_PROPERTY_BASE_ROT_X 4
#define MFC_PROPERTY_BASE_ROT_Y 5
#define MFC_PROPERTY_BASE_ROT_Z 6
#define MFC_PROPERTY_BASE_SCALE_X 7
#define MFC_PROPERTY_BASE_SCALE_Y 8
#define MFC_PROPERTY_BASE_SCALE_Z 9
#define MFC_PROPERTY_BASE_END  99

#define MFC_PROPERTY_MODEL_ANIMATE_BEGIN 100
#define MFC_PROPERTY_MODEL_ANIMATE_PATH 101
#define MFC_PROPERTY_MODEL_ANIMATE_RATE 102
#define MFC_PROPERTY_MODEL_ANIMATE_START_FRAME 103
#define MFC_PROPERTY_MODEL_ANIMATE_END_FRAME 104
#define MFC_PROPERTY_MODEL_ANIMATE_END 199

#define MFC_PROPERTY_MODEL_MATERIAL_BEGIN 200
#define MFC_PROPERTY_MODEL_MATERIAL_PATH 201
#define MFC_PROPERTY_MODEL_MATERIAL_TECHNIQUE 202
#define MFC_PROPERTY_MODEL_MATERIAL_END 299

struct BasePropert
{
	float posX;
	float posY;
	float posZ;
	float rotX;
	float rotY;
	float rotZ;
	float scaleX;
	float scaleY;
	float scaleZ;

	BasePropert(float px = 0.0f, float py = 0.0f, float pz = 0.0f, float rx = 0.0f, float ry = 0.0f, float rz = 0.0f, float sx = 1.0f, float sy = 1.0f, float sz = 1.0f)
		:posX(px), posY(py), posZ(pz), rotX(rx), rotY(ry), rotZ(rz), scaleX(sx), scaleY(sy), scaleZ(sz)
	{

	}
};

struct ModelAnimate
{
	std::string path;
	float rate;
	int startframe;
	int endframe;

	ModelAnimate(std::string p = "", float r = 24, int s = 0, int e = 1)
		:path(p), rate(r), startframe(s), endframe(e)
	{

	}
};

struct ModelMaterial
{
	std::string path;
	std::string technique;
};

#endif