#ifndef ITEMS_HPP
#define ITEMS_HPP

#include <raylib.h>
#include <vector>

#include "map.hpp"
#include "player.hpp"

#define ITEM_SIZE 0.6f

class Item {
    // VARIABLES
    public:
        static std::vector<Item*> items;
    protected: 
        Vector3 position;
        Model* model = nullptr;
        BoundingBox collisionBox;
        float scale = 1.0f;
    private:
        float rotation = 0;

    // METHODS
    public:
        static void drawItems();
        virtual void get(Player& player) = 0;
        void draw() const;
        void update();
    protected:
        void initializeItem(Model* model, int row, int col);
};

class Bomb : public Item {
    // VARIABLES
    private:
        static Model* bombModel;
    // METHODS
    public:
        Bomb(int row, int col);
        void get(Player& player);
};

class Credit : public Item {
    // VARIABLES
    private:
        int credits;
        static Model* creditModel;
    // METHODS
    public:
        Credit(int row, int col, int credits);
        void get(Player& player);
};

class Health : public Item {
    // VARIABLES
    private:
        static Model* healthModel;
    // METHODS
    public:
        Health(int row, int col);
        void get(Player& player);
};

class Life : public Item {
    // VARIABLES
    private:
        static Model* lifeModel;
    // METHODS
    public:
        Life(int row, int col);
        void get(Player& player);
};

class Clock : public Item {
    // VARIABLES
    private:
        int time;
        static Model* clockModel;
    // METHODS
    public:
        Clock(int row, int col, int time);
        void get(Player& player);
};

#endif
