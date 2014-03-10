//
//  Box2DHandler.h
//  PhysicsBalls
//
//  Created by Wei Fang on 3/7/14.
//
//

#ifndef __PhysicsBalls__Box2DHandler__
#define __PhysicsBalls__Box2DHandler__

#include "cocos2d.h"
#include "Box2D/Box2D.h"
#include "B2Sprite.h"

#include <set>
#include <map>

#define PTM_RADIO 32.0

class Box2DHandler : public cocos2d::CCNode, public b2ContactListener {
    b2World* _world;
    b2Body* _edgeBody;
    typedef std::pair<b2Fixture*, b2Fixture*> ContactItem;
    std::set<ContactItem> _contacts;
    static Box2DHandler* _handler;
    
    bool init();
    void dealCollisions();

public:
    static Box2DHandler* sharedBox2DHandler();
    ~Box2DHandler();

    // contact interfaces
    virtual void BeginContact(b2Contact* contact);
    virtual void EndContact(b2Contact* contact);
    virtual void PreSolve(b2Contact* contact, const b2Manifold* oldManifold){}
    virtual void PostSolve(b2Contact* contact, const b2ContactImpulse* impulse) {}
    
    virtual void update(float dt);
    void addSprite(B2Sprite* sprite);
    void removeSprite(B2Sprite* sprite);
};


#endif /* defined(__PhysicsBalls__Box2DHandler__) */
