#include <Book/GameState2.hpp>
#include <Book/MusicPlayer.hpp>
#include <Book/Utility.hpp>

#include <SFML/Graphics/RenderWindow.hpp>

GameState2::GameState2(StateStack& stack, Context context)
: State(stack, context)
, mWorld(*context.window, *context.fonts, *context.sounds)
, mPlayer(*context.player)
, mGame2Text()
{
	sf::Font& font = context.fonts->get(Fonts::Main);
	sf::Vector2f windowSize(context.window->getSize());

	mPlayer.setMissionStatus(Player::MissionRunning);

	// Play game theme
	context.music->play(Music::MissionTheme);

	mGame2Text.setFont(font);
	if (context.player->getMissionStatus() == Player::MissionRunning)
	{
		mGame2Text.setString("Mission Two");	
	}

	mGame2Text.setCharacterSize(70);
	centerOrigin(mGame2Text);
	mGame2Text.setPosition(0.5f * windowSize.x, 0.05 * windowSize.y);
}

void GameState2::draw()
{
	sf::RenderWindow& window = *getContext().window;
	window.setView(window.getDefaultView());
	mWorld.draw();
	window.draw(mGame2Text);
}

bool GameState2::update(sf::Time dt)
{
	mWorld.update(dt);

	if (!mWorld.hasAlivePlayer())
	{
		mPlayer.setMissionStatus(Player::MissionFailure);
		requestStackPush(States::GameOver);
	}
	else if (mWorld.hasPlayerReachedEnd())
	{
		mPlayer.setMissionStatus(Player::MissionSuccess);
		requestStackPush(States::GameOver);
	}

	CommandQueue& commands = mWorld.getCommandQueue();
	mPlayer.handleRealtimeInput(commands);

	return true;
}

bool GameState2::handleEvent(const sf::Event& event)
{
	// Game input handling
	CommandQueue& commands = mWorld.getCommandQueue();
	mPlayer.handleEvent(event, commands);

	// Escape pressed, trigger the pause screen
	if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
		requestStackPush(States::Pause);

	return true;
}