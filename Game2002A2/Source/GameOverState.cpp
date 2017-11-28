#include <Book/GameOverState.hpp>
#include <Book/Utility.hpp>
#include <Book/Player.hpp>
#include <Book/ResourceHolder.hpp>

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/View.hpp>

bool Winner = false;
float Level = 1;
GameOverState::GameOverState(StateStack& stack, Context context)
: State(stack, context)
, mGameOverText()
, mElapsedTime(sf::Time::Zero)
{
	sf::Font& font = context.fonts->get(Fonts::Main);
	sf::Vector2f windowSize(context.window->getSize());

	mGameOverText.setFont(font);
	if (context.player->getMissionStatus() == Player::MissionFailure)
	{
		mGameOverText.setString("Mission failed!");	
		Winner = false;
	}
	else
	{
		mGameOverText.setString("Mission successful!");
		Winner = true;
	}

	mGameOverText.setCharacterSize(70);
	centerOrigin(mGameOverText);
	mGameOverText.setPosition(0.5f * windowSize.x, 0.4f * windowSize.y);
}

void GameOverState::draw()
{
	sf::RenderWindow& window = *getContext().window;
	window.setView(window.getDefaultView());

	// Create dark, semitransparent background
	sf::RectangleShape backgroundShape;
	backgroundShape.setFillColor(sf::Color(0, 0, 0, 150));
	backgroundShape.setSize(window.getView().getSize());

	window.draw(backgroundShape);
	window.draw(mGameOverText);
}

bool GameOverState::update(sf::Time dt)
{
	// Show state for 3 seconds, after return to menu
	mElapsedTime += dt;
	if (mElapsedTime > sf::seconds(3))
	{
		requestStateClear();

		if (Winner == false)
		{
			mGameOverText.setString("Mission failed!");	
			requestStackPush(States::Menu);
		}
		else if (Level == 1)
		{
			mGameOverText.setString("Mission 1 successful!");
			requestStackPush(States::Game2);
			Level = 2;
		}
		else if (Level == 2)
		{
			mGameOverText.setString("Mission 2 successful!");
			requestStackPush(States::Game3);
			Level = 3;
		}
		else if (Level == 3)
		{
			mGameOverText.setString("Game Complete");
			requestStackPush(States::Menu);
			Level = 1;
		}

		
	}
	return false;
}

bool GameOverState::handleEvent(const sf::Event&)
{
	return false;
}
