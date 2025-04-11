#include "GameObject.h"

GameObject::GameObject(const std::string& texture_filePath, const sf::Vector2f& pos, const sf::Vector2f& scale)	
{
	this->InitTexture(texture_filePath);

	this->Init(pos, scale);
}

GameObject::GameObject(const sf::Sprite& sprite) : p_sprite(new sf::Sprite(sprite))
{
	m_spriteTexure = new sf::Texture(sprite.getTexture());
}

MovementComponent* GameObject::GetMovementComponent()
{
	if (m_movementComponent)
	{
		return m_movementComponent;
	}
	else
	{
		std::cerr << "GameObject:ERROR::MovementComponent is null" << "\n";
		return nullptr;
	}
}

HitBoxComponent* GameObject::GetHitBoxComponent()
{
	
	return p_hitBoxComponent;

}

void GameObject::InitTexture(const std::string& texture_filePath)
{
	m_spriteTexure = new sf::Texture();
	std::string path = "..\\Assets\\" + texture_filePath;
	if (!m_spriteTexure->loadFromFile(path))
	{
		std::cerr << "GameObject:ERROR::CANT_OPEN_FILE: " << texture_filePath << std::endl;
		m_spriteTexure = NULL;
	}
}

void GameObject::Init(const sf::Vector2f& pos, const sf::Vector2f& scale)
{
	if (m_spriteTexure)
		p_sprite = new sf::Sprite(*m_spriteTexure);
	else
		return;

	p_sprite->setPosition(pos);
	p_sprite->setScale(scale);

}

void GameObject::Update(float dt)
{
	if (p_hitBoxComponent)
		p_hitBoxComponent->Update(dt);

	if (m_movementComponent)
	{
		m_movementComponent->Update(dt);
	}
}

void GameObject::Render(sf::RenderWindow& window, const sf::Vector2f& camera)
{
	if (p_sprite)
	{
		// Save original position
		sf::Vector2f originalPos = p_sprite->getPosition();

		if (p_hitBoxComponent)
			p_hitBoxComponent->Render(window);

		// Apply camera offset
		//m_sprite->setPosition(originalPos - camera);
		//std::cout << camera.x << "\n";
		// Draw sprite
		window.draw(*p_sprite);

		// Restore original position
		p_sprite->setPosition(originalPos);
	}

	

}

void GameObject::AddHitBoxComponent(const sf::Vector2f& offset, const sf::Vector2f& size)
{
	if (p_sprite)
		p_hitBoxComponent = new HitBoxComponent(*p_sprite, offset, size);
}

void GameObject::AddMovementComponent(float speed)
{
	if (p_sprite)
		m_movementComponent = new MovementComponent(*p_sprite, speed);
}

GameObject* GameObject::CreateObject(json object_data)
{
	try {


		std::string texture_filePath = object_data["texture"].get<std::string>();
		sf::Vector2f playerPos;
		sf::Vector2f playerScale;
		if (object_data["pos"].is_array())
		{
			playerPos = sf::Vector2f(
				object_data["pos"][0].get<float>()
				, object_data["pos"][1].get<float>());
		}
		if (object_data["scale"].is_array())
		{
			playerScale = sf::Vector2f(
				object_data["scale"][0].get<float>()
				, object_data["scale"][1].get<float>());
		}
		GameObject* newObject = new GameObject(texture_filePath, playerPos, playerScale);
		if (object_data["origin"].get<std::string>() == "center")
		{
			newObject->GetSprite()->setOrigin(newObject->GetSprite()->getLocalBounds().getCenter());
		}
		
		if (object_data["HitBoxComponent"].is_array())
		{
			if (object_data["HitBoxComponent"][0].get<bool>())
			{
				sf::Vector2f hitboxOffset;
				sf::Vector2f hitboxSize;
				if (object_data["HitBoxComponent"][1].is_array())
				{
					hitboxOffset = sf::Vector2f(
						object_data["HitBoxComponent"][1][0].get<float>()
						, object_data["HitBoxComponent"][1][1].get<float>());
				}
				if (object_data["HitBoxComponent"][2].is_array())
				{
					hitboxSize = sf::Vector2f(
						object_data["HitBoxComponent"][2][0].get<float>()
						, object_data["HitBoxComponent"][2][1].get<float>());
				}

				newObject->AddHitBoxComponent(hitboxOffset, hitboxSize);
			}

		}
		if (object_data["MovementComponent"].is_array())
		{
			if (object_data["MovementComponent"][0].get<bool>())
			{
				float speed = object_data["MovementComponent"][1].get<float>();

				newObject->AddMovementComponent(speed);
			}

		}
		return newObject;
	}
	catch (const std::exception& e) {
		std::cerr << "GameObject:Error creating object: " << e.what() << std::endl;
		return nullptr;
	}

	return nullptr;
}