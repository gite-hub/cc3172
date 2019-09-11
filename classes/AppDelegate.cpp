#include "AppDelegate.h"
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
#include "../proj.win32/_utf.h"
#endif
#include "../libui/_cc8.h"
#include "../libui/_ccu.h"
#include "../libui/_ui.h"

USING_NS_CC;
AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate()
{
}

void AppDelegate::initGLContextAttrs()
{
	GLContextAttrs glContextAttrs = { 8, 8, 8, 8, 24, 8, 0 };

	GLView::setGLContextAttrs(glContextAttrs);
}

std::string cPath::cDownload = "Download/";
std::string cPath::cLxy = "langxiyou/";
std::string cPath::cI32 = "i32.png";
std::string cPath::cWdf = "wdfs/";
std::string cPath::cMap = "maps/";
std::string cPath::cMusic = "music/";
std::string cPath::cFont = "fonts/";

const std::string& cPath::getRoot()
{
	static std::string root;
	if (root.empty())
	{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include <jni.h>
#include <fstream>
		JNIEnv* env = JniHelper::getEnv();
		jclass envClz = env->FindClass("android/os/Environment");
		jmethodID getExternalStorageDirectory = env->GetStaticMethodID(envClz,
			"getExternalStorageDirectory",
			"()Ljava/io/File;");
		jobject jobject1 = env->CallStaticObjectMethod(envClz, getExternalStorageDirectory);

		jmethodID getAbsolutePath = env->GetMethodID(env->FindClass("java/io/File"),
			"getAbsolutePath",
			"()Ljava/lang/String;");
		jstring jstring1 = (jstring)env->CallObjectMethod(jobject1, getAbsolutePath);
		const char *path_utf = env->GetStringUTFChars(jstring1, NULL);
		root = path_utf;
		//  LOGE("%s", path_utf);
		env->ReleaseStringUTFChars(jstring1, path_utf);

		// "file://" +
		root += "/";
		std::vector<std::string> strs = { cLxy, cDownload + cLxy, cDownload + cLxy + cLxy };
		bool isFound = false;
		for (const auto& s : strs)
		{
			std::ifstream ifile(root + s + cI32, std::ios::binary);
			if (ifile.is_open())
			{
				ifile.close();
				root += s;
				isFound = true;
				break;
			}
		}
		if (!isFound)
		{
			root.clear();
		}
#endif
	}
	return root;
}

bool AppDelegate::applicationDidFinishLaunching()
{
	// Initialize director
	auto director = Director::getInstance();
	Size winSize(960, 540);
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	auto glview = GLViewImpl::createWithRect(cc::gbk2utf("浪西游") + " v20190910", Rect(Vec2::ZERO, winSize));
#else
	auto glview = director->getOpenGLView();
	if (glview == nullptr) {
	    glview = GLViewImpl::create("langxiyou");
		director->setOpenGLView(glview);
	}
#endif
	Size frameSize = glview->getFrameSize();
	if (frameSize.width / frameSize.height < 1.59f)
	{
		// 16:10 以下的一般都是平板, 屏幕够大了
		glview->setDesignResolutionSize(winSize.width, winSize.height, ResolutionPolicy::FIXED_WIDTH);
	}
	else
	{
		glview->setDesignResolutionSize(winSize.height * frameSize.width / frameSize.height, winSize.height, ResolutionPolicy::NO_BORDER);
	}
	director->setOpenGLView(glview);
	// Set window icon with best resolution (windows and linux)
#if (CC_TARGET_PLATFORM == CC_PLATFORM_LINUX)
// assert error when using listFilesRecursively on Windows 10
// refer to: https://github.com/cocos2d/cocos2d-x/issues/18835
// don't use listFiles as workaround (it will return directory itself)
// refer to: https://github.com/cocos2d/cocos2d-x/issues/18834
	std::vector<std::string> icons;
	FileUtils::getInstance()->listFilesRecursively("icons", &icons);
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	// 去掉 Resources/
	std::string icons = FileUtils::getInstance()->getDefaultResourceRootPath();
	do { icons.pop_back(); } while (icons.back() != '/');
	FileUtils::getInstance()->setDefaultResourceRootPath(icons);
	icons = "i32.png";
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	std::string icons = cPath::getRoot();
	if (icons.empty())
	{
		icons = cPath::cDownload + cPath::cLxy + "   is not found";
		ccc_box(icons.c_str());
		return true;
	}
	auto searchs = FileUtils::getInstance()->getSearchPaths();
	searchs.push_back(icons);
    FileUtils::getInstance()->setSearchPaths(searchs);
    icons = "i32.png";
#endif
	glview->setIcon(icons);

	director->setDisplayStats(false);
	director->setAnimationInterval(1.0f / 60);

//	Texture2D::setDefaultAlphaPixelFormat(Texture2D::PixelFormat::RGBA4444);

// 	cSps::getInstance()->load("C:/Users/Deen/Desktop/浪西游资料片/scene.wd/shape.wd1");
// 	cSps::getInstance()->load("C:/Users/Deen/Desktop/浪西游资料片/scene.wd/shape.wdf");
// 	cSps::getInstance()->load("C:/Users/Deen/Desktop/浪西游资料片/scene.wd/shape.wd2");
// 	cSps::getInstance()->load("C:/Users/Deen/Desktop/浪西游资料片/scene.wd/baby.wdf");
// 	cSps::getInstance()->load("C:/Users/Deen/Desktop/浪西游资料片/scene.wd/uijd.wdf");
// 	cSps::getInstance()->load("C:/Users/Deen/Desktop/i56.wdf");

	std::string pathWdf = cPath::getRoot() + cPath::cWdf;
	cSps::getInstance()->load(pathWdf + "shape.wdf");
	cSps::getInstance()->load(pathWdf + "baby.wdf");
	cSps::getInstance()->load(pathWdf + "icons.wdf");
	cSps::getInstance()->load(pathWdf + "ui.wdf");
	cWdf::getColor()->load(pathWdf + "dyes.wdf");

//	cWdf::getColor()->load("C:/Users/Deen/Desktop/浪西游资料片/scene.wd/color.wdf");
//	cWdf::getWav()->load("C:/Users/Deen/Desktop/浪西游资料片/scene.wd/sound.wdf");
	// Create a scene. it's an autorelease object


	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("1.plist", "1.png");

	auto scene = Scene::create();
	initScene(scene);

	director->runWithScene(scene);
	return true;
}

// This function will be called when the app is inactive. Note, when receiving a phone call it is invoked.
void AppDelegate::applicationDidEnterBackground()
{
	Director::getInstance()->stopAnimation();

	// If you use SimpleAudioEngine, it must be paused
	// SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
}

// This function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground()
{
	Director::getInstance()->startAnimation();

	// If you use SimpleAudioEngine, it must resume here
	// SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}



void AppDelegate::initScene(Scene* scene)
{
	uiMap* uimap = uiMap::create();
	ccu::setMap(uimap);
	scene->addChild(uimap);

	uiManager* ui = uiManager::create();
	scene->addChild(ui, 1);
	ccu::setManager(ui);
#if 1
	float h = 0;
	ui::ScrollView* scrollView = ui::ScrollView::create();
	scene->addChild(scrollView);
	scrollView->setContentSize(cc::vsSize());
 	const auto& skis = txtIcon::getIcons().at(eIcon::ski);
	scrollView->setVisible(false);

	if (0)
	{
		for (const auto& it : skis)
		{
			const auto& ski = it.second;
			cSprite* sprite = cSprite::create(ski.uid);
			sprite->play();
			sprite->setPosition(120, h);
			scrollView->addChild(sprite);
			sprite->addChild(cLabel::create(ski.name, eFont::normal));

			h += sprite->getContentSize().height + 15;
		}
		scrollView->setInnerContainerSize(Size(cc::vsSize().width, h));
		return;
	}
	if (0)
	{
		h += 480;
		for (const auto& it : txtSki::getSkis())
		{
			const auto& ski = it.second;
			cSprite* sprite = cSprite::create(ski.act);
			sprite->play();
			sprite->setPosition(480, h);
			scrollView->addChild(sprite);

			const auto& it2 = skis.find((int)it.first);
			if (it2 != skis.end())
			{
				sprite->addChild(cLabel::create(it2->second.name, eFont::normal));
			}

			cSprite* sprite2 = cSprite::create(ski.state);
			sprite2->play();
			sprite2->setPosition(sprite->getPositionX() + sprite->getContentSize().width, h);
			scrollView->addChild(sprite2);

			h += std::max(sprite->getContentSize().height, sprite2->getContentSize().height);
		}
		scrollView->setInnerContainerSize(Size(cc::vsSize().width, h));
		return;
	}
	if (0)
	{
		for (int e = (int)eIcon::e0; e <= (int)eIcon::stone; ++e)
		{
			if (e == (int)eIcon::shoujue)
			{
				continue;
			}
			const auto& icons = txtIcon::getIcons().at((eIcon)e);
			forv(icons, k)
			{
				cSprite1* sprite = cSprite1::create(icons.at(k).uid);
				scrollView->addChild(sprite);
				sprite->setPosition(120, h);
				h += sprite->getContentSize().height;
				sprite->addChild(cLabel::create(toString("%d.%s", k, icons.at(k).name.c_str()), eFont::normal));
			}
		}
		scrollView->setInnerContainerSize(Size(cc::vsSize().width, h));
		return;
	}

	sRole* role = cRole::getInstance()->getHero();
	role->mod.setMod((eMod)cc::random((int)eMod::e0, (int)eMod::e0end));
	role->name = txtMod::getMods().at(role->mod.e).name;
	role->menpai = eMenpai::assist;
	role->lvupEasy(59);
// 	role->lv += 800;
// 	role->point.lvup(800);
	role->exp.add(0xFFFFFF);
	role->money.add(0xFFFFFF);
	for (int k = 0; k < cEquip::c4; ++k)
	{
		sItem* it = new sItem();
		it->setData(cEquip::getType(k), 6);
		role->equips.at(k) = it;
	}
	for (int k = 0; k < ccp::main7; ++k)
	{
		role->skilvs.at(k) = role->lv + cSki::cGap;
	}

	if (0)
	{
		std::vector<eMod> mods = { eMod::paopao, eMod::baize, eMod::xiaoxiang, eMod::liuermihou };
		forv(mods, k)
		{
			auto pet = cPet::getInstance()->getPet(mods.at(k));
			pet->lvupEasy(role->lv + ccp::lvGap);
			role->addPet(pet);
		}
	}
	ui->load(role);

	cObject* viewer = cObject::create(role->mod);
	viewer->setName(role->name);
	uimap->setViewer(viewer);

	uimap->load(eMap::haiwan);
	uimap->load(30, 110);

	auto func = [viewer]()
	{
		viewer->say(cc8::cWelcome, true);
	};
	scene->runAction(Sequence::create(DelayTime::create(8), CallFunc::create(func), nullptr));

	if (0)
	{
		for (int e = (int)eMod::e0; e <= (int)eMod::eEnd; ++e)
		{
			sMod m;
			m.setMod((eMod)e, 1);
			float h2 = 0;
			float h3 = 3;
			for (int a = (int)eAct::stand, w = 0, w2 = 0; a <= (int)eAct::back; ++a)
			{
				cDyeRender::apply(m.e, 1, m.dyes);
				m.apply();
				cSprite* sprite = cSprite::create(m.get((eAct)a, false));
				sprite->setShadow(true);
				sprite->play();
				scrollView->addChild(sprite);
				if (a <= (int)eAct::atk2)
				{
					sprite->setPosition(w + 120, h);
					w += sprite->getContentSize().width;
					h2 = std::max(h2, sprite->getContentSize().height);
				}
				else
				{
					sprite->setPosition(w2 + 120, h + h2);
					w2 += sprite->getContentSize().width;
					h3 = std::max(h3, sprite->getContentSize().height);
				}
			}
			h += h2 + h3;
		}
		scrollView->setInnerContainerSize(Size(cc::vsSize().width, h));
//		return;
	}
#endif

#if 0
	cWdf* wdf = new cWdf();
	wdf->load("shape.wdf");
	auto writeWas = [wdf](ulong uid, const std::string& path)
	{
		if (uid == cSp::c0)
		{
			return;
		}
		int size = 0;
		auto ptr = wdf->getData(uid, size);
		if (ptr == nullptr)
		{
			return;
		}
		std::ofstream ofile("D:/Users/mac-wolf/cc3172/_output_Debug/" + path + toString("%08X.was", uid), std::ios::binary);
		ofile.write(ptr, size);
	};

	for (int e = (int)eMod::paopao; e <= (int)eMod::xiaoxiang; ++e)
	{
		const auto& m = txtMod::getMods().at((eMod)e);
		forv(m.parts, k)
		{
			const auto& p = m.parts.at(k);
			writeWas(p.maps.at(eAct::stand), "shape.wd2.unpack/");
			writeWas(p.maps.at(eAct::walk), "shape.wd2.unpack/");
			for (const auto& a : p.acts)
			{
				writeWas(a.second, "shape.wd2.unpack/");
			}
		}
	}
#endif

#if 0
	std::vector<cWdf*> wdfs;
	if(1)
	{
		std::vector<std::string> wdfNames = { "shape.wd1", "shape.wdf", "shape.wd2", "baby.wdf", "uijd.wdf" };
		for (auto& name : wdfNames)
		{
			name = "浪西游资料片/scene.wd/" + name;
		}
		wdfNames.push_back("i56.wdf");
		for (auto& name : wdfNames)
		{
			name = "C:/Users/Deen/Desktop/" + name;
		}
		forv(wdfNames, k)
		{
			cWdf* wdf = new cWdf();
			wdf->load(wdfNames.at(k));
			wdfs.push_back(wdf);
		}
	}


	auto writeWas = [wdfs](ulong uid, const std::string& path)
	{
		return;
		if (uid == cSp::c0)
		{
			return;
		}
		int size = 0;
		forv(wdfs, k)
		{
			auto ptr = wdfs.at(k)->getData(uid, size);
			if (ptr == nullptr)
			{
				continue;
			}
			std::ofstream ofile("D:/Users/mac-wolf/cc3172/_output_Debug/" + path + toString("%08X.was", uid), std::ios::binary);
			ofile.write(ptr, size);
		}
	};
	auto writeSound = [](ulong uid)
	{
		int size = 0;
		auto ptr = cWdf::getWav()->getData(uid, size);
		if (ptr == nullptr)
		{
			return;
		}
		std::ofstream ofile("D:/Users/mac-wolf/cc3172/_output_Debug/sounds/" + toString("%08X.was", uid), std::ios::binary);
		ofile.write(ptr, size);
	};
	auto writeDye = [](ulong uid)
	{
		int size = 0;
		auto ptr = cWdf::getColor()->getData(uid, size);
		if (ptr == nullptr)
		{
			return;
		}
		std::ofstream ofile("D:/Users/mac-wolf/cc3172/_output_Debug/dyes.wdf/" + toString("%08X.was", uid), std::ios::binary);
		ofile.write(ptr, size);
	};
	if(1)
	{
		for (int e = (int)eIcon::e0; e <= (int)eIcon::eEnd; ++e)
		{
			if (e == (int)eIcon::shoujue)
			{
				continue;
			}
			const auto& icons = txtIcon::getIcons().at((eIcon)e);
			for (const auto& icon : icons)
			{
				writeWas(icon.second.uid, "icons.wdf/");
			}
		}
		for (int e = (int)eMod::e0; e <= (int)eMod::eEnd; ++e)
		{
			const auto& m = txtMod::getMods().at((eMod)e);
			writeWas(m.head.at(eAct::head), "heads.wdf/");
			writeWas(m.head.at(eAct::dialog), "heads.wdf/");

			for (const auto& sound : m.sound)
			{
				writeSound(sound.second);
			}

			forv (m.parts, k)
			{
				const auto& p = m.parts.at(k);
				writeDye(p.color);
				writeWas(p.maps.at(eAct::stand), "shape.wdf/");
				writeWas(p.maps.at(eAct::walk), "shape.wdf/");
				for (const auto& a : p.acts)
				{
					writeWas(a.second, "shape.wdf/");
				}
			}
		}

		for (const auto& ski : txtSki::getSkis())
		{
			writeWas(ski.second.act, "magic.wdf/");
			writeWas(ski.second.state, "magic.wdf/");
			writeSound(ski.second.sound);
		}
	}

	std::vector<ulong>  uids = {
	0x220AEF93, 0x2FE08CEB, 0x72E1B8C7, 0x7C83B9D4, 0x935672A0, 0x00000000, 0x704B48CC, 0x6E57F609, 0x0581A7A6, 0x67C54CFB, 0x1A618AAD,
	0x574D7DF4, 0x578771AB, 0xFDB3FA02, 0xDDE71F8A, 0xB92A33F2, 0x00000000, 0x3FF7420A, 0x307D1D47, 0x5B58D8FC, 0x1DDBB1C6, 0x5A5A13FD
	};
	int size = 0;
	cWdf wdf;
	wdf.load("C:/Users/Deen/Desktop/浪西游资料片/scene.wd/shape.wd1");
	forv(uids, k)
	{
		auto ptr = wdf.getData(uids.at(k), size);
		if (ptr == nullptr)
		{
			continue;
		}
		std::ofstream ofile("D:/Users/mac-wolf/cc3172/_output_Debug/虎子/" + toString("%08X.was", uids.at(k)), std::ios::binary);
		ofile.write(ptr, size);
	}
#endif

	if (0)
	{
		sItem it;
		it.setData(eIcon::clothes, 6);
		cEquip::setStone(&it, eStone::guangmang);
		it.save(false);
		cSave::getSave()->save(cPath::getRoot() + "item.txt", false);
		cSave::getLoad()->load(cPath::getRoot() + "item.txt", false);
		sItem it2;
		it2.load(false);

		sDescs descs;
		it2.toDesc(descs);

		//	icons.clear();
		std::string icons = descs.name;
		for (const auto& d : descs.descs)
		{
			icons += s_enter + d.text;
		}
		ccc_box(icons);
	}
}
