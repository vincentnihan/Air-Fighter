#include <Book/Player.hpp>
#include <Book/CommandQueue.hpp>
#include <Book/Aircraft.hpp>
#include <Book/Foreach.hpp>

#include <SFML\Window\VideoMode.hpp>

#include <iostream>

#include <map>
#include <string>
#include <algorithm>

using namespace std::placeholders;

extern bool mouseCtrlEnabled;
int mouseX = 1;
int mouseY = 1;


struct AircraftMover
{
	AircraftMover(float vx, float vy)
	: velocity(vx, vy)
	{
	}

	void operator() (Aircraft& aircraft, sf::Time) const
	{
		aircraft.accelerate(velocity * aircraft.getMaxSpeed());
	}

	sf::Vector2f velocity;
};

Player::Player()
: mCurrentMissionStatus(MissionRunning)
{
	// Set initial key bindings
	mKeyBinding[sf::Keyboard::Left] = MoveLeft;
	mKeyBinding[sf::Keyboard::Right] = MoveRight;
	mKeyBinding[sf::Keyboard::Up] = MoveUp;
	mKeyBinding[sf::Keyboard::Down] = MoveDown;
	mKeyBinding[sf::Keyboard::Space] = Fire;
	mKeyBinding[sf::Keyboard::M] = LaunchMissile;
 	mKeyBinding[sf::Keyboard::N] = LaunchLaser;

	
	joystickLaunch = false;
	joystickLaunch2 = false;
	//mouseEnabled = false;


	// Set initial action bindings
	initializeActions();	

	// Assign all categories to player's aircraft
	FOREACH(auto& pair, mActionBinding)
		pair.second.category = Category::PlayerAircraft;
}

void Player::handleEvent(const sf::Event& event, CommandQueue& commands)
{
	if (event.type == sf::Event::KeyPressed)
	{
		// Check if pressed key appears in key binding, trigger command if so
		auto found = mKeyBinding.find(event.key.code);
		if (found != mKeyBinding.end() && !isRealtimeAction(found->second))
			commands.push(mActionBinding[found->second]);
	}
	/*
	if (commands.mouseControlOn)
	{
		std::cout<<" Mouse control is on" << std::endl;
	}else
	{
		std::cout<<" Mouse control is OFF" << std::endl;
	}
	*/


	if (event.type == sf::Event::JoystickMoved)
	{
		if (sf::Joystick::getAxisPosition(0, sf::Joystick::X) < -40)
		{
			mouseX = 0;
		}else if ((sf::Joystick::getAxisPosition(0, sf::Joystick::X) > 40))
		{
			mouseX = 2;
		}else
		{
			mouseX = 1;
		}



		if (sf::Joystick::getAxisPosition(0, sf::Joystick::Y) < -40)
		{
			mouseY = 0;
		}else if ((sf::Joystick::getAxisPosition(0, sf::Joystick::Y) > 40))
		{
			mouseY = 2;
		}else
		{
			mouseY = 1;
		}


	}



	if (event.type == sf::Event::MouseMoved && mouseCtrlEnabled == true)
	{

	

	if (event.mouseMove.x < 341)
	{
		mouseX = 0;
	} else if (event.mouseMove.x > 683)
	{
		mouseX = 2;
	} else
	{
		mouseX = 1;
	}

	if (event.mouseMove.y < 256)
	{
		mouseY = 0;
	}else if (event.mouseMove.y > 512)
	{
		mouseY = 2;
	}else
	{
		mouseY = 1;
	}

	}



	if (joystickLaunch == true && sf::Joystick::isButtonPressed(0, 2) == false)
	{
		commands.push(mActionBinding[LaunchMissile]);
	}else
	if (joystickLaunch2 == true && sf::Joystick::isButtonPressed(0, 3) == false)
	{
		commands.push(mActionBinding[LaunchLaser]);
	}
	
	joystickLaunch = sf::Joystick::isButtonPressed(0, 2);
	joystickLaunch2 = sf::Joystick::isButtonPressed(0, 3);

	if (event.type == sf::Event::MouseButtonPressed)
{
    if (event.mouseButton.button == sf::Mouse::Right)
    {
		commands.push(mActionBinding[LaunchMissile]);
	}

	}

	
	

	

}

void Player::handleRealtimeInput(CommandQueue& commands)
{
	// Traverse all assigned keys and check if they are pressed
	FOREACH(auto pair, mKeyBinding)
	{
		// If key is pressed, lookup action and trigger corresponding command
		if (sf::Keyboard::isKeyPressed(pair.first) && isRealtimeAction(pair.second))
			commands.push(mActionBinding[pair.second]);
	}




	/*
	if (true)
	{
		
	

		
		if (sf::Mouse::getPosition().x > sf::VideoMode::getDesktopMode().width * 3.0f / 5.0f)
		{
			commands.push(mActionBinding[MoveRight]);

		}else if (sf::Mouse::getPosition().x < sf::VideoMode::getDesktopMode().width * 2.0f / 5.0f)
		{
			commands.push(mActionBinding[MoveLeft]);
		}
		

		if (sf::Mouse::getPosition().y > sf::VideoMode::getDesktopMode().height * 3.0f / 5.0f)
		{
			commands.push(mActionBinding[MoveDown]);
		}else if (sf::Mouse::getPosition().y < sf::VideoMode::getDesktopMode().height * 2.0f / 5.0f)
		{
			commands.push(mActionBinding[MoveUp]);
		}

		*/



	if (mouseX == 0)
	{
		commands.push(mActionBinding[MoveLeft]);
	}else if (mouseX == 2)
	{
		commands.push(mActionBinding[MoveRight]);
	}


	if (mouseY == 0)
	{
		commands.push(mActionBinding[MoveUp]);
	}else if (mouseY == 2)
	{
		commands.push(mActionBinding[MoveDown]);
	}

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			commands.push(mActionBinding[Fire]);
		}

	if (sf::Joystick::isButtonPressed(0, 1))
	{
		commands.push(mActionBinding[Fire]);
	}




	//}
}

void Player::assignKey(Action action, sf::Keyboard::Key key)
{
	// Remove all keys that already map to action
	for (auto itr = mKeyBinding.begin(); itr != mKeyBinding.end(); )
	{
		if (itr->second == action)
			mKeyBinding.erase(itr++);
		else
			++itr;
	}

	// Insert new binding
	mKeyBinding[key] = action;
}

sf::Keyboard::Key Player::getAssignedKey(Action action) const
{
	FOREACH(auto pair, mKeyBinding)
	{
		if (pair.second == action)
			return pair.first;
	}

	return sf::Keyboard::Unknown;
}

void Player::setMissionStatus(MissionStatus status)
{
	mCurrentMissionStatus = status;
}

Player::MissionStatus Player::getMissionStatus() const
{
	return mCurrentMissionStatus;
}

void Player::initializeActions()
{
	mActionBinding[MoveLeft].action      = derivedAction<Aircraft>(AircraftMover(-1,  0));
	mActionBinding[MoveRight].action     = derivedAction<Aircraft>(AircraftMover(+1,  0));
	mActionBinding[MoveUp].action        = derivedAction<Aircraft>(AircraftMover( 0, -1));
	mActionBinding[MoveDown].action      = derivedAction<Aircraft>(AircraftMover( 0, +1));
	mActionBinding[Fire].action          = derivedAction<Aircraft>([] (Aircraft& a, sf::Time) { a.fire(); });
	mActionBinding[LaunchMissile].action = derivedAction<Aircraft>([] (Aircraft& a, sf::Time) { a.launchMissile(); });
	mActionBinding[LaunchLaser].action = derivedAction<Aircraft>([] (Aircraft& a, sf::Time) { a.launchLaser(); });
}

bool Player::isRealtimeAction(Action action)
{
	switch (action)
	{
		case MoveLeft:
		case MoveRight:
		case MoveDown:
		case MoveUp:
		case Fire:
			return true;

		default:
			return false;
	}
}
