#include <Book/Container.hpp>
#include <Book/Foreach.hpp>

#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>


namespace GUI
{

Container::Container()
: mChildren()
, mSelectedChild(-1)
{
	joystickY = 1;
}

void Container::pack(Component::Ptr component)
{
	mChildren.push_back(component);

	if (!hasSelection() && component->isSelectable())
		select(mChildren.size() - 1);
}

bool Container::isSelectable() const
{
    return false;
}

void Container::handleEvent(const sf::Event& event)
{
    
	if (event.mouseButton.button == sf::Mouse::Left){
		/*
		std::cout << "Left mouse is clicked. Mouse pos : " 
			<< sf::Mouse::getPosition().x <<" " << sf::Mouse::getPosition().x  
			<< std::endl;
			*/
		//std::cout << event.mouseButton.x << " " << event.mouseButton.y << std::endl;


	 }

	

	if (event.type == sf::Event::JoystickMoved)
	{
		if (sf::Joystick::getAxisPosition(0, sf::Joystick::Y) < -40 && joystickY != 4)
		{
			joystickY = 0;
		}else if ((sf::Joystick::getAxisPosition(0, sf::Joystick::Y) > 40) && joystickY != 4)
		{
			joystickY = 2;
		}else if(sf::Joystick::getAxisPosition(0, sf::Joystick::Y) < 40 && sf::Joystick::getAxisPosition(0, sf::Joystick::Y) > -40)
		{
			joystickY = 1;
		}
	}

	if (joystickY == 0)
	{
		selectPrevious();
		joystickY = 4;
	}else if (joystickY == 2)
	{
		selectNext();
		joystickY = 4;
	}

	if (sf::Joystick::isButtonPressed(0, 2) == true)
	{
		if (hasSelection())
		mChildren[mSelectedChild]->activate();
	}

	
	if (event.mouseMove.x < 301 && event.mouseMove.x > 99 && event.mouseMove.y > 299 && event.mouseMove.y < 501)
	{
		if (event.mouseMove.y < 351)
		{
			if (!hasSelection())
		return;

	// Search previous component that is selectable, wrap around if necessary
	int prev = mSelectedChild;
	

	// Select that component
	select(0);
		} else if (event.mouseMove.y < 401)
		{
			if (!hasSelection())
		return;

	// Search previous component that is selectable, wrap around if necessary
	int prev = mSelectedChild;
	

	// Select that component
	select(1);
		}else if (event.mouseMove.y < 451)
		{
			if (!hasSelection())
		return;

	// Search previous component that is selectable, wrap around if necessary
	int prev = mSelectedChild;
	

	// Select that component
	select(2);
		}else if (event.mouseMove.y < 501)
		{
			if (!hasSelection())
		return;

	// Search previous component that is selectable, wrap around if necessary
	int prev = mSelectedChild;
	

	// Select that component
	select(3);
		} else if (event.mouseMove.y < 551)
		{
			if (!hasSelection())
		return;

	// Search previous component that is selectable, wrap around if necessary
	int prev = mSelectedChild;
	

	// Select that component
	select(4);
		}else if (event.mouseMove.y < 601)
		{
			if (!hasSelection())
		return;

	// Search previous component that is selectable, wrap around if necessary
	int prev = mSelectedChild;
	

	// Select that component
	select(5);
		}

	}

	if (event.mouseButton.x < 301 && event.mouseButton.x > 99 && event.mouseButton.y > 299 && event.mouseButton.y < 501)
	{
		if (hasSelection())
		mChildren[mSelectedChild]->activate();
	}


    // If we have selected a child then give it events
	if (hasSelection() && mChildren[mSelectedChild]->isActive())
	{
		mChildren[mSelectedChild]->handleEvent(event);
	}
	else if (event.type == sf::Event::KeyReleased)
	{
		if (event.key.code == sf::Keyboard::W || event.key.code == sf::Keyboard::Up)
		{
			selectPrevious();
		}
		else if (event.key.code == sf::Keyboard::S || event.key.code == sf::Keyboard::Down)
		{
			selectNext();
		}
		else if (event.key.code == sf::Keyboard::Return || event.key.code == sf::Keyboard::Space)
		{
			if (hasSelection())
				mChildren[mSelectedChild]->activate();
		} else if (event.key.code == sf::Keyboard::Num0 )
		{
			select(0);
		}else if (event.key.code == sf::Keyboard::Num1 )
		{
			select(1);
		}else if (event.key.code == sf::Keyboard::Num2 )
		{
			select(2);
		}else if (event.key.code == sf::Keyboard::Num3 )
		{
			select(3);
		}else if (event.key.code == sf::Keyboard::Num4 )
		{
			select(4);
		}else if (event.key.code == sf::Keyboard::Num5 )
		{
			select(5);
		}else if (event.key.code == sf::Keyboard::Num6 )
		{
			select(6);
		}else if (event.key.code == sf::Keyboard::Num7 )
		{
			select(7);
		}else if (event.key.code == sf::Keyboard::Num8 )
		{
			select(8);
		}else if (event.key.code == sf::Keyboard::Num9 )
		{
			select(9);
		}
	}
}

void Container::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();

	FOREACH(const Component::Ptr& child, mChildren)
		target.draw(*child, states);
}

bool Container::hasSelection() const
{
	return mSelectedChild >= 0;
}

void Container::select(std::size_t index)
{
	if (mChildren[index]->isSelectable())
	{
		if (hasSelection())
			mChildren[mSelectedChild]->deselect();

		mChildren[index]->select();
		mSelectedChild = index;
	}
}

void Container::selectNext()
{
	if (!hasSelection())
		return;

	// Search next component that is selectable, wrap around if necessary
	int next = mSelectedChild;
	do
		next = (next + 1) % mChildren.size();
	while (!mChildren[next]->isSelectable());

	// Select that component
	select(next);
}

void Container::selectPrevious()
{
	if (!hasSelection())
		return;

	// Search previous component that is selectable, wrap around if necessary
	int prev = mSelectedChild;
	do
		prev = (prev + mChildren.size() - 1) % mChildren.size();
	while (!mChildren[prev]->isSelectable());

	// Select that component
	select(prev);
}

}
