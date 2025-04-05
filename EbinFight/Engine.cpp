#include "Engine.h"

Engine::Engine(Client& client) : m_client(client)
{
	this->Init();
}

Engine::~Engine()
{
    delete m_window;
}

void Engine::Run()
{
    if (m_window)
    {
        while (m_window->isOpen())
        {
            m_dt = m_clock.restart().asSeconds();

            this->Handle_Events();

            this->Update();

            this->Render();
        }
    }

    this->CloseWindow();
}


void Engine::Init()
{
    std::string winName;
    std::string winStyle;
    std::vector<std::string> lines;
    if (OpenFile(lines, "E:\\EbinFight\\Configs\\Window.txt"))
    {

        try {
            std::string m_winName = lines[0];
            m_winWidth = static_cast<unsigned int>(std::stoi(lines[1]));
            m_winHeight = static_cast<unsigned int>(std::stoi(lines[2]));
            winStyle = lines[3];
        }
        catch (const std::exception& e) {
            std::cerr << "Engine:Error parsing configuration: " << e.what() << std::endl;
            // You c
        }
        std::cout << "Engine:winWidth: " << m_winWidth << "\n";
        std::cout << "Engine:winHeight: " << m_winHeight << "\n";
    }
    if(winStyle == "Titlebar")
        m_window = new sf::RenderWindow(
            sf::VideoMode({ m_winWidth , m_winHeight }),
             winName,
            sf::Style::Titlebar);
    else if(winStyle == "Resize")
        m_window = new sf::RenderWindow(
            sf::VideoMode({ m_winWidth , m_winHeight }),
            winName,
            sf::Style::Resize);
    else if (winStyle == "Default")
        m_window = new sf::RenderWindow(
            sf::VideoMode({ m_winWidth , m_winHeight }),
            winName,
            sf::Style::Default);
    else
        std::cerr << "Engine:Error createing window: " << std::endl;

    m_dt = 0;

    m_state.push(new Game(m_state));
}


void Engine::Handle_Events()
{
    if (m_state.top())
    {
        m_state.top()->Handle_Events();
    }
}

void Engine::Update()
{
    if (m_state.top())
    {
        m_state.top()->Update(m_dt);
    }
}

void Engine::Render()
{
    m_window->clear(sf::Color::Green);

    if (m_state.top())
    {
        m_state.top()->Render(*m_window);
    }
   


    m_window->display();
}

void Engine::CloseWindow()
{
    std::cout << "Engine:Closing window..." << "\n";
    m_window->close();
    m_client.Disconnect();
}
