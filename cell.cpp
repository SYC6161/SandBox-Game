#include "src\include\headers\main.hpp"


CellManager::CellManager()
{
    for(int i = 0; i< width;i++)
    {
        for(int j =0;j< height;j++)
        {
            old_frame_grid[i][j].id = air;
            new_frame_grid[i][j].id = air;
        }
    }
}

void CellManager::Update()
{
	for (int i = 0; i < width - 1; i++)
	{
		for (int j = 0; j < height - 1; j++)
		{
			if (old_frame_grid[i][j].id == air) 	new_frame_grid[i][j].occupied = false;

			if (old_frame_grid[i][j].id == sand) updateSand(i, j);
			
			if (old_frame_grid[i][j].id == water) updateWater(i, j);

			if (old_frame_grid[i][j].id == gas) updateGas(i, j);
		}

	}
}

void CellManager::Draw(sf::RenderWindow& _window)
{

	for (int i = 0; i < width - 1; i++)
	{
		for (int j = 0; j < height - 1; j++)
		{

			if (new_frame_grid[i][j].id == sand) {
				sf::RectangleShape _sandShape = sf::RectangleShape();
				_sandShape.setPosition({i * cell_size, j * cell_size});
				_sandShape.setSize(sf::Vector2f(cell_size, cell_size));
				_sandShape.setFillColor(sf::Color::Yellow);

				_window.draw(_sandShape);
			}
			if (new_frame_grid[i][j].id == stone) {
				sf::RectangleShape _stoneShape = sf::RectangleShape();
				_stoneShape.setPosition({i * cell_size, j * cell_size});
				_stoneShape.setSize(sf::Vector2f(cell_size, cell_size));
				_stoneShape.setFillColor(sf::Color::White);

				_window.draw(_stoneShape);
			}
			if (new_frame_grid[i][j].id == water) {
				sf::RectangleShape _waterShape = sf::RectangleShape();
				_waterShape.setPosition({i * cell_size, j * cell_size});
				_waterShape.setSize(sf::Vector2f(cell_size, cell_size));
				_waterShape.setFillColor(sf::Color::White);

				_window.draw(_waterShape);
			}
            if (new_frame_grid[i][j].id == gas) {
				sf::RectangleShape _gasShape = sf::RectangleShape();
				_gasShape.setPosition({i * cell_size, j * cell_size});
				_gasShape.setSize(sf::Vector2f(cell_size, cell_size));
				_gasShape.setFillColor(sf::Color::White);

				_window.draw(_gasShape);
			}

			old_frame_grid[i][j] = new_frame_grid[i][j];

		}
	}
}

void CellManager::Clear()
{
	for (int i = 0; i < width - 1; i++)
	{
		for (int j = 0; j < height - 1; j++)
		{
			old_frame_grid[i][j].id = air;
			new_frame_grid[i][j].id = air;
		}
	}
}

void CellManager::CreateSand(int posX, int posY)
{
	new_frame_grid[posX][posY].id = sand;
}

void CellManager::CreateStone(int posX, int posY)
{
	new_frame_grid[posX][posY].id = stone;
}

void CellManager::CreateWater(int posX, int posY)
{
	new_frame_grid[posX][posY].id = water;
}

void CellManager::CreateGas(int posX, int posY)
{
	new_frame_grid[posX][posY].id = gas;
}

void CellManager::DeleteCell(int posX, int posY)
{
	new_frame_grid[posX][posY].id = air;

}

void CellManager::updateSand(int posX, int posY)
{
		new_frame_grid[posX][posY].occupied = true;

		bool _downwardLeft = false, _downwardRight = false, _down = false;
	
		if (old_frame_grid[posX][posY + 1].id == air) { // if air below - fall down 
			_down = true;
		}
		if (old_frame_grid[posX - 1][posY + 1].id == air) {
			_downwardLeft = true;
		}
		if (old_frame_grid[posX + 1][posY + 1].id == air) {
			_downwardRight = true;
		}

		if (_downwardLeft && _downwardRight) {
			bool _dir = rand() % 2;
			if (_dir == 0) {
				_downwardLeft = true;
				_downwardRight = false;
			}
			else if (_dir == 1) {
				_downwardLeft = false;
				_downwardRight = true;
			}
		}

		if (old_frame_grid[posX][posY + 1].id == water) {
			new_frame_grid[posX][posY].id = water;
			new_frame_grid[posX][posY + 1].id = sand;
		}

		if (_down) {
			new_frame_grid[posX][posY].id = air;
			new_frame_grid[posX][posY + 1].id = sand;
		}
		else if (_downwardLeft) {
			new_frame_grid[posX][posY].id = air;
			new_frame_grid[posX - 1][posY + 1].id = sand;
		}
		else if (_downwardRight) {
			new_frame_grid[posX][posY].id = air;
			new_frame_grid[posX + 1][posY + 1].id = sand;
		}

	
}
void CellManager::updateWater(int posX, int posY)
{
	new_frame_grid[posX][posY].occupied = true;


	bool _left = false, _right = false, _down = false, _downwardLeft = false, _downwardRight = false;

	if (old_frame_grid[posX][posY + 1].id == air) { // if air below - fall down 
		_down = true;
	}
	if (old_frame_grid[posX - 1][posY + 1].id == air) {
		_downwardLeft = true;
	}
	if (old_frame_grid[posX + 1][posY + 1].id == air) {
		_downwardRight = true;
	}
	if (old_frame_grid[posX - 1][posY].id == air) {
		_left = true;
	}
	if (old_frame_grid[posX + 1][posY].id == air) {
		_right = true;
	}
	
	if (_down) {
		new_frame_grid[posX][posY].id = air;
		new_frame_grid[posX][posY + 1].id = water;
	}
	else if (_downwardLeft) {
	
		new_frame_grid[posX][posY].id = air;
		new_frame_grid[posX - 1][posY + 1].id = water;
	}
	else if (_downwardRight) {
	
		new_frame_grid[posX][posY].id = air;
		new_frame_grid[posX + 1][posY + 1].id = water;
	}
	else if (_left && old_frame_grid[posX - 1][posY].occupied == false) {
		old_frame_grid[posX - 1][posY].occupied = true;
		new_frame_grid[posX][posY].id = air;
		new_frame_grid[posX - 1][posY].id = water;
	}
	else if (_right && old_frame_grid[posX + 1 ][posY].occupied == false) {
		old_frame_grid[posX + 1][posY].occupied = true;
		new_frame_grid[posX][posY].id = air;
		new_frame_grid[posX + 1][posY].id = water;
	}    
}


void CellManager::updateGas(int posX, int posY)
{
	new_frame_grid[posX][posY].occupied = true;


	bool _left = false, _right = false, _down = false, _downwardLeft = false, _downwardRight = false;

	if (old_frame_grid[posX][posY + 1].id == air) { // if air below - fall down 
		_down = true;
	}
	if (old_frame_grid[posX - 1][posY + 1].id == air) {
		_downwardLeft = true;
	}
	if (old_frame_grid[posX + 1][posY + 1].id == air) {
		_downwardRight = true;
	}
	if (old_frame_grid[posX - 1][posY].id == air) {
		_left = true;
	}
	if (old_frame_grid[posX + 1][posY].id == air) {
		_right = true;
	}
	
	if (_down) {
		new_frame_grid[posX][posY].id = air;
		new_frame_grid[posX][posY - 1].id = gas;
	}
	else if (_downwardLeft) {
	
		new_frame_grid[posX][posY].id = air;
		new_frame_grid[posX + 1][posY - 1].id = gas;
	}
	else if (_downwardRight) {
	
		new_frame_grid[posX][posY].id = air;
		new_frame_grid[posX - 1][posY - 1].id = gas;
	}
	else if (_left && old_frame_grid[posX + 1][posY].occupied == false) {
		old_frame_grid[posX + 1][posY].occupied = true;
		new_frame_grid[posX][posY].id = air;
		new_frame_grid[posX + 1][posY].id = gas;
	}
	else if (_right && old_frame_grid[posX - 1 ][posY].occupied == false) {
		old_frame_grid[posX - 1][posY].occupied = true;
		new_frame_grid[posX][posY].id = air;
		new_frame_grid[posX - 1][posY].id = gas;
	}
}
