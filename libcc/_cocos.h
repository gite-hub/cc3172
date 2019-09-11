#pragma once

#if true || (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include "cocos2d.h"
#else
// #include "base/ccConfig.h"

// base
// #include "base/CCAsyncTaskPool.h"
// #include "base/CCAutoreleasePool.h"
// #include "base/CCConfiguration.h"
// #include "base/CCConsole.h"
// #include "base/CCData.h"
#include "base/CCDirector.h"
#include "base/CCIMEDelegate.h"
#include "base/CCIMEDispatcher.h"
// #include "base/CCMap.h"
// #include "base/CCNS.h"
// #include "base/CCProfiling.h"
// #include "base/CCProperties.h"
// #include "base/CCRef.h"
// #include "base/CCRefPtr.h"
#include "base/CCScheduler.h"
// #include "base/CCUserDefault.h"
// #include "base/CCValue.h"
// #include "base/CCVector.h"
// #include "base/ZipUtils.h"
// #include "base/base64.h"
// #include "base/ccConfig.h"
// #include "base/ccMacros.h"
// #include "base/ccTypes.h"
// #include "base/ccUTF8.h"
// #include "base/ccUtils.h"

// EventDispatcher
// #include "base/CCEventAcceleration.h"
#include "base/CCEventCustom.h"
#include "base/CCEventDispatcher.h"
#include "base/CCEventFocus.h"
// #include "base/CCEventKeyboard.h"
// #include "base/CCEventListenerAcceleration.h"
#include "base/CCEventListenerCustom.h"
// #include "base/CCEventListenerFocus.h"
// #include "base/CCEventListenerKeyboard.h"
// #include "base/CCEventListenerMouse.h"
#include "base/CCEventListenerTouch.h"
// #include "base/CCEventMouse.h"
#include "base/CCEventTouch.h"
#include "base/CCEventType.h"

// math
// #include "math/CCAffineTransform.h"
// #include "math/CCGeometry.h"
// #include "math/CCVertex.h"
// #include "math/Mat4.h"
// #include "math/MathUtil.h"
// #include "math/Quaternion.h"
#include "math/Vec2.h"
// #include "math/Vec3.h"
// #include "math/Vec4.h"

// actions
#include "2d/CCAction.h"
// #include "2d/CCActionCamera.h"
// #include "2d/CCActionCatmullRom.h"
// #include "2d/CCActionEase.h"

#include "2d/CCActionInstant.h"
#include "2d/CCActionInterval.h"
#include "2d/CCActionManager.h"

// #include "2d/CCActionProgressTimer.h"

#include "2d/CCActionTween.h"
#include "2d/CCTweenFunction.h"

// 2d nodes
// #include "2d/CCAtlasNode.h"
// #include "2d/CCClippingNode.h"

#include "2d/CCDrawNode.h"
#include "2d/CCDrawingPrimitives.h"
#include "2d/CCFontFNT.h"
#include "2d/CCLabel.h"
#include "2d/CCLabelAtlas.h"
#include "2d/CCLabelBMFont.h"
#include "2d/CCLabelTTF.h"
#include "2d/CCLayer.h"
#include "2d/CCMenu.h"
#include "2d/CCMenuItem.h"
// #include "2d/CCMotionStreak.h"
#include "2d/CCNode.h"

// #include "2d/CCParticleBatchNode.h"
// #include "2d/CCParticleExamples.h"
// #include "2d/CCParticleSystem.h"
// #include "2d/CCParticleSystemQuad.h"
// #include "2d/CCProgressTimer.h"
// #include "2d/CCProtectedNode.h"
// #include "2d/CCRenderTexture.h"
#include "2d/CCScene.h"
// #include "2d/CCTransition.h"


// 2d utils
// #include "2d/CCCamera.h"
// #include "2d/CCCameraBackgroundBrush.h"
// #include "2d/CCGrabber.h"
// #include "2d/CCGrid.h"
// #include "2d/CCLight.h"

// include
// #include "base/CCProtocols.h"

// renderer
// #include "renderer/CCCustomCommand.h"
// #include "renderer/CCGLProgram.h"
// #include "renderer/CCGLProgramCache.h"
// #include "renderer/CCGLProgramState.h"
// #include "renderer/CCGroupCommand.h"
// #include "renderer/CCMaterial.h"
// #include "renderer/CCPass.h"
// #include "renderer/CCPrimitive.h"
// #include "renderer/CCPrimitiveCommand.h"
// #include "renderer/CCQuadCommand.h"
// #include "renderer/CCRenderCommand.h"
// #include "renderer/CCRenderCommandPool.h"
// #include "renderer/CCRenderState.h"
#include "renderer/CCRenderer.h"
// #include "renderer/CCTechnique.h"
// #include "renderer/CCTexture2D.h"
// #include "renderer/CCTextureCube.h"
#include "renderer/CCTextureCache.h"
// #include "renderer/CCTrianglesCommand.h"
// 
// #include "renderer/CCVertexIndexBuffer.h"
// #include "renderer/CCVertexIndexData.h"
// #include "renderer/CCFrameBuffer.h"
// #include "renderer/ccGLStateCache.h"
// #include "renderer/ccShaders.h"

// physics

// platform
// #include "platform/CCCommon.h"
// #include "platform/CCDevice.h"
#include "platform/CCFileUtils.h"
#include "platform/CCImage.h"
// #include "platform/CCPlatformConfig.h"
// #include "platform/CCPlatformMacros.h"
// #include "platform/CCSAXParser.h"
// #include "platform/CCThread.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#include "platform/ios/CCApplication-ios.h"
#include "platform/ios/CCGLViewImpl-ios.h"
#include "platform/ios/CCGL-ios.h"
#include "platform/ios/CCStdC-ios.h"
#endif // CC_TARGET_PLATFORM == CC_PLATFORM_IOS

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include "platform/android/CCApplication-android.h"
#include "platform/android/CCGLViewImpl-android.h"
#include "platform/android/CCGL-android.h"
#include "platform/android/CCStdC-android.h"
//Enhance modification begin
#include "platform/android/CCEnhanceAPI-android.h"
//Enhance modification end
#endif // CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID

#if (CC_TARGET_PLATFORM == CC_PLATFORM_BLACKBERRY)
#include "platform/blackberry/CCApplication.h"
#include "platform/blackberry/CCGLViewImpl.h"
#include "platform/blackberry/CCGL.h"
#include "platform/blackberry/CCStdC.h"
#endif // CC_TARGET_PLATFORM == CC_PLATFORM_BLACKBERRY

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
#include "platform/win32/CCApplication-win32.h"
#include "platform/desktop/CCGLViewImpl-desktop.h"
#include "platform/win32/CCGL-win32.h"
#include "platform/win32/CCStdC-win32.h"
#endif // CC_TARGET_PLATFORM == CC_PLATFORM_WIN32

#if (CC_TARGET_PLATFORM == CC_PLATFORM_MAC)
#include "platform/desktop/CCGLViewImpl-desktop.h"
#include "platform/mac/CCApplication-mac.h"
#include "platform/mac/CCGL-mac.h"
#include "platform/mac/CCStdC-mac.h"
#endif // CC_TARGET_PLATFORM == CC_PLATFORM_MAC

#if (CC_TARGET_PLATFORM == CC_PLATFORM_LINUX)
#include "platform/linux/CCApplication-linux.h"
#include "platform/desktop/CCGLViewImpl-desktop.h"
#include "platform/linux/CCGL-linux.h"
#include "platform/linux/CCStdC-linux.h"
#endif // CC_TARGET_PLATFORM == CC_PLATFORM_LINUX

// script_support
// #include "base/CCScriptSupport.h"

// sprite_nodes
#include "2d/CCSprite.h"
// #include "2d/CCAutoPolygon.h"
// #include "2d/CCSpriteBatchNode.h"
// #include "2d/CCSpriteFrame.h"
// #include "2d/CCSpriteFrameCache.h"

// text_input_node
// #include "2d/CCTextFieldTTF.h"

// textures
// #include "renderer/CCTextureAtlas.h"

// tilemap_parallax_nodes
// #include "2d/CCParallaxNode.h"
// #include "2d/CCTMXLayer.h"
// #include "2d/CCTMXObjectGroup.h"
// #include "2d/CCTMXTiledMap.h"
// #include "2d/CCTMXXMLParser.h"
// #include "2d/CCTileMapAtlas.h"
// #include "2d/CCFastTMXLayer.h"
// #include "2d/CCFastTMXTiledMap.h"

// component
#include "2d/CCComponent.h"
#include "2d/CCComponentContainer.h"

//3d

// vr


// Deprecated
// All deprecated features are include inside deprecated/CCDeprecated.h.
// It is recommended that you just include what is needed.
// eg. #include "deprecated/CCString.h" if you only need cocos2d::__String.
#include "deprecated/CCDeprecated.h"


// NS_CC_BEGIN
// CC_DLL inline const char* cocos2dVersion(){ return "cocos2dx-3.15.1"; }
// NS_CC_END
#endif

#define CREATE_INIT(_T_, _I_, ...)\
_T_ *pRet = new (std::nothrow)_T_();\
if (pRet && pRet->_I_(__VA_ARGS__))\
{\
	pRet->autorelease();\
	return pRet;\
}\
else\
{\
	delete pRet;\
	return nullptr;\
}
#define CREATE(_TYPE_, ...) CREATE_INIT(_TYPE_, init, __VA_ARGS__)
// #define CREATE_FUNC(__TYPE__) static __TYPE__* create(){ CREATE(__TYPE__) }




////////////////////////////////////////////////////////////////////////// 弹框
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
#define ccc_msgbox(...) MessageBoxA(nullptr, toString(__VA_ARGS__).c_str(), __FUNCTION__, MB_OK)
#define ccc_box(_one_) MessageBoxA(nullptr, cc::toString(_one_).c_str(), __FUNCTION__, MB_OK)
#else
#define ccc_msgbox(...) cocos2d::MessageBox(toString(__VA_ARGS__).c_str(),  __FUNCTION__)
#define ccc_box(_one_) cocos2d::MessageBox(cc::toString(_one_).c_str(),  __FUNCTION__)
#endif
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) && defined(_DEBUG)
////////////////////////////////////////////////////////////////////////// CRTDBG
#include <crtdbg.h>
inline void ccc_crtdbg(const char *file, int line)
{
	_CrtDbgReport(_CRT_WARN, file, line, nullptr, "");
}
////////////////////////////////////////////////////////////////////////// 定位输出 英文
#define ccc_log(...)\
do{\
ccc_crtdbg(__FILE__, __LINE__);\
std::string _str_ =  "★★点击定位★★    ";\
_str_ += StringUtils::format(__VA_ARGS__) + "\n";\
OutputDebugStringA(_str_.c_str());\
}while(0)
////////////////////////////////////////////////////////////////////////// asert
#define asert(_cond_, ...)\
if(!(_cond_))\
{\
	ccc_msgbox(__VA_ARGS__);\
	DebugBreak();\
}
#else
#define ccc_log cocos2d::log
#define asert(_cond_, ...)\
if(!(_cond_))\
{\
	ccc_msgbox(__VA_ARGS__);\
}
#endif

USING_NS_CC;
namespace cc
{
	inline Vec2 vsOrigin(){ return Director::getInstance()->getVisibleOrigin(); }
	inline Size vsSize() { return Director::getInstance()->getVisibleSize(); }
	inline Size vsSize(float x_0_1, float y_0_1)
	{
		Size size = Director::getInstance()->getVisibleSize();
		size.width *= x_0_1;
		size.height *= y_0_1;
		return size;
	}
	inline Vec2 vsAt(float x_0_1, float y_0_1){ return vsOrigin() + vsSize(x_0_1, y_0_1); }
	inline Vec2 vsCenter(){ return vsOrigin() + vsSize() / 2; }
	inline Vec2 vsRand(){ return vsAt(cocos2d::random(0.0f, 1.0f), cocos2d::random(0.0f, 1.0f)); }
	inline float vsX(float x_0_1){ return vsOrigin().x + vsSize().width * x_0_1; }
	inline float vsY(float y_0_1){ return vsOrigin().y + vsSize().height * y_0_1; }

	inline Vec2 getLB(const Node* node) { return node->getBoundingBox().origin; }
	inline Vec2 getLM(const Node* node) { Rect r = node->getBoundingBox(); return r.origin + Size(0, r.size.height / 2); }
	inline Vec2 getLT(const Node* node) { Rect r = node->getBoundingBox(); return r.origin + Size(0, r.size.height); }
	inline Vec2 getRB(const Node* node) { Rect r = node->getBoundingBox(); return r.origin + Size(r.size.width, 0); }
	inline Vec2 getRM(const Node* node) { Rect r = node->getBoundingBox(); return r.origin + Size(r.size.width, r.size.height / 2); }
	inline Vec2 getRT(const Node* node) { Rect r = node->getBoundingBox(); return r.origin + r.size; }
	inline Vec2 getBM(const Node* node) { Rect r = node->getBoundingBox(); return r.origin + Size(r.size.width / 2, 0); }
	inline Vec2 getTM(const Node* node) { Rect r = node->getBoundingBox(); return r.origin + Size(r.size.width / 2, r.size.height); }
	inline Vec2 getMM(const Node* node) { Rect r = node->getBoundingBox(); return r.origin + r.size / 2; }
	inline float getLeft(const Node* node) { return node->getBoundingBox().origin.x; }
	inline float getRight(const Node* node) { return node->getBoundingBox().getMaxX() ; }
	inline float getBottom(const Node* node) { return node->getBoundingBox().origin.y; }
	inline float getTop(const Node* node) { return node->getBoundingBox().getMaxY(); }

	inline bool isVisible(Node* node)
	{
		do
		{
			if (node == nullptr || !node->isVisible())
			{
				return false;
			}
			node = node->getParent();
		} while (true);
		return true;
	}
}