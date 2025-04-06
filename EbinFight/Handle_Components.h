#pragma once

#include "Component.h"

class Handle_Components
{
public:
	Handle_Components();

	void AddComponent(Component& component);

private:
	void Init();

private:
	std::map<std::string, Component*> m_components;

};

