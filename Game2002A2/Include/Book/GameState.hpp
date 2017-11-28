#ifndef BOOK_GAMESTATE_HPP
#define BOOK_GAMESTATE_HPP

#include <Book/State.hpp>
#include <Book/World.hpp>
#include <Book/Player.hpp>
#include <Book/Container.hpp>

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>


class GameState : public State
{
	public:
							GameState(StateStack& stack, Context context);
							GameState(StateStack& stack, Context context, bool mouseCTRL);

		virtual void		draw();
		virtual bool		update(sf::Time dt);
		virtual bool		handleEvent(const sf::Event& event);

		bool mouseEnabled;
	//private:
		World				mWorld;
		Player&				mPlayer;
		sf::Text			mGameText;
};

#endif // BOOK_GAMESTATE_HPP