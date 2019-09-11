#pragma once
#include "_inc.h"

class cMenu : public Menu
{
public:
	/**
	 *@brief Creates an empty Menu.
	 */
	static cMenu* create();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	// VS2013 does not support nullptr in variable args lists and variadic templates are also not supported.
	typedef MenuItem* M;
	static cMenu* create(M m1, std::nullptr_t listEnd) { return variadicCreate(m1, NULL); }
	static cMenu* create(M m1, M m2, std::nullptr_t listEnd) { return variadicCreate(m1, m2, NULL); }
	static cMenu* create(M m1, M m2, M m3, std::nullptr_t listEnd) { return variadicCreate(m1, m2, m3, NULL); }
	static cMenu* create(M m1, M m2, M m3, M m4, std::nullptr_t listEnd) { return variadicCreate(m1, m2, m3, m4, NULL); }
	static cMenu* create(M m1, M m2, M m3, M m4, M m5, std::nullptr_t listEnd) { return variadicCreate(m1, m2, m3, m4, m5, NULL); }
	static cMenu* create(M m1, M m2, M m3, M m4, M m5, M m6, std::nullptr_t listEnd) { return variadicCreate(m1, m2, m3, m4, m5, m6, NULL); }
	static cMenu* create(M m1, M m2, M m3, M m4, M m5, M m6, M m7, std::nullptr_t listEnd) { return variadicCreate(m1, m2, m3, m4, m5, m6, m7, NULL); }
	static cMenu* create(M m1, M m2, M m3, M m4, M m5, M m6, M m7, M m8, std::nullptr_t listEnd) { return variadicCreate(m1, m2, m3, m4, m5, m6, m7, m8, NULL); }
	static cMenu* create(M m1, M m2, M m3, M m4, M m5, M m6, M m7, M m8, M m9, std::nullptr_t listEnd) { return variadicCreate(m1, m2, m3, m4, m5, m6, m7, m8, m9, NULL); }
	static cMenu* create(M m1, M m2, M m3, M m4, M m5, M m6, M m7, M m8, M m9, M m10, std::nullptr_t listEnd) { return variadicCreate(m1, m2, m3, m4, m5, m6, m7, m8, m9, m10, NULL); }

	// On WP8 for lists longer than 10 items, use createWithArray or variadicCreate with NULL as the last argument.
	static cMenu* variadicCreate(MenuItem* item, ...);
#else
	/** Creates a Menu with MenuItem objects. */
	static cMenu* create(MenuItem* item, ...) CC_REQUIRES_NULL_TERMINATION;
#endif

	/**
	 * Creates a Menu with a Array of MenuItem objects.
	 * @js NA
	 */
	static cMenu* createWithArray(const Vector<MenuItem*>& arrayOfItems);

	/**
	 * Creates a Menu with it's item, then use addChild() to add
	 * other items. It is used for script, it can't be initialized with undetermined
	 * number of variables.
	 * @js NA
	 */
	static cMenu* createWithItem(MenuItem* item);

	/** Creates a Menu with MenuItem objects.
	 * @js NA
	 */
	static cMenu* createWithItems(MenuItem *firstItem, va_list args);


	void setSwallowsTouch(bool swallowTouches);

protected:
	bool init() override;

	/** initializes a Menu with a NSArray of MenuItem objects */
	bool initWithArray(const Vector<MenuItem*>& arrayOfItems);

	bool onTouchBegan(Touch* touch, Event* event);
	void onTouchEnded(Touch* touch, Event* event);
	void onTouchCancelled(Touch* touch, Event* event);
	void onTouchMoved(Touch* touch, Event* event);

	void update(float delta);

	EventListenerTouchOneByOne* _touchListener;
	Touch* _touch;
	int _keepTimes;
	float _delta;
};

