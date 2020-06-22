#pragma once

#include "cocos2d.h"
#include "cocos2d/cocos/ui/CocosGUI.h"

class DrawingCanvas: public cocos2d::Node
{
public:
	CREATE_FUNC(DrawingCanvas);
	DrawingCanvas();
	~DrawingCanvas();
protected:
	cocos2d::DrawNode* drawNode;

	
	bool init() override;
	void onEnter() override;

	void setupTouchHandling();
	void setupMenus();
	
	void clearPressed(Ref* pSender, cocos2d::ui::Widget::TouchEventType eEventType);
	void backPressed(Ref* pSender, cocos2d::ui::Widget::TouchEventType eEventType);

	void colorChangePressed(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType eEventType);

	//-------------------
	cocos2d::LayerColor* background;
	cocos2d::Sprite* check;
	cocos2d::Color4F selectedColor;
	
};

