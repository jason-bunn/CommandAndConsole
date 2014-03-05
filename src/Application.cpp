#include <Application.hpp>





const sf::Time Application::TimePerFrame = sf::seconds(1.0f/60.0f);

Application::Application()
: mWindow(sf::VideoMode(1024, 768), "In Game Console Test")
, mConsole(mWindow)
{

}

Application::~Application()
{
    //delete mConsole;
}

void Application ::Init()
{
    //mConsole = new GameConsole(mWindow);
}

void Application::Run()
{
    sf::Clock clock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;

    while(mWindow.isOpen())
    {
        sf::Time dt = clock.restart();
        timeSinceLastUpdate += dt;
        while(timeSinceLastUpdate > TimePerFrame)
        {
            timeSinceLastUpdate -= TimePerFrame;

            //process input
            ProcessInput();

            //update logic frames
            Update(TimePerFrame);

        }

        //draw stuff
        Render();
    }
}

void Application::ProcessInput()
{
    sf::Event event;
    while(mWindow.pollEvent(event))
    {
        //close the window if event registered
        if(event.type == sf::Event::Closed)
        {
            mWindow.close();
        }

        if(event.type == sf::Event::KeyPressed)
        {
            if(event.key.code == sf::Keyboard::Tilde)
            {
                //open console window
                if(!mConsole.IsConsoleActive())
                {
                    std::cout<< "Open Console" << std::endl;
                    mConsole.OpenConsole();
                }
                else
                {
                    std::cout<< "Close Console" << std::endl;
                    mConsole.CloseConsole();
                }
            }
        }
        if(event.type == sf::Event::TextEntered)
        {
            std::cout << event.text.unicode << std::endl;
            if(mConsole.IsConsoleActive())
            {
                mConsole.PassKey(static_cast<char>(event.text.unicode));

            }
        }

    }
}

void Application::Update(sf::Time dt)
{
    if(mConsole.IsConsoleActive())
    {
        mConsole.Update();
    }

}

void Application::Render()
{
    mWindow.clear();


    //set the view of the main window
    mWindow.setView(mWindow.getDefaultView());
    mConsole.Render();
    mWindow.display();
}
