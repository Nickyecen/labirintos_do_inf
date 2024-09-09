#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <raylib.h>

#include "map.hpp"

#define WALKING_SPEED 1.5f
#define SPRINTING_SPEED 4.5f
#define SENSITIVITY 0.25f
#define COLLISION_SIZE 0.1f
#define PLAYER_HEIGHT 1.7f

class Player {
    // VARIABLES
    private:
        int row, col;

        int bombs = 0, credits = 0, health = 3, life = 3, timeRemaining = 0;

        Vector3 position;
        Camera3D* camera;

        BoundingBox collisionBox;
        BoundingBox viewBox;
   
    // METHODS
    public:
        Player(Vector2 pos);

        void update(Map&);

        void incBomb();
        void incHealth();
        void incLife();
        void addCredits(int);
        void addTime(int);

        int getRow() const;
        int getCol() const;
        Camera3D* getCamera() const;
        BoundingBox getCollision() const;
        BoundingBox getViewBox() const;

    private:
        Vector3 getMovement(Map&);
        Vector3 getRotation();
};

#endif
