#include "Engine.h"

Engine::Engine(Client& client) : m_client(client)
{
	this->Init();
}

Engine::~Engine()
{
    delete m_window;
    while(!m_state.empty())
    { 
        delete m_state.top();
        m_state.pop();
    }
  
}

void Engine::Run()
{
    if (m_window)
    {
        while (m_window->isOpen())
        {
            m_dt = m_clock.restart().asMilliseconds();

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
    std::string handleControlsFilePath;
    std::vector<std::string> lines;
    if (OpenFile(lines, "..\\Configs\\Window.txt"))
    {

        try {
            std::string m_winName = lines[0];
            m_winWidth = static_cast<unsigned int>(std::stoi(lines[1]));
            m_winHeight = static_cast<unsigned int>(std::stoi(lines[2]));
            winStyle = lines[3];
            handleControlsFilePath = lines[4];
        }
        catch (const std::exception& e) {
            std::cerr << "Engine:Error parsing configuration: " << e.what() << std::endl;
            // You c
        }
        std::cout << "Engine:winWidth: " << m_winWidth << "\n";
        std::cout << "Engine:winHeight: " << m_winHeight << "\n";
        Global::win_width = m_winWidth;
        Global::win_height = m_winHeight;
    }
    else
        return;
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
    else if (winStyle == "Close")
        m_window = new sf::RenderWindow(
            sf::VideoMode({ m_winWidth , m_winHeight }),
            winName,
            sf::Style::Close);
    else
        std::cerr << "Engine:Error createing window: " << std::endl;

    m_dt = 0;

    m_handle_controls = new Handle_Controls(handleControlsFilePath);

    m_state.push(new HomePage(m_client, m_state));
}


void Engine::Handle_Events()
{

    while (const std::optional event = m_window->pollEvent())
    {
      
        if (event->is<sf::Event::Closed>())
            this->CloseWindow();

        auto keyEvent = event->getIf<sf::Event::KeyPressed>();
        if(keyEvent)
        { 
            if (keyEvent->code == m_handle_controls->GetControls("CloseWindow"))
                this->CloseWindow();


        }
       

        if (m_state.top())
        {
            m_state.top()->Handle_Events(*event, *m_handle_controls, m_dt);
        }
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
    m_window->clear(sf::Color::Red);

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
