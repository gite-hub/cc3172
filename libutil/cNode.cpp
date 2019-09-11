#include "cNode.h"

// #if defined(__GNUC__) && ((__GNUC__ >= 4) || ((__GNUC__ == 3) && (__GNUC_MINOR__ >= 1)))
// #pragma GCC diagnostic warning "-Wdeprecated-declarations"
// #elif _MSC_VER >= 1400 //vs 2005 or higher
// #pragma warning (pop)
// #endif
/// LayerColor

cNode::cNode()
{
	// default blend function
	_blendFunc = BlendFunc::ALPHA_PREMULTIPLIED;
}

cNode::~cNode()
{
}

/// blendFunc getter
const BlendFunc &cNode::getBlendFunc() const
{
	return _blendFunc;
}
/// blendFunc setter
void cNode::setBlendFunc(const BlendFunc &var)
{
	_blendFunc = var;
}

cNode* cNode::create(const sColor& color /* = sColor::WHITE */)
{
	CREATE(cNode, color);
}

bool cNode::init(const sColor& color)
{
	if (Node::init())
	{

		// default blend function
		_blendFunc = BlendFunc::ALPHA_NON_PREMULTIPLIED;

		_displayedColor.r = _realColor.r = color.r;
		_displayedColor.g = _realColor.g = color.g;
		_displayedColor.b = _realColor.b = color.b;
		_displayedOpacity = _realOpacity = 0xFF;

		for (size_t i = 0; i < sizeof(_squareVertices) / sizeof(_squareVertices[0]); i++)
		{
			_squareVertices[i].x = 0.0f;
			_squareVertices[i].y = 0.0f;
		}

		updateColor();

		setGLProgramState(GLProgramState::getOrCreateWithGLProgramName(GLProgram::SHADER_NAME_POSITION_COLOR_NO_MVP));
		return true;
	}
	return false;
}

/// override contentSize
void cNode::setContentSize(const Size & size)
{
	_squareVertices[1].x = size.width;
	_squareVertices[2].y = size.height;
	_squareVertices[3].x = size.width;
	_squareVertices[3].y = size.height;

	Node::setContentSize(size);
}

void cNode::updateColor()
{
	for (unsigned int i = 0; i < 4; i++)
	{
		_squareColors[i].r = _displayedColor.r / 255.0f;
		_squareColors[i].g = _displayedColor.g / 255.0f;
		_squareColors[i].b = _displayedColor.b / 255.0f;
		_squareColors[i].a = _displayedOpacity / 255.0f;
	}
}

void cNode::draw(Renderer *renderer, const Mat4 &transform, uint32_t flags)
{
	_customCommand.init(_globalZOrder, transform, flags);
	_customCommand.func = CC_CALLBACK_0(cNode::onDraw, this, transform, flags);
	renderer->addCommand(&_customCommand);

	for (int i = 0; i < 4; ++i)
	{
		Vec4 pos;
		pos.x = _squareVertices[i].x; pos.y = _squareVertices[i].y; pos.z = _positionZ;
		pos.w = 1;
		_modelViewTransform.transformVector(&pos);
		_noMVPVertices[i] = Vec3(pos.x, pos.y, pos.z) / pos.w;
	}
}

void cNode::onDraw(const Mat4& transform, uint32_t /*flags*/)
{
	getGLProgram()->use();
	getGLProgram()->setUniformsForBuiltins(transform);

	GL::enableVertexAttribs(GL::VERTEX_ATTRIB_FLAG_POSITION | GL::VERTEX_ATTRIB_FLAG_COLOR);

	//
	// Attributes
	//
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_POSITION, 3, GL_FLOAT, GL_FALSE, 0, _noMVPVertices);
	glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_COLOR, 4, GL_FLOAT, GL_FALSE, 0, _squareColors);

	GL::blendFunc(_blendFunc.src, _blendFunc.dst);

	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	CC_INCREMENT_GL_DRAWN_BATCHES_AND_VERTICES(1, 4);
}