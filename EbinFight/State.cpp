#include "State.h"

State::State(Client& client, std::stack<State*>& currentState) : p_client(client), p_currentState(currentState)
{
}
