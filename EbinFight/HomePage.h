#pragma once
#include "State.h"
#include "InputField.h"
#include "Button.h"

class HomePage :
    public State
{
public:
	HomePage(Client& client, std::stack<State*>& currentState);
	~HomePage() = default;
	void Handle_Events(const sf::Event& event, Handle_Controls& m_handle_controls, float dt) override;
	void Update(float dt) override;
	void SavePlayer();
	void Render(sf::RenderWindow& window) override;
	void OnExitState() override;
private:
	void Init();
private:
	sf::Sprite* bg;
	sf::Texture bgTexture;
	std::vector<InputField> inputFields;
	Button* saveButton;
	int currentFocusIndex = 0;

	sf::Texture texture;
};

