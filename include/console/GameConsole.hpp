#ifndef CONSOLE_GAMECONSOLE_HPP
#define CONSOLE_GAMECONSOLE_HPP

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Time.hpp>

#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Font.hpp>

#include <string>
#include <iostream>
#include <vector>
#include <list>
#include <sstream>
#include <functional>
// Console item type constants

enum console_item_type_t
{
    CTYPE_UCHAR,
    CTYPE_CHAR,
    CTYPE_CHARP,
    CTYPE_UINT,
    CTYPE_INT,
    CTYPE_FLOAT,
    CTYPE_STRING,
    CTYPE_FUNCTION
};

// console function pointer
typedef std::function<void(const std::vector<std::string> &)> console_function;

//console item struct
typedef struct
{
    //console_item_t();

    //item name
    std::string name;

    //item type
    console_item_type_t type;

    //function callback or pointer to the value

    console_function FN;
    void *variable_ptr;

} console_item_t;

class GameConsole
{
private:
    //define item database type
    typedef std::list<console_item_t> ITEM_DB;

private:
    sf::RenderWindow&       mWindow;
    bool                    bActive;
    sf::RectangleShape      backgroundRect;
    sf::Font                mFont;
    sf::Text                mCurrentCommand;
    sf::Text                mCursor;
    std::list<sf::Text>   mTextDisplay;

    sf::Time                mBlinkTime;
    sf::Time                mBlinkTimer;

    // holds the command line
    std::string             mCommandLine;

    //command to be executed by default
    console_function        defaultCommand;

    //holds the list of items
    ITEM_DB                 mItemList;

    //actual line index in history
    int                     mLineIndex;

    // buffer sizes
    int                     mCommandBufferSize;
    int                     mTextBufferSize;

    //holds the text buffer
    std::list<std::string>  mTextBuffer;

    //holds the buffer for previously entered commands
    std::vector<std::string> mCommandBuffer;

    bool                    mCommandEcho;


public:
                            GameConsole(sf::RenderWindow& window);
                            ~GameConsole();

    void                    Update(sf::Time dt);
    void                    Render();

    void                    AddItem(const std::string& strName, void *pointer, console_function fn, console_item_type_t type);
    void                    RemoveItem(const std::string& strName);
    void                    SetDefaultCommand(console_function def);
    void                    SetCommandBufferSize(int size);
    void                    ClearCommandBuffer();
    void                    SetTextBufferSize(int size);
    void                    ClearTextBuffer();
    void                    HistoryGo(int where);

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
