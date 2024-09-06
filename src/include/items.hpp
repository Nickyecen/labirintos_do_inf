#ifndef ITEMS_HPP
#define ITEMS_HPP

#include <raylib.h>
#include <vector>
#include <algorithm>

#include "map.hpp"
#include "player.hpp"

#define ITEM_SIZE 0.6f
#define ITEM_SPEED 30

class Item {
    // VARIABLES
    public:
        static std::vector<Item*> items;
    protected: 
        Vector3 position;
        int row;
        int col;
        bool collected = false;
        Model* model = nullptr;
        BoundingBox collisionBox;
        float scale = 1.0f;
    private:
        float rotation = 0;

    // METHODS
    public:
        static void drawItems(bool debug);
        static void updateItems(Player& player);
        static void genRandom(Map& map, int numCredits, int numLives, int numHealth, int numBombs, int numTime);

        ~Item();

        virtual void get(Player& player) = 0;

        void draw() const;
        void drawBB() const;
        void update(Player& player);
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
        void get(Player& player) override;
};

class Credit : public Item {
    // VARIABLES
    private:
        int credits;
        static Model* creditModel;
    // METHODS
    public:
        Credit(int row, int col, int credits);
        void get(Player& player) override;
};

class Health : public Item {
    // VARIABLES
    private:
        static Model* healthModel;
    // METHODS
    public:
        Health(int row, int col);
        void get(Player& player) override;
};

class Life : public Item {
    // VARIABLES
    private:
        static Model* lifeModel;
    // METHODS
    public:
        Life(int row, int col);
        void get(Player& player) override;
};

class Clock : public Item {
    // VARIABLES
    private:
        int time;
        static Model* clockModel;
        static Texture* diffuse;
    // METHODS
    public:
        Clock(int row, int col, int time);
        void get(Player& player) override;
};

#endif
