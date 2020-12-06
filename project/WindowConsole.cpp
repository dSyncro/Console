#include <Detective.h>

#if defined(DETECTIVE_OS_WINDOWS)

#include <Console.h>
#include <Windows.h>

using namespace AnsiStyle;

const HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

static CONSOLE_SCREEN_BUFFER_INFO GetConsoleInfo() noexcept
{
	CONSOLE_SCREEN_BUFFER_INFO info;
	GetConsoleScreenBufferInfo(hConsole, &info);
	return info;
}

const CONSOLE_SCREEN_BUFFER_INFO baseConsoleInfo = GetConsoleInfo();

enum class WinConsoleColors {
	Black,
	Blue,
	Green,
	Aqua,
	Red,
	Purple,
	Yellow,
	White,
	Gray,
	LightBlue,
	LightGreen,
	LightAqua,
	LightRed,
	LightPurple,
	LightYellow,
	BrightWhite
};

static WinConsoleColors ansiForegroundToWinColor(Forecolors color)
{
	switch (color)
	{
		case Forecolors::DarkBlack: return WinConsoleColors::Black;
		case Forecolors::DarkRed: return WinConsoleColors::Red;
		case Forecolors::DarkGreen: return WinConsoleColors::Green;
		case Forecolors::DarkYellow: return WinConsoleColors::Yellow;
		case Forecolors::DarkBlue: return WinConsoleColors::Blue;
		case Forecolors::DarkMagenta: return WinConsoleColors::Purple;
		case Forecolors::DarkCyan: return WinConsoleColors::Aqua;
		case Forecolors::DarkWhite: return WinConsoleColors::White;
		case Forecolors::Black: return WinConsoleColors::Gray;
		case Forecolors::Red: return WinConsoleColors::LightRed;
		case Forecolors::Green: return WinConsoleColors::LightGreen;
		case Forecolors::Yellow: return WinConsoleColors::LightYellow;
		case Forecolors::Blue: return WinConsoleColors::LightBlue;
		case Forecolors::Magenta: return WinConsoleColors::LightPurple;
		case Forecolors::Cyan: return WinConsoleColors::LightAqua;
		case Forecolors::White:
		default: return WinConsoleColors::BrightWhite;
	}
}

static WinConsoleColors ansiBackgroundToWinColor(Backcolors color)
{
	switch (color)
	{
		case Backcolors::DarkBlack: return WinConsoleColors::Black;
		case Backcolors::DarkRed: return WinConsoleColors::Red;
		case Backcolors::DarkGreen: return WinConsoleColors::Green;
		case Backcolors::DarkYellow: return WinConsoleColors::Yellow;
		case Backcolors::DarkBlue: return WinConsoleColors::Blue;
		case Backcolors::DarkMagenta: return WinConsoleColors::Purple;
		case Backcolors::DarkCyan: return WinConsoleColors::Aqua;
		case Backcolors::DarkWhite: return WinConsoleColors::White;
		case Backcolors::Black: return WinConsoleColors::Gray;
		case Backcolors::Red: return WinConsoleColors::LightRed;
		case Backcolors::Green: return WinConsoleColors::LightGreen;
		case Backcolors::Yellow: return WinConsoleColors::LightYellow;
		case Backcolors::Blue: return WinConsoleColors::LightBlue;
		case Backcolors::Magenta: return WinConsoleColors::LightPurple;
		case Backcolors::Cyan: return WinConsoleColors::LightAqua;
		case AnsiStyle::Backcolors::White:
		default: return WinConsoleColors::BrightWhite;
	}
}

void Console::setForegroundColor(Forecolors color) noexcept
{
	WinConsoleColors consoleColor = ansiForegroundToWinColor(color);
	SetConsoleTextAttribute(hConsole, (int)consoleColor);
}

void Console::setBackgroundColor(Backcolors color) noexcept
{
	WinConsoleColors consoleColor = WinConsoleColors::White;
	SetConsoleTextAttribute(hConsole, 16 * (int)consoleColor);
}

void Console::reset() noexcept
{
	SetConsoleTextAttribute(hConsole, baseConsoleInfo.wAttributes);
}

void Console::clear() noexcept
{
	COORD cursorPos = { 0, 0 };
	CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
	GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
	DWORD written, cells = consoleInfo.dwSize.X * consoleInfo.dwSize.Y;
	FillConsoleOutputCharacterW(hConsole, ' ', cells, cursorPos, &written);
	FillConsoleOutputAttribute(hConsole, consoleInfo.wAttributes, cells, cursorPos, &written);
	SetConsoleCursorPosition(hConsole, cursorPos);;
}

std::size_t Console::getWidth() noexcept
{
	CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
	GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
	return consoleInfo.dwSize.X;
}

std::size_t Console::getHeight() noexcept
{
	CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
	GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
	return consoleInfo.dwSize.Y;
}

std::pair<std::size_t, std::size_t> Console::getSize() noexcept
{
	CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
	GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
	return { consoleInfo.dwSize.X, consoleInfo.dwSize.Y };
}

#endif
