//
//  BallsLayer.cpp
//  PhysicsBalls
//
//  Created by Wei Fang on 3/7/14.
//
//

#include "BallsLayer.h"
#include "B2Sprite.h"
#include "Box2DHandler.h"

USING_NS_CC;

bool BallsLayer::init() {
    if (CCLayer::init()) {
        // add background
        CCSize winSize = CCDirector::sharedDirector()->getWinSize();
        CCTexture2D* cache = CCTextureCache::sharedTextureCache()->addImage("background.jpg");
        _background = CCSprite::createWithTexture(cache);
        _background->setPosition(ccp(winSize.width*0.5,winSize.height*0.5));
        this->addChild(_background);
        
        //
        this->setTouchEnabled(true);
        this->addChild(Box2DHandler::sharedBox2DHandler());
        return true;
    }
    return false;
}

void BallsLayer::ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent) {
    // create sprite
    CCPoint point = CCDirector::sharedDirector()->convertToGL(pTouch->getLocationInView());
    B2Sprite* sprite = B2Sprite::create("ball.png");
    sprite->setPosition(point);
    
    // add to box2d world
    Box2DHandler* handler = Box2DHandler::sharedBox2DHandler();
    handler->addSprite(sprite);
}

void BallsLayer::setTouchEnabled(bool flag)
{
    if (_bTouchEnabled != flag){
        _bTouchEnabled = flag;
        if(flag){
            CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
        }else{
            CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
        }
    }
}