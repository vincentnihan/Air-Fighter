#include <Book/SettingsState.hpp>
#include <Book/Utility.hpp>
#include <Book/ResourceHolder.hpp>

#include <SFML/Graphics/RenderWindow.hpp>



SettingsState::SettingsState(StateStack& stack, Context context)
: State(stack, context)
, mGUIContainer()
{
	mBackgroundSprite.setTexture(context.textures->get(Textures::TitleScreen));
	
	// Build key binding buttons and labels
	addButtonLabel(Player::MoveLeft,		300.f, "Move Left", context);
	addButtonLabel(Player::MoveRight,		350.f, "Move Right", context);
	addButtonLabel(Player::MoveUp,			400.f, "Move Up", context);
	addButtonLabel(Player::MoveDown,		450.f, "Move Down", context);
	addButtonLabel(Player::Fire,			500.f, "Fire", context);
	addButtonLabel(Player::LaunchMissile,	550.f, "Heatseeking Missile", context);
	addButtonLabel(Player::LaunchLaser, 600.0f, "Linear Missiles", context);

	updateLabels();

	auto backButton = std::make_shared<GUI::Button>(context);
	backButton->setPosition(80.f, 650.f);
	backButton->setText("Back");
	backButton->setCallback(std::bind(&SettingsState::requestStackPop, this));

	mGUIContainer.pack(backButton);
}

void SettingsState::draw()
{
	sf::RenderWindow& window = *getContext().window;

	window.draw(mBackgroundSprite);
	window.draw(mGUIContainer);
}

bool SettingsState::update(sf::Time)
{
	return true;
}

bool SettingsState::handleEvent(const sf::Event& event)
{
	bool isKeyBinding = false;
	
	// Iterate through all key binding buttons to see if they are being pressed, waiting for the user to enter a key
	for (std::size_t action = 0; action < Player::ActionCount; ++action)
	{
		if (mBindingButtons[action]->isActive())
		{
			isKeyBinding = true;
			if (event.type == sf::Event::KeyReleased)
			{
				getContext().player->assignKey(static_cast<Player::Action>(action), event.key.code);
				mBindingButtons[action]->deactivate();
			}
			break;
		}
	}

	// If pressed button changed key bindings, update labels; otherwise consider other buttons in container
	if (isKeyBinding)
		updateLabels();
	else if (event.mouseMove.x < 301 && event.mouseMove.x > 99 && event.mouseMove.y > 299 && event.mouseMove.y < 701)
	{
		if (event.mouseMove.y < 351)
		{
			if (!mGUIContainer.hasSelection())
		return(NULL);

	// Search previous component that is selectable, wrap around if necessary
	int prev = mGUIContainer.mSelectedChild;
	

	// Select that component
	mGUIContainer.select(0);
		
		} else
		if (event.mouseMove.y < 401)
		{
			//mGUIContainer.selectNext();
			mGUIContainer.select(2);
		}else
		if (event.mouseMove.y < 451)
		{
			mGUIContainer.select(4);
		}else
		if (event.mouseMove.y < 501)
		{
			mGUIContainer.select(6);
		}else
		if (event.mouseMove.y < 551)
		{
			mGUIContainer.select(8);
		}else
		if (event.mouseMove.y < 601)
		{
			mGUIContainer.select(10);
		}else
		if (event.mouseMove.y < 651)
		{
			mGUIContainer.select(12);
		}
		else if (event.mouseMove.y < 701){
			mGUIContainer.select(14);
		}
	} else
	{
				mGUIContainer.handleEvent(event);

	}


	if (event.mouseButton.x < 301 && event.mouseButton.x > 99 && event.mouseButton.y > 299 && event.mouseButton.y < 701)
	{
		if (mGUIContainer.hasSelection())
		mGUIContainer.mChildren[mGUIContainer.mSelectedChild]->activate();
	}

	return false;
}

void SettingsState::updateLabels()
{
	Player& player = *getContext().player;

	for (std::size_t i = 0; i < Player::ActionCount; ++i)
	{
		sf::Keyboard::Key key = player.getAssignedKey(static_cast<Player::Action>(i));
		mBindingLabels[i]->setText(toString(key));
	}
}

void SettingsState::addButtonLabel(Player::Action action, float y, const std::string& text, Context context)
{
	mBindingButtons[action] = std::make_shared<GUI::Button>(context);
	mBindingButtons[action]->setPosition(80.f, y);
	mBindingButtons[action]->setText(text);
	mBindingButtons[action]->setToggle(true);

	mBindingLabels[action] = std::make_shared<GUI::Label>("", *context.fonts);
	mBindingLabels[action]->setPosition(300.f, y + 15.f);

	mGUIContainer.pack(mBindingButtons[action]);
	mGUIContainer.pack(mBindingLabels[action]);
}
