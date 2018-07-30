#pragma once

#include <vector>
#include <memory>

#include <SFML/Graphics.hpp>

#include "HitBox.h"

class World;

class Entity: public sf::Drawable, public sf::Transformable, public std::enable_shared_from_this<Entity> {
    public:
        //friends
        friend World;

        //aliases
        template <class T> using Ptr = std::shared_ptr<T>;
        using BasePtr = Ptr<Entity>;
        using ClonePtr = std::shared_ptr<Entity>;

        //enumerations
        //flag used to optimize collisions by inhibiting double collision checking
        enum COLLISIONS_HANDLED_FLAG_T {
            COLLHANDLEDF_1   = 0,
            COLLHANDLEDF_2   = 1,
            COLLHANDLEDF_MAX = 2
        };
        //collision faction (collisions between entities of the same factions are not handled)
        enum COLLISION_FACTION_T {
            COLLFACT_NEUTRAL,
            COLLFACT_FRIEND,
            COLLFACT_ENEMY
        };

    protected:
        //media
        const sf::Texture* mTexture = nullptr;

        //graphics
        sf::RectangleShape mSprite;

        //hitbox (used to calculate collisions)
        hb::Ptr mHitBox = nullptr;

        //additional collision info
        int mCollisionDamage = -1;
        int mLife = -1;
        COLLISIONS_HANDLED_FLAG_T mCollisionsHandledFlag = COLLHANDLEDF_1;
        COLLISION_FACTION_T mCollisionFaction = COLLFACT_NEUTRAL;

        //true if entity needs to be despawned
        bool mToDespawn = false;

        //custom logic
        virtual void handleEvent(sf::RenderWindow& window, const sf::Event& event) {}
        virtual void vHandleLogic(sf::RenderWindow& window, const sf::Time& timeElapsed, COLLISIONS_HANDLED_FLAG_T collHFlag) {}
        virtual void vDraw(sf::RenderTarget& target, sf::RenderStates states) const {}
        virtual void vDie() {};
        virtual void onSpawn() {};

    public:
        //entity world
        static World* sWorld;

        //true if debug mode is activated
        static bool sDebugMode;

        //constructor
        Entity(const sf::Texture* texture, const sf::Vector2f& position, const sf::Vector2f& spriteSize,
               int collisionDamage, int life,
               hb::Ptr hitBox);
        Entity(const sf::Texture* texture, const sf::Vector2f& position, const sf::Vector2f& spriteSize);
        Entity(const sf::Texture* texture, const sf::Vector2f& position);
        Entity(const sf::Texture* texture);
        Entity();

        //destructor
        virtual ~Entity() {}

        //copy constructor
        Entity(const Entity& other);

        //getters and setters
        virtual void setPosition(const sf::Vector2f& position);
        void setPosition(float x, float y) {setPosition(sf::Vector2f(x, y));}

        void move(const sf::Vector2f& displacement);
        void move(float dx, float dy) {move(sf::Vector2f(dx,dy));}

        const sf::Texture* getTexture() const {return mTexture;}
        void setTexture(const sf::Texture* texture) {mTexture = texture; mSprite.setTexture(texture);}

        const sf::Vector2f& getSpriteSize() const {return mSprite.getSize();}
        void setSpriteSize(const sf::Vector2f& size) {mSprite.setSize(size);}

        const hb::HitBox& getHitBox() const {return *mHitBox;}

        int getCollisionDamage() const {return mCollisionDamage;}
        void setCollisionDamage(int collisionDamage) {mCollisionDamage = collisionDamage;}

        int getLife() const {return mLife;}
        bool isDead() const {return mLife <= 0;}
        void setLife(int life) {mLife = life;}

        void setCollisionsHandledFlag(COLLISIONS_HANDLED_FLAG_T collHFlag) {mCollisionsHandledFlag = collHFlag;}

        COLLISION_FACTION_T getCollisionFaction() const {return mCollisionFaction;}
        void setCollisionFaction(COLLISION_FACTION_T collFact) {mCollisionFaction = collFact;}

        //clone
        virtual ClonePtr clone() const = 0;

        //remove from game
        void die();

        //collision interface
        bool canCollide() const {return bool(mHitBox);}
        bool isColliding(const Entity& collider) const {assert(canCollide() && collider.canCollide() && "checking entity-entity collision with no hitbox");
                                                        return mHitBox->isColliding(collider.getHitBox());}
        bool collisionsHandled(COLLISIONS_HANDLED_FLAG_T flag) const {return mCollisionsHandledFlag == flag;}
        static void advanceCollisionsHandledFlag(COLLISIONS_HANDLED_FLAG_T& collHFlag) {collHFlag = COLLISIONS_HANDLED_FLAG_T((collHFlag + 1) % COLLHANDLEDF_MAX);}

        //handle collisions with other entities
        void handleEntityCollision(const BasePtr& collider);

        //forced logic
        void handleLogic(sf::RenderWindow& window, const sf::Time& timeElapsed, COLLISIONS_HANDLED_FLAG_T collHFlag);
        void draw(sf::RenderTarget& target, sf::RenderStates states) const override final;
};
