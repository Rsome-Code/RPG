/*#include <SFML/Graphics.hpp>
#include <windows.h>
#include <XInput.h>
#include "Controller.cpp"
#include <iostream>
#include <chrono>
#include <thread>
using namespace std;

using namespace std::chrono; // nanoseconds, system_clock, seconds


template <
    class result_t = std::chrono::milliseconds,
    class clock_t = std::chrono::steady_clock,
    class duration_t = std::chrono::milliseconds
>
auto since(std::chrono::time_point<clock_t, duration_t> const& start)
{
    return std::chrono::duration_cast<result_t>(clock_t::now() - start);
}


int main2()
{
    TController* controller0;
    controller0 = new TController(0);
    string lastFrame = "";
    int i = 0;
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "SFML works!");

    sf::Texture texture;
    sf::Texture background;
    if (!texture.loadFromFile("Assets\\NES - Final Fantasy - Light Warriors.png"))
    {
        cout << "Error";
    }
    sf::Vector2u size = texture.getSize();
    std::cout << "Width: " << size.x << ", Height: " << size.y << std::endl;
    if (!background.loadFromFile("Assets\\grids-4.png"))
    {
        cout << "Error";
    }
    sf::Sprite sprite;
    sprite.setTexture(texture);
    sf::Sprite sword;
    sword.setTexture(texture);
    sf::Sprite back;
    back.setTexture(background);


    sf::Clock clock;

    double targetRate = 120;
    int speed = 200;
    double posi = 0;
    double universalX = 0;
    double universalY = 0;

    ///////////////////////////////////////////////////////////////
    while (window.isOpen())
    {
        int wait = 0;

        universalX = 960 - posi;

        auto start = std::chrono::steady_clock::now();


        
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        sprite.setScale(sf::Vector2f(6.f, 6.f));

        tuple <int, int, int, int> ack;

        ack = make_tuple(377, 5, 16, 24);

        tuple <int, int, int, int> s;

        s = make_tuple(135, 159, 16, 16);
        sword.setTextureRect(sf::IntRect(get<0>(s), get<1>(s), get<2>(s), get<3>(s)));
        sword.setPosition(sf::Vector2f(1000.f +universalX, 500.f+ universalY));
        sprite.setPosition(sf::Vector2f(posi +universalX, 580.f+ universalY));
        back.setPosition(sf::Vector2f(universalX, universalY));
        sword.setScale(sf::Vector2f(6.f, 6.f));
        back.setScale(sf::Vector2f(0.5f, 0.5f));

        sprite.setTextureRect(sf::IntRect(get<0>(ack), get<1>(ack), get<2>(ack), get<3>(ack)));







        window.clear();
        window.draw(back);
        window.draw(sword);
        window.draw(sprite);
        
        //window.draw(shape);
        window.display();


        if (controller0->IsConnected())
        {
            if (controller0->GetState().Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT)
            {
                speed = 200;
                
                
            }
            else if (controller0->GetState().Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT)
            {
                speed = -200;
            }
            else {
                speed = 0;
            }
        }


        


        //Frame limiter
        
        double targetDelta = (1 / targetRate) * 1000000000;
        double delta = since<nanoseconds>(start).count();

        while (delta <= targetDelta) {
            delta = since<nanoseconds>(start).count();
        }



        //if (targetDelta >= delta) {
            // wait = ((targetDelta) - (delta));
            //wait = wait;
            //sleep_for(nanoseconds(wait));
        //}
        //sleep_until(system_clock::now() + seconds(1));

        double delta1 = since<nanoseconds>(start).count();
        int frame = 1 / (delta1 / 1000000000);

        cout << frame;
        cout << ". ";

        double last = since<nanoseconds>(start).count();
        double since1 = last / 1000000000;
        double move = since1 * speed;
        posi = posi + move;

        
    }
    return 0;
}*/