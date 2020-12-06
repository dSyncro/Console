#include "Detective.h"

#if !defined(DETECTIVE_OS_WINDOWS)

#include <Console.h>

#include <sys/ioctl.h>
#include <unistd.h>

void Console::setForegroundColor(AnsiStyle::Forecolors color) noexcept { std::cout << color; }
void Console::setBackgroundColor(AnsiStyle::Backcolors color) noexcept { std::cout << color; }
void Console::reset() noexcept { std::cout << AnsiStyle::Reset; }
void Console::clear() noexcept { std::cout << AnsiStyle::Clear << AnsiStyle::CursorNavigation::Home; }

std::size_t Console::getWidth() noexcept
{
	struct winsize size;
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &size);
	return size.ws_col;
}

std::size_t Console::getHeight() noexcept
{
	struct winsize size;
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &size);
	return size.ws_row;
}

std::pair<std::size_t, std::size_t> Console::getSize() noexcept
{
	struct winsize size;
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &size);
	return { size.ws_col, size.ws_row };
}

#endif
