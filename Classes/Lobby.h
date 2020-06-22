#ifndef Doodler_Lobby
#define Doodler_Lobby

#include "cocos2d.h"
#include "cocos2d/cocos/ui/CocosGUI.h";

class Lobby: public cocos2d::Node
{
public:
	Lobby();
	~Lobby();
	CREATE_FUNC(Lobby);

protected:
	
	bool init() override;	
	void onEnter() override;

	
	void setupUi();
	
	void soloPressed(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType eEventType);
	void duoPressed(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType eEventType);

};

#endif /* defined(Doodler_Lobby)  */