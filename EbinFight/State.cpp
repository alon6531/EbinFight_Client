#include "State.h"

State::State(std::stack<State*>& currentState) : m_currentState(currentState)
{
}
