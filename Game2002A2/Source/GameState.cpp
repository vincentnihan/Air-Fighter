#include <Book/GameState.hpp>
#include <Book/MusicPlayer.hpp>
#include <Book/Utility.hpp>

#include <SFML/Graphics/RenderWindow.hpp>

GameState::GameState(StateStack& stack, Context context)
: State(stack, context)
, mWorld(*context.window, *context.fonts, *context.sounds)
, mPlayer(*context.player)
, mGameText()
{
	sf::Font& font = context.fonts->get(Fonts::Main);
	sf::Vector2f windowSize(context.window->getSize());

	mPlayer.setMissionStatus(Player::MissionRunning);
	
	
	mPlayer.mouseEnabled = false;
	// Play game theme
	context.music->play(Music::MissionTheme);

	mGameText.setFont(font);
	if (context.player->getMissionStatus() == Player::MissionRunning)
	{
		mGameText.setString("Mission One");	
	}

	mGameText.setCharacterSize(70);
	centerOrigin(mGameText);
	mGameText.setPosition(0.5f * windowSize.x, 0.05 *windowSize.y);
}


GameState::GameState(StateStack& stack, Context context, bool mouseCTRL)
: State(stack, context)
, mWorld(*context.window, *context.fonts, *context.sounds)
, mPlayer(*context.player)
, mGameText()
{
	sf::Font& font = context.fonts->get(Fonts::Main);
	sf::Vector2f windowSize(context.window->getSize());

	mPlayer.setMissionStatus(Player::MissionRunning);
	
	
	mPlayer.mouseEnabled = mouseCTRL;
	// Play game theme
	context.music->play(Music::MissionTheme);

	mGameText.setFont(font);
	if (context.player->getMissionStatus() == Player::MissionRunning)
	{
		mGameText.setString("Mission One");	
	}

	mGameText.setCharacterSize(70);
	centerOrigin(mGameText);
	mGameText.setPosition(0.5f * windowSize.x, 0.05 *windowSize.y);
}

void GameState::draw()
{
	sf::RenderWindow& window = *getContext().window;
	window.setView(window.getDefaultView());
	mWorld.draw();
	window.draw(mGameText);
}

bool GameState::update(sf::Time dt)
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

bool GameState::handleEvent(const sf::Event& event)
{
	// Game input handling
	CommandQueue& commands = mWorld.getCommandQueue();
	mPlayer.handleEvent(event, commands);

	// Escape pressed, trigger the pause screen
	if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
		requestStackPush(States::Pause);

	return true;
}