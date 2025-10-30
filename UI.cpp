#include "precomp.h"
#include "UI.h"

UI::UI(Surface* surface, int x, int y)
	: surface(surface), x(x), y(y)
{
}

void UI::Draw(Surface* screen)
{
	surface->CopyTo(screen, x, y);
}
