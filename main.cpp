#include "src\include\headers\main.hpp"

bool sandSelect = true, stoneSelect = false,waterSelect=false,gasSelect=false;


const float tickRate = 0.01f;

float updateRate = tickRate;

int main()
{
    sf::Clock clock;
    sf::RenderWindow window(sf::VideoMode({400, 400}), "SFML works!",sf::Style::Close);

    window.setFramerateLimit(120);
    
    CellManager simulation;

    while (window.isOpen())
    {
        window.clear();

        while (const std::optional event = window.pollEvent())
        {
            if(event->is<sf::Event::Closed>())
            {
                window.close();
            }

            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num1))
            {
                sandSelect = true;
                stoneSelect = false;
                waterSelect = false;
                gasSelect = false;
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num2))
            {
                sandSelect = false;
                stoneSelect = true;
                waterSelect = false;
                gasSelect = false;    
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num3))
            {
                sandSelect = false;
                stoneSelect = false;
                waterSelect = true;
                gasSelect = false;
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num4))
            {
                sandSelect = false;
                stoneSelect = false;
                waterSelect = false;
                gasSelect = true;
            }

            sf::Vector2i pos = sf::Mouse::getPosition(window);

            int posX = floor(pos.x /simulation.cell_size);
            int posY = floor(pos.y /simulation.cell_size);

            if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
            {
                if(sandSelect) simulation.CreateSand(posX,posY);
                else if(waterSelect) simulation.CreateWater(posX,posY);
                else if (stoneSelect) simulation.CreateStone(posX,posY);
                else if(gasSelect) simulation.CreateGas(posX,posY);
            }else if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Right))
            {
                simulation.DeleteCell(posX,posY);
            }else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::R))
            {
                simulation.Clear();
            }
        }
        
        float t = clock.restart().asSeconds();
        updateRate -= t;

        if(updateRate< 0.0f)
        {
            simulation.Update();
            updateRate = tickRate;
        }

        simulation.Draw(window);
    
        window.display();
    }
}