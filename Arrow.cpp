#include "precomp.h"
#include "Arrow.h"
#include "game.h"

Arrow::Arrow(Sprite* sprite) : arrow(sprite)
{
}

void Arrow::keyDown(int const key)
{
	switch(key)
	{
	case GLFW_KEY_LEFT:
	case GLFW_KEY_A:
		x = startPosX;
		break;
	case GLFW_KEY_RIGHT:
	case GLFW_KEY_D:
		x = secondStartPosX;
		break;
	case GLFW_KEY_ENTER:
		if (game->showMenu)
		{
			if (x == startPosX)
			{
				game->showMenu = false;
				game->showGameMode = true;
			}
			else if (x == secondStartPosX)
			{
				game->showMenu = false;
				game->showControls = true;
			}
			break;
		}

		if (game->showGameOver)
		{
			if (x == startPosX)
			{
				game->showGameOver = false;
				game->showGameMode = true;
				game->pressedPlay = true;
			}
			else if (x == secondStartPosX)
			{
				game->showGameOver = false;
				exit(0);
			}
			game->showGame = false;
			break;
		}
		if (game->showGameMode)
		{
			if (x == startPosX)
			{
				game->showGameMode = false;
				game->gameMode = 1;
			}
			else if (x == secondStartPosX)
			{
				game->showGameMode = false;
				game->gameMode = 2;
			}
			game->showGame = true;
			break;
		}

		if (game->showControls)
		{
			if (x == startPosX)
			{
				game->showMenu = true;
			}
			else if (x == secondStartPosX)
			{
				game->showGameMode = true;
			}
			game->showControls = false;
			break;
		}

		/*if (x == startPosX)
		{
			if (game->showMenu)
			{
				//game->showMenu = false;
				game->showGameMode = true;
				//game->showGameOver = true;
				//game->showGame = true;
				//game->pressedPlay = true;
				break;
			}

			if (game->showGameOver)
			{
				game->pressedPlay = true;
				game->showGameOver = false;
				game->showGame = false;
				game->showGameMode = true;
				break;
			}

			if (game->showGameMode)
			{
				//game->showMenu = false;
				game->gameMode = 1;
				game->showGameMode = false;
				game->showGame = true;
				break;
			}
		}

		if (x == secondStartPosX)
		{
			if (game->showMenu)
			{
				game->showControls = true;
				break;
			}

			if (game->showGameOver)
			{
				exit(0);
			}

			if (game->showGameMode)
			{
				game->gameMode = 2;
				game->showGameMode = false;
				game->showGame = true;
				break;
			}
		}
		*/
	}
}

void Arrow::move()
{
}

void Arrow::Draw(Surface* screen) const
{
	arrow->Draw(screen, x, y);
}
