#ifndef CONSOLE_GAMECONSOLE_HPP
#define CONSOLE_GAMECONSOLE_HPP

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Font.hpp>

#include <string>

class GameConsole
{


private:
    sf::RenderWindow&       mWindow;
    bool                    bActive;
    sf::RectangleShape      backgroundRect;
    sf::Font                mFont;
    sf::Text                mCurrentCommand;

    std::string             mCommandLine;
public:
                            GameConsole(sf::RenderWindow& window);
                            ~GameConsole();

    void                    Update();
    void                    Render();

    void                    AddItem();
    void                    RemoveItem();
    void                    SetDefaultCommand();

    void                    Print(const std::string& strText);
    void                    PassKey(char key);
    void                    PassBackspace();
    void                    PassIntro();

    bool                    IsConsoleActive();
    void                    OpenConsole();
    void                    CloseConsole();

private:
    bool                    ParseCommandLine();
};
#endif // CONSOLE_GAMECONSOLE_HPP
