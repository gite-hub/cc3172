#pragma once
#include "_inc.h"

class cNode : public Node, public BlendProtocol
{
public:
	cNode();
	virtual ~cNode();

	static cNode* create(const sColor& color = sColor::WHITE);

	virtual void draw(Renderer *renderer, const Mat4 &transform, uint32_t flags) override;

	virtual void setContentSize(const Size & var) override;

	virtual const BlendFunc& getBlendFunc() const override;

	virtual void setBlendFunc(const BlendFunc& blendFunc) override;

protected:
	bool init(const sColor& color);

protected:
	void onDraw(const Mat4& transform, uint32_t flags);

	virtual void updateColor() override;

	BlendFunc _blendFunc;
	Vec2 _squareVertices[4];
	Color4F  _squareColors[4];
	CustomCommand _customCommand;
	Vec3 _noMVPVertices[4];
private:
	CC_DISALLOW_COPY_AND_ASSIGN(cNode);
};