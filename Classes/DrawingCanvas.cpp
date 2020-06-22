#include "DrawingCanvas.h"
#include "cocos2d/cocos/ui/CocosGUI.h"
#include <Constants.h>

using namespace cocos2d;


DrawingCanvas::DrawingCanvas()
{
}


DrawingCanvas::~DrawingCanvas()
{
}

//Initializing the scene
bool DrawingCanvas::init()
{
	if (!Node::init()) {
		return false;
	}

	drawNode = DrawNode::create();

	background = LayerColor::create(Color4B(COLOR_WHITE));
	addChild(background);

	addChild(drawNode);

	selectedColor = COLOR_GREEN;

	return true;
}

//Runs after the scene is loaded completely
void DrawingCanvas::onEnter()
{
	Node::onEnter();

	Size visibleSize = CCDirector::getInstance() -> getVisibleSize();

	setContentSize(visibleSize);//DrawingCanvas content size
	drawNode->setContentSize(visibleSize);

	setupTouchHandling();

	setupMenus();
}

//last touched position on the screen
static Vec2 lastTouchPos;

//Manages different touch states
void DrawingCanvas::setupTouchHandling()
{
	static Vec2 lastTouchPos;
	static float lastRadius = INITIAL_RADIUS;
	auto touchListener = EventListenerTouchOneByOne::create();

	touchListener->onTouchBegan = [&](Touch * touch, Event * event)
	{
		lastTouchPos = drawNode->convertTouchToNodeSpace(touch);
		lastRadius = INITIAL_RADIUS;
		return true;//Rturns true in order for "onTouchMoved" to work
	};

	touchListener->onTouchMoved = [&](Touch * touch, Event * event)
	{
		Vec2 touchPos = drawNode->convertTouchToNodeSpace(touch);

		//infinite impulse response filter - lowpass filter
		float distance = lastTouchPos.distance(touchPos);
		float dt = 1.0f / 60.0f;
		float rc = 1.0f;
		float alpha = dt / (rc + dt);
		float radius = (alpha * distance) + (1.0f - alpha) * lastRadius;

		 drawNode->drawSegment(lastTouchPos, touchPos, radius, selectedColor);

		 lastRadius = radius;
		 lastTouchPos = touchPos;
	};

	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, this);
}

//Shows different buttons on the canvas
void DrawingCanvas::setupMenus()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	//Size visibleSize = CCDirector::getInstance()->getVisibleSize();

	//clear button
	auto clearButton = ui::Button::create();
	clearButton->setAnchorPoint(Vec2(1.0f, 1.0f));
	clearButton->setPosition(Vec2(visibleSize.width, visibleSize.height));
	clearButton->loadTextures("clearButton.png", "clearButtonPressed.png");
	clearButton->addTouchEventListener(CC_CALLBACK_2(DrawingCanvas::clearPressed, this));
	this->addChild(clearButton);


	//back button
	auto backButton = ui::Button::create();
	backButton->setAnchorPoint(Vec2(0.0f, 1.0f));
	backButton->setPosition(Vec2(0.0f, visibleSize.height));
	backButton->loadTextures("backButton.png", "backButtonPressed.png");
	backButton->addTouchEventListener(CC_CALLBACK_2(DrawingCanvas::backPressed, this));
	this->addChild(backButton);

	//check sprite
	check = Sprite::create("checkMark.png");
	check->setAnchorPoint(Vec2(0.5f, 0.5f));
	check->setPositionNormalized(Vec2(0.5f, 0.5f));

	//color button layout
	auto colorButonLayout = Node::create();
	colorButonLayout->setContentSize(Size(visibleSize.width, visibleSize.height * 0.2f));
	colorButonLayout->setAnchorPoint(Vec2(0.5f, 0.0f));
	colorButonLayout->setPosition(Vec2(visibleSize.width * 0.5, 0.0));
	addChild(colorButonLayout);

	//adding colors to the colorButtonLayout
	for (auto i = 1; i <= 5; ++i) 
	{
		auto colorButton = ui::Button::create();
		colorButton->setAnchorPoint(Vec2(0.5f, 0.5f));
		colorButton->setPosition(Vec2(visibleSize.width * i*(1.0f / 6.0f), 40.0f));
		colorButton->loadTextures("colorSwatch.png", "colorSwatch.png");
		colorButton->addTouchEventListener(CC_CALLBACK_2(DrawingCanvas::colorChangePressed,this));

		switch (i)//deciding colors
		{
		case 1:
			colorButton->setColor(Color3B(COLOR_RED));
			break;
		case 2:
			colorButton->setColor(Color3B(COLOR_YELLOW));
			break;
		case 3:
			colorButton->setColor(Color3B(COLOR_GREEN));
			colorButton->addChild(this->check);//Adds check mark on the button(default color is green)
			break;
		case 4:
			colorButton->setColor(Color3B(COLOR_BLUE));
			break;
		case 5:
			colorButton->setColor(Color3B(COLOR_PURPLE));
			break;
		default:
			colorButton->setColor(Color3B(COLOR_GREEN));
			colorButton->addChild(this->check);
			break;
		}
		

		colorButonLayout->addChild(colorButton);//Adds each button to the layout
	}
}

//Triggers when clear button is pressed - Clears the canvas
void DrawingCanvas::clearPressed(Ref* pSender, ui::Widget::TouchEventType eEventType)
{
	if (eEventType == ui::Widget::TouchEventType::ENDED)//When the touch is ended 
	{
		drawNode->clear();
	}
}

//Triggers when back button is pressed - Brings lobby scene up
void DrawingCanvas::backPressed(Ref* pSender, ui::Widget::TouchEventType eEventType)
{
	if (eEventType == ui::Widget::TouchEventType::ENDED)//When the touch is ended 
	{
		Director::getInstance()->popScene();//Pops the last scene from stack
	}
}

//Triggers when color buttons are pressed - Changes drawing color
void DrawingCanvas::colorChangePressed(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType eEventType)
{
	auto pressedButton = static_cast<ui::Button*>(pSender);

	pressedButton->setScale(1.25f);

	if (eEventType == ui::Widget::TouchEventType::ENDED 
		|| eEventType == ui::Widget::TouchEventType::CANCELED)
	{
		pressedButton->setScale(1.0f);
	}

	if (eEventType == ui::Widget::TouchEventType::ENDED)
	{
		
		selectedColor =(Color4F) pressedButton->getColor();
	}
	check->retain();
	check->removeFromParent();
	pressedButton->addChild(check);
	check->release();
}
