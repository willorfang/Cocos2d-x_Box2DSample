//
//  BallsLayer.h
//  PhysicsBalls
//
//  Created by Wei Fang on 3/7/14.
//
//

#ifndef __PhysicsBalls__BallsLayer__
#define __PhysicsBalls__BallsLayer__

#include "cocos2d.h"

class BallsLayer : public cocos2d::CCLayer {
    cocos2d::CCSprite* _background;
    bool _bTouchEnabled;
    
public:
    CREATE_FUNC(BallsLayer);
    bool init();
    void setTouchEnabled(bool enabled);
    bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent) { CCLOG("ccc"); return true; }
    void ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent) {}
    void ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
};

#endif /* defined(__PhysicsBalls__BallsLayer__) */
