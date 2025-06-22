#include "SFML/Graphics.hpp"
#include <cmath>
#include <iostream>

struct Cell
{
    int id;
    bool occupied;
};

class CellManager
{
    static const int width = 133;
    static const int height = 133;

	Cell old_frame_grid[width][height];
	Cell new_frame_grid[width][height];

    public:
        CellManager();

        void Update();
        void Draw(sf::RenderWindow& _window);
        void Clear();
        void CreateSand(int posX,int posY);
        void CreateStone(int posX,int posY);
        void CreateWater(int posX,int posY);
        void CreateGas(int posX,int posY);
        void DeleteCell(int posX,int posY);
        int cell_size = 3;

    private:
        void updateSand(int posX,int posY);
        void updateWater(int posX,int posY);
        void updateGas(int posX,int posY);

        static const int air = 0;
        static const int sand = 1;
        static const int stone = 2;
        static const int water = 3;
        static const int gas = 4;

};

