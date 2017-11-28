#ifndef BOOK_GAMESTATE2_HPP
#define BOOK_GAMESTATE2_HPP

#include <Book/State.hpp>
#include <Book/World.hpp>
#include <Book/Player.hpp>

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>


class GameState2 : public State
{
	public:
							GameState2(StateStack& stack, Context context);

		virtual void		draw();
		virtual bool		update(sf::Time dt);
		virtual bool		handleEvent(const sf::Event& event);


	private:
		World				mWorld;
		Player&				mPlayer;
		sf::Text			mGame2Text;
};

#endif // BOOK_GAMESTATE_HPP