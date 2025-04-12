#include "State.h"

State::State(Client& client, std::stack<State*>& currentState) : p_client(client), p_currentState(currentState)
{
}

void State::UpdateMousePosition(sf::RenderWindow& window)
{
	p_mousePos = sf::Mouse::getPosition(window);
	//std::cout << p_mousePos.x << " " << p_mousePos.y << "\n";
}
