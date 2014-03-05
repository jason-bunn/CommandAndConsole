#include <console/GameConsole.hpp>

GameConsole::GameConsole(sf::RenderWindow& window)
: mWindow(window)
, bActive(false)
, backgroundRect(sf::Vector2f(mWindow.getSize().x, 100))
, mFont()
, mCurrentCommand()
{
    mFont.loadFromFile("media/clacon.ttf");

    backgroundRect.setFillColor(sf::Color(150,150,150));
    backgroundRect.setOutlineThickness(5);
    backgroundRect.setOutlineColor(sf::Color(200,200,200));

    mCurrentCommand.setFont(mFont);
    mCurrentCommand.setCharacterSize(20);
    mCurrentCommand.setPosition(5, 74);
    mCurrentCommand.setColor(sf::Color::Black);

}

GameConsole::~GameConsole()
{

}

void GameConsole::Update()
{
    mCurrentCommand.setString(mCommandLine);
}

void GameConsole::Render()
{
    if(bActive)
    {
        mWindow.draw(backgroundRect);
        mWindow.draw(mCurrentCommand);
    }
}

void GameConsole::AddItem()
{

}

void GameConsole::RemoveItem()
{

}

void GameConsole::SetDefaultCommand()
{

}

void GameConsole::Print(const std::string& strText)
{

}

void GameConsole::PassKey(char key)
{
    if(key > 31 && key < 126)
    {
        if(key != 96)
            mCommandLine += key;
    }
    //if backspace
    if(key == 8)
        PassBackspace();
    //if enter
    if(key == 13)
    {
        PassIntro();
    }
}

void GameConsole::PassBackspace()
{
    if(mCommandLine.length() >0)
    {
        mCommandLine.pop_back();
    }
}

void GameConsole::PassIntro()
{

}

bool GameConsole::ParseCommandLine()
{
    return false;
}


bool GameConsole::IsConsoleActive()
{
    return bActive;
}

void GameConsole::OpenConsole()
{
    mCommandLine = "";
    bActive = true;
}

void GameConsole::CloseConsole()
{
    bActive = false;
}
