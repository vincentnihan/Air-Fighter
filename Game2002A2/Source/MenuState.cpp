#include <Book/MenuState.hpp>
#include <Book/Button.hpp>
#include <Book/Utility.hpp>
#include <Book/MusicPlayer.hpp>
#include <Book/ResourceHolder.hpp>

#include <Book\CommandQueue.hpp>
#include <Book\GameState.hpp>
#include <Book\Application.hpp>
#include <Book\State.hpp>
#include <Book\StateStack.hpp>


#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/View.hpp>

extern bool mouseCtrlEnabled;


MenuState::MenuState(StateStack& stack, Context context)
: State(stack, context)
, mGUIContainer()
{
	sf::Texture& texture = context.textures->get(Textures::TitleScreen);
	mBackgroundSprite.setTexture(texture);
	

	auto playMouseButton = std::make_shared<GUI::Button>(context);
	playMouseButton->setPosition(100,300);
	playMouseButton->setText("Play w/ Mouse");
	playMouseButton->setCallback([this] ()
	{
				mouseCtrlEnabled = true;

		requestStackPop();
		requestStackPush(States::Game);
		
	});

	
	auto playButton = std::make_shared<GUI::Button>(context);
	playButton->setPosition(100, 350);
	playButton->setText("Play");
	playButton->setCallback([this] ()
	{
		mouseCtrlEnabled = false;
		requestStackPop();
		requestStackPush(States::Game);
	});

	auto settingsButton = std::make_shared<GUI::Button>(context);
	settingsButton->setPosition(100, 400);
	settingsButton->setText("Settings");
	settingsButton->setCallback([this] ()
	{
		requestStackPush(States::Settings);
	});

	auto exitButton = std::make_shared<GUI::Button>(context);
	exitButton->setPosition(100, 450);
	exitButton->setText("Exit");
	exitButton->setCallback([this] ()
	{
		requestStackPop();
	});

	mGUIContainer.pack(playMouseButton);
	mGUIContainer.pack(playButton);
	mGUIContainer.pack(settingsButton);
	mGUIContainer.pack(exitButton);

	// Play menu theme
	context.music->play(Music::MenuTheme);
}

void MenuState::draw()
{
	sf::RenderWindow& window = *getContext().window;

	window.setView(window.getDefaultView());

	window.draw(mBackgroundSprite);
	window.draw(mGUIContainer);
}

bool MenuState::update(sf::Time)
{
	return true;
}

bool MenuState::handleEvent(const sf::Event& event)
{
	mGUIContainer.handleEvent(event);
	return false;
}
