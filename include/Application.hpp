#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include <console/GameConsole.hpp>

#include <SFML/System/Time.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Window/Event.hpp>

#include <iostream>
#include <vector>
#include <string>




class Application
{
public:
    sf::RenderWindow        mWindow;
    GameConsole             mConsole;

private:
    static const sf::Time   TimePerFrame;


public:
                            Application();
                            ~Application();

    void                    Run();
    void                    Init();
    void                    DefaultCom(const std::vector<std::string>& args);
    void                    CCExit(const std::vector<std::string>& args);
private:
    void                    ProcessInput();
    void                    Update(sf::Time dt);
    void                    Render();

};
#endif // APPLICATION_HPP
