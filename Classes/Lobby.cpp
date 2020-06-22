#include "Lobby.h"
#include <DrawingCanvas.h>
#include <Constants.h>

using namespace cocos2d;

Lobby::Lobby()
{
}


Lobby::~Lobby()
{
}

//Initializes the Lobby scene
bool Lobby::init()
{
	if (!Node::init())
	{
		return false;
	}

	LayerColor* background = LayerColor::create(Color4B(COLOR_WHITE));
	this->addChild(background);
	return true;
}

//Runs when the scene is loaded
void Lobby::onEnter()
{
	Node::onEnter();

	setupUi();
}

//Sets up the UI in the scene
void Lobby::setupUi()
{
	const Size visibleSize = Director::getInstance()->getVisibleSize();

	//logo settings and adding
	Sprite* logo = Sprite::create("doodlerLogo.png");
	logo->setAnchorPoint(Vec2(0.5f, 0.5f));
	logo->setPosition(visibleSize.width * 0.5f, visibleSize.height * 0.75f);
	addChild(logo);

	//solo button
	ui::Button* soloButton = ui::Button::create();
	soloButton->setAnchorPoint(Vec2(0.5f, 0.5f));
	soloButton->setPosition(Vec2(visibleSize.width /2.0f, visibleSize.height * 0.4f));
	soloButton->loadTextures("soloButton.png", "soloButtonPressed.png");
	soloButton->addTouchEventListener(CC_CALLBACK_2(Lobby::soloPressed, this));
	addChild(soloButton);

	//duo button
	ui::Button* duoButton = ui::Button::create();
	duoButton->setAnchorPoint(Vec2(0.5f, 0.5f));
	duoButton->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height * 0.25f));
	duoButton->loadTextures("duoButton.png", "duoButtonPressed.png");
	duoButton->addTouchEventListener(CC_CALLBACK_2(Lobby::duoPressed, this));
	addChild(duoButton);

}


//triggeres when the solo play button is pressed
void Lobby::soloPressed(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType eEventType)
{
	if (eEventType == ui::Widget::TouchEventType::ENDED)
	{
		Scene* scene = Scene::create();

		DrawingCanvas* drawingCanvas = DrawingCanvas::create();
		scene->addChild(drawingCanvas);

		Director::getInstance()->pushScene(scene);
	}
}

//triggeres when the duo play button is pressed
void Lobby::duoPressed(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType eEventType)
{
}
