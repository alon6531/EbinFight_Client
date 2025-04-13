#include "GameObject.h"

GameObject::GameObject(const std::string& texture_filePath, const sf::Vector2f& pos, const sf::Vector2f& scale)	
{

	this->InitTexture(texture_filePath);
	this->Init(pos, scale);
}

GameObject::GameObject(const json& object_data)
{
	try {


		std::string texture_filePath = object_data["texture"].get<std::string>();
		this->InitTexture(texture_filePath);
	
		sf::Vector2f objectPos;
		sf::Vector2f objectScale;
		if (object_data.contains("pos") && object_data["pos"].is_array())
		{
			objectPos = sf::Vector2f(
				object_data["pos"][0].get<float>()
				, object_data["pos"][1].get<float>());
		}
		if (object_data.contains("scale") && object_data["scale"].is_array())
		{
			objectScale = sf::Vector2f(
				object_data["scale"][0].get<float>()
				, object_data["scale"][1].get<float>());
		}
		this->Init(objectPos, objectScale);
		if (object_data.contains("HitBoxComponent") && object_data["HitBoxComponent"].is_array())
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

				this->AddHitBoxComponent(hitboxOffset, hitboxSize);
			}

		}
		if (object_data.contains("MovementComponent") && object_data["MovementComponent"].is_array())
		{
			if (object_data["MovementComponent"][0].get<bool>())
			{
				float speed = object_data["MovementComponent"][1].get<float>();

				this->AddMovementComponent(speed);
			}

		}
		if (object_data.contains("AnimationComponent") && object_data["AnimationComponent"].is_array())
		{

			if (object_data["AnimationComponent"][0].get<bool>())
			{
				this->AddAnimationComponent();

				float frameTime = object_data["AnimationComponent"][1].get<float>();
				std::string frameName = object_data["AnimationComponent"][2].get<std::string>();
				p_animationComponent->Push(frameName, frameTime);
				if (object_data["AnimationComponent"][3].is_array())
				{
					
					auto& frames = object_data["AnimationComponent"][3];
					for (auto frame : frames)
					{
						sf::IntRect frameRect(
							sf::Vector2i(frame[0][0].get<int>(), frame[0][1].get<int>()),
							sf::Vector2i(frame[1][0].get<int>(), frame[1][1].get<int>()));
						//newObject.GetAnimationComponent()->AddFrame(frameRect);
						
						p_animationComponent->AddFrame(frameRect);
					}
				}
			}
		}
	}
	catch (const std::exception& e) {
		std::cerr << "GameObject:Error creating object: " << e.what() << std::endl;
	}
}

GameObject::~GameObject()
{
	std::cout << "dis colled\n";
	if (m_spriteTexure)
	{
		delete m_spriteTexure;
	}
	if (p_sprite)
	{
		delete p_sprite;
	}
	if (p_movementComponent)
	{
		delete p_movementComponent;
	}
	if (p_hitBoxComponent)
	{
		delete p_hitBoxComponent;
	}
	if (p_animationComponent)
	{
		delete p_animationComponent;
	}
}

MovementComponent* GameObject::GetMovementComponent()
{
	if (p_movementComponent)
	{
		return p_movementComponent;
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

AnimationComponent* GameObject::GetAnimationComponent()
{
	return p_animationComponent;
}

void GameObject::InitTexture(const std::string& texture_filePath)
{
	m_spriteTexure = new sf::Texture();
	std::string path = "..\\Assets\\" + texture_filePath;
	if (!m_spriteTexure->loadFromFile(path))
	{
		std::cerr << "GameObject:ERROR::CANT_OPEN_FILE: " << texture_filePath << std::endl;
		delete m_spriteTexure;
		m_spriteTexure = nullptr;
	}
	//std::cout << "GameObject:OPEN_FILE: " << texture_filePath << std::endl;
}

void GameObject::Init(const sf::Vector2f& pos, const sf::Vector2f& scale)
{

	
	if (m_spriteTexure && !p_sprite)
		p_sprite = new sf::Sprite(*m_spriteTexure);
	else
		return;

	p_sprite->setPosition(pos);
	p_sprite->setScale(scale);
	p_sprite->setOrigin(p_sprite->getLocalBounds().getCenter());
}

void GameObject::Update(float dt)
{
	if (p_hitBoxComponent)
		p_hitBoxComponent->Update(dt);

	if (p_movementComponent)
	{
		p_movementComponent->Update(dt);
	}
	if (p_animationComponent)
	{
		p_animationComponent->Update(dt);
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
		p_movementComponent = new MovementComponent(*p_sprite, speed);
}

void GameObject::AddAnimationComponent()
{
	if (p_sprite)
		p_animationComponent = new AnimationComponent(*p_sprite);
}

void GameObject::UpdateObjectData(json object_data)
{
	
	try {
		

		
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
		p_sprite->setPosition(playerPos);
		p_sprite->setScale(playerScale);
	
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

				p_hitBoxComponent->UpdateCompData(hitboxOffset, hitboxSize);
			}

		}
		if (object_data["MovementComponent"].is_array())
		{
			if (object_data["MovementComponent"][0].get<bool>())
			{
				float speed = object_data["MovementComponent"][1].get<float>();

				p_movementComponent->UpdateCompData(speed);
			}

		}
		if (object_data["AnimationComponent"].is_array())
		{

			if (object_data["AnimationComponent"][0].get<bool>())
			{
				
				float frameTime = object_data["AnimationComponent"][1].get<float>();
				std::string frameName = object_data["AnimationComponent"][2].get<std::string>();
				if (frameName != p_animationComponent->Top().getAnimName())
					p_animationComponent->Pop();
				p_animationComponent->Push(frameName, frameTime);

				if (object_data["AnimationComponent"][3].is_array())
				{

					auto& frames = object_data["AnimationComponent"][3];
					std::cout << frames[0][0][1] << "\n";
					for (auto frame : frames)
					{
						
						sf::IntRect frameRect(
							sf::Vector2i(frame[0][0].get<int>(), frame[0][1].get<int>()),
							sf::Vector2i(frame[1][0].get<int>(), frame[1][1].get<int>()));
						//newObject.GetAnimationComponent()->AddFrame(frameRect);

						p_animationComponent->AddFrame(frameRect);
					}

				}
			}
		}
		
	}
	catch (const std::exception& e) {
		std::cerr << "GameObject:Error creating object: " << e.what() << std::endl;
	}
	
}
