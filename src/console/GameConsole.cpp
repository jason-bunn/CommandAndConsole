#include <console/GameConsole.hpp>

GameConsole::GameConsole(sf::RenderWindow& window)
: mWindow(window)
, bActive(false)
, backgroundRect(sf::Vector2f(mWindow.getSize().x, 100))
, mFont()
, mCurrentCommand()
, mLineIndex(0)
, defaultCommand(NULL)
, mCommandBufferSize(20)
, mTextBufferSize(50)
, mCommandEcho(true)

{
    mFont.loadFromFile("media/arial.ttf");

    backgroundRect.setFillColor(sf::Color(20,20,20));
    backgroundRect.setOutlineThickness(1);
    backgroundRect.setOutlineColor(sf::Color(255,179,0));

    mCurrentCommand.setFont(mFont);
    mCurrentCommand.setCharacterSize(16);
    mCurrentCommand.setPosition(5, 74);
    mCurrentCommand.setColor(sf::Color(255,179,0));

    mCursor.setFont(mFont);
    mCursor.setCharacterSize(16);
    mCursor.setPosition(5,74);
    mCursor.setColor(sf::Color(255,179,0));
    mCursor.setString("_");

    mBlinkTime = sf::seconds(0.25f);


}

GameConsole::~GameConsole()
{

}

void GameConsole::Update(sf::Time dt)
{
    mBlinkTimer += dt;


    //set the cursor to blink
    if(mBlinkTimer.asSeconds() > mBlinkTime.asSeconds())
    {
        if(mCursor.getColor() == sf::Color::Transparent)
        {
            mCursor.setColor(sf::Color(255,179,0));
        }
        else
        {
            mCursor.setColor(sf::Color::Transparent);
        }

        mBlinkTimer = sf::seconds(0);
    }
    //move cursor to end of string
    mCursor.setPosition(mCurrentCommand.getGlobalBounds().width + 5, 74);
    mCurrentCommand.setString(mCommandLine);
}

void GameConsole::Render()
{
    if(bActive)
    {
        int i = 0;
        mWindow.draw(backgroundRect);
        for(auto itr = mTextDisplay.rbegin(); itr != mTextDisplay.rend(); ++itr)
        {

            itr->setPosition(5, 58 - (i * itr->getCharacterSize()));

            mWindow.draw((*itr));
            i++;
        }
        mWindow.draw(mCurrentCommand);
        mWindow.draw(mCursor);
    }
}

void GameConsole::AddItem(const std::string& strName, void *pointer, console_function fn, console_item_type_t type)
{
    console_item_t it;

    //fill item properties
    it.name = strName;
    it.type = type;


    it.variable_ptr = pointer;


    it.FN = fn;


    //add item
    mItemList.push_back(it);
}

void GameConsole::RemoveItem(const std::string& strName)
{
    ITEM_DB::iterator itr;

    //find item
    for(itr = mItemList.begin(); itr != mItemList.end(); ++itr)
    {
        if(itr->name == strName)
        {
            mItemList.erase(itr);
            break;
        }
    }
}

void GameConsole::Print(const std::string& strText)
{
    sf::Text text(strText, mFont);
    text.setColor(sf::Color(255,179,0));
    text.setCharacterSize(16);

    mTextDisplay.push_back(text);
    mTextBuffer.push_back(strText);

    //check bounds
    if(mTextBuffer.size() > mTextBufferSize)
    {
        mTextBuffer.pop_front();
        mTextDisplay.pop_front();
    }
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
    if(mCommandLine.length() > 0)
    {
        ParseCommandLine();
    }
}

bool GameConsole::ParseCommandLine()
{
    std::cout << "Parsing command" << std::endl;


    std::ostringstream out;
    std::string::size_type index = 0;
    std::vector<std::string> arguments;
    ITEM_DB::const_iterator itr;

    if(mCommandEcho)
    {
        Print(mCommandLine);
    }

    //add command line to buffer
    mCommandBuffer.push_back(mCommandLine);
    if(mCommandBuffer.size() > mCommandBufferSize)
    {
        mCommandBuffer.erase(mCommandBuffer.begin());
    }

    //tokenize
    while(index != std::string::npos)
    {
        //push word
        std::string::size_type next_space = mCommandLine.find(' ');
        arguments.push_back(mCommandLine.substr(index, next_space));

        //increment index
        if(next_space != std::string::npos)
        {
            index = next_space +1;

        }
        else
        {
            break;
        }

    }
    //execute
    if(mItemList.empty())
    {
        mCommandLine ="";
        std::cout << "Command database empty" << std::endl;
        return false;
    }
    for(itr = mItemList.begin(); itr != mItemList.end(); ++itr)
    {
        if(itr->name == arguments[0])
        {
            switch(itr->type)
            {
            case CTYPE_UCHAR:
                if(arguments.size() > 2)
                {
                    return true;
                }
                else if(arguments.size() == 1)
                {
                    out.str("");
                    out << (*itr).name << " = " << *((unsigned char *)(*itr).variable_ptr);
                    Print(out.str());

                    return true;
                }
                else if(arguments.size() == 2)
                {
                    *((unsigned char *)(*itr).variable_ptr) = (unsigned char) atoi(arguments[1].c_str());
                    return true;
                }
                break;

            case CTYPE_CHAR:
                if(arguments.size() > 2)
                {
                    return true;
                }
                else if(arguments.size() == 1)
                {
                    out.str("");
                    out << (*itr).name << " = " << *((char *)(*itr).variable_ptr);
                    Print(out.str());
                    return true;
                }
                else if(arguments.size() == 2)
                {
                    *((char *)(*itr).variable_ptr) = (char) atoi(arguments[1].c_str());
                    return true;
                }
                break;

            /*case CTYPE_CHARP:
                if(arguments.size() > 2)
                {
                    return true;
                }
                else if(arguments.size() == 1)
                {

                }
                else if(arguments.size() == 2)
                {

                }
                break;*/

            case CTYPE_UINT:
                if(arguments.size() > 2)
                {
                    return true;
                }
                else if(arguments.size() == 1)
                {
                    out.str("");
                    out << (*itr).name << " = " << *((unsigned int *)(*itr).variable_ptr);
                    Print(out.str());
                    return true;
                }
                else if(arguments.size() == 2)
                {
                    *((unsigned int *)(*itr).variable_ptr) = (unsigned int) atoi(arguments[1].c_str());
                    return true;
                }
                break;

            case CTYPE_INT:
                if(arguments.size() > 2)
                {
                    return true;
                }
                else if(arguments.size() == 1)
                {
                    out.str("");
                    out << (*itr).name << " = " << *((int *)(*itr).variable_ptr);
                    Print(out.str());
                    return true;
                }
                else if(arguments.size() == 2)
                {
                    *((int *)(*itr).variable_ptr) = (int) atoi(arguments[1].c_str());
                    return true;
                }
                break;

            case CTYPE_FLOAT:
                if(arguments.size() > 2)
                {
                    return true;
                }
                else if(arguments.size() == 1)
                {
                    out.str("");
                    out << (*itr).name << " = " << *((float *)(*itr).variable_ptr);
                    Print(out.str());
                    return true;
                }
                else if(arguments.size() == 2)
                {
                    *((float *)(*itr).variable_ptr) = (float) atof(arguments[1].c_str());
                    return true;
                }
                break;

            case CTYPE_STRING:

                if(arguments.size() == 1)
                {
                    out.str("");
                    out << (*itr).name << " = " << (std::string *)(*itr).variable_ptr;
                    Print(out.str());
                    return false;
                }
                else if(arguments.size() > 1)
                {
                    //reset variable
                    *((std::string *)(*itr).variable_ptr) = "";

                    //add new string
                    for(int i=0; i < arguments.size(); ++i)
                    {
                        *((std::string *)(*itr).variable_ptr) += arguments[i];
                    }
                    return true;
                }
                break;

            case CTYPE_FUNCTION:
                (*itr).FN(arguments);
                return true;
                break;

            default:
                std::cout << "Parsed to default command" << std::endl;
                defaultCommand(arguments);
                return false;
                break;

            }
        }
        else
        {
            defaultCommand(arguments);
        }
    }
    mCommandLine ="";
    return true;
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

void GameConsole::SetCommandBufferSize(int size)
{
    mCommandBufferSize = size;

    //remove any extra line
    if(mCommandBuffer.size() > mCommandBufferSize)
    {
        std::vector<std::string>::iterator itr;
        itr = mCommandBuffer.end() - mCommandBufferSize;
        mCommandBuffer.erase(mCommandBuffer.begin(), itr);
    }
}

void GameConsole::ClearCommandBuffer()
{
    mCommandBuffer.clear();
}

void GameConsole::SetTextBufferSize(int size)
{
    mTextBufferSize = size;

    if(mTextBuffer.size() > mTextBufferSize)
    {
        std::list<std::string>::iterator itr = mTextBuffer.end();
        itr = std::next(itr, -mTextBufferSize);

        mTextBuffer.erase(mTextBuffer.begin(), itr);
    }
}

void GameConsole::ClearTextBuffer()
{
    mTextBuffer.clear();
}

void GameConsole::HistoryGo(int where)
{
    mLineIndex += where;

    if(mLineIndex < 0)
    {
        mLineIndex = 0;
    }
    else if(mLineIndex >= mCommandBuffer.size())
    {
        mLineIndex = mCommandBuffer.size() - 1;
    }

    //set command line
    if(!mCommandBuffer.empty())
    {
        mCommandLine = mCommandBuffer[mLineIndex];
    }
}

void GameConsole::SetDefaultCommand(console_function def)
{
    std::cout << "Setting default command" <<std::endl;
    defaultCommand = def;
}


