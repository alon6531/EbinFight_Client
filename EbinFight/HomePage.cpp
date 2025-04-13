#include "HomePage.h"
#include "Game.h"

HomePage::HomePage(Client& client, std::stack<State*>& currentState)
	: State(client, currentState)
{
	std::cout << "HomePage:HomePage State Opened" << "\n";
	this->Init();
}

void HomePage::Init()
{

	if (!texture.loadFromFile("..\\Assets\\HomePage\\bg.png")) {
		std::cerr << "HomePage:ERROR::CANT_OPEN_FILE: background.png" << std::endl;
		return;
	}
	// Set the background sprite
	bg = new sf::Sprite(texture);
	bg->setPosition(sf::Vector2f(0, 0));
	//bg->setScale(Global::win_width / bg->getGlobalBounds().width, Global::win_height / bg->getGlobalBounds().height);
	// Initialize input fields
	
    inputFields.emplace_back(sf::Vector2f(300, 100), sf::Vector2f(500, 100));  // Name
    inputFields.emplace_back(sf::Vector2f(1300, 100), sf::Vector2f(500, 100));  // Texture path
    inputFields.emplace_back(sf::Vector2f(250, 270), sf::Vector2f(300, 100)); // Pos X
    inputFields.emplace_back(sf::Vector2f(750, 270), sf::Vector2f(150, 100)); // Pos Y
    inputFields.emplace_back(sf::Vector2f(1150, 270), sf::Vector2f(150, 100)); // Scale X
    inputFields.emplace_back(sf::Vector2f(1600, 270), sf::Vector2f(150, 100)); // Scale Y
	inputFields.emplace_back(sf::Vector2f(340, 480), sf::Vector2f(200, 100)); // hitbox 
	inputFields.emplace_back(sf::Vector2f(905, 400), sf::Vector2f(200, 100)); // hitbox offsetX
	inputFields.emplace_back(sf::Vector2f(905, 540), sf::Vector2f(200, 100)); // hitbox offsetY
	inputFields.emplace_back(sf::Vector2f(1489, 400), sf::Vector2f(200, 100)); // hitbox sizeX
	inputFields.emplace_back(sf::Vector2f(1489, 540), sf::Vector2f(200, 100)); // hitbox sizeY
	inputFields.emplace_back(sf::Vector2f(394, 720), sf::Vector2f(200, 100)); // movement
	inputFields.emplace_back(sf::Vector2f(1054, 720), sf::Vector2f(200, 100)); // speed


    inputFields[0].setFocus(true);

	saveButton = new Button(Global::win_width / 2, Global::win_height - 110, 150, 100, "Save", sf::Color::Blue);
}


void HomePage::Handle_Events(const sf::Event& event, Handle_Controls& m_handle_controls, float dt)
{
    for (auto& field : inputFields)
        field.handleEvent(event);


    auto keyPressed = event.getIf<sf::Event::KeyPressed>();
    if (keyPressed && keyPressed->code == sf::Keyboard::Key::Tab) {
        inputFields[currentFocusIndex].setFocus(false);
        currentFocusIndex = (currentFocusIndex + 1) % inputFields.size();
        inputFields[currentFocusIndex].setFocus(true);
    }

    auto mousePressed = event.getIf<sf::Event::MouseButtonPressed>();
    if (mousePressed) {
        // Apply inputs to sprite
		if (saveButton && mousePressed->button == sf::Mouse::Button::Left && saveButton->IsPressed(p_mousePos))
		{
            SavePlayer();
			OnExitState();
			return;
		}
		for (int i = 0; i < inputFields.size(); i++)
		{
			if (mousePressed->button == sf::Mouse::Button::Left && inputFields[i].IsPressed(p_mousePos))
			{
				inputFields[i].setFocus(true);
				
			}
			else
			{
				inputFields[i].setFocus(false);
			}
		}
	}
}

void HomePage::Update(float dt)
{
}

void HomePage::SavePlayer()
{
    std::string name = inputFields[0].getContent();
	p_client.InitUser(name);
    std::string texPath = inputFields[1].getContent();
	std::string posX = inputFields[2].getContent();
	std::string posY = inputFields[3].getContent();
	std::string scaleX = inputFields[4].getContent();
	std::string scaleY = inputFields[5].getContent();
	std::string hitbox = inputFields[6].getContent();
	std::string hitboxOffsetX = inputFields[7].getContent();
	std::string hitboxOffsetY = inputFields[8].getContent();
	std::string hitboxSizeX = inputFields[9].getContent();
	std::string hitboxSizeY = inputFields[10].getContent();
	std::string movement = inputFields[11].getContent();
	std::string speed = inputFields[12].getContent();
	// Convert strings to appropriate types
	try {
		json playerData = {
		{"texture", texPath},
		{"pos", {std::stof(posX), std::stof(posY)}},
		{"scale", {std::stof(scaleX), std::stof(scaleY)}},
		{"origin", "center"},
		{"HitBoxComponent", {hitbox == "true", {std::stof(hitboxOffsetX), std::stof(hitboxOffsetY)}, {std::stoi(hitboxSizeX), std::stoi(hitboxSizeY)}}},
		{"MovementComponent", {movement == "true", std::stof(speed)}}
		};
		p_client.InitPlayer(playerData);
		
	}
	catch (const std::exception& e) {
		std::cerr << "HomePage:Error parsing input: " << e.what() << std::endl;
	}
	try {
		
		json playerData1 = {
		{"texture", "a.png"},
 		{"pos", {600.f, 400.f}},
 		{"scale", {3, 3}},
 		{"origin", "center"},
 		{"HitBoxComponent", {true, {0.f, 0.f}, {0, 0}}},
 		{"MovementComponent", {true, 20}},
		{"AnimationComponent",
			{
			true, 200, "idle", {
					{{0,0},{16,32}},
					{{16,0},{16,32}},
					{{32,0},{16,32}},
					{{48,0},{16,32}},
					}
			}},
		};

		p_client.InitPlayer(playerData1);
		
	}
	catch (const std::exception& e) {
		std::cerr << "HomePage:Error parsing input: " << e.what() << std::endl;
		return;
	}
	
	

	// Save player data

	
  
   
	std::cout << "Name: " << name << "\n";
  
}

void HomePage::Render(sf::RenderWindow& window)
{
	UpdateMousePosition(window);
	window.draw(*bg);
	

    for (auto& field : inputFields)
        field.render(window);

	if (saveButton)
	    saveButton->Render(window);



}

void HomePage::OnExitState()
{
	std::this_thread::sleep_for(std::chrono::seconds(2));
	p_currentState.push(new Game(p_client, p_currentState));
}

