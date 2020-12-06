#pragma once

#include <iomanip>

#include "AnsiStyle.h"

class Console {

public:

	enum class Alignment {
		Left = 0,
		Right = 1,
	};

	struct AlignmentInfo {

		AlignmentInfo(std::size_t width = 0, char fill = ' ', Alignment method = Alignment::Left)
			: width(width), fill(fill), alignmentMethod(method) {}

		std::size_t width;
		char fill;
		Alignment alignmentMethod;

	};

	Console() = delete;

	static void newLine() noexcept { std::cout << '\n'; }

	static void setForegroundColor(AnsiStyle::Forecolors color) noexcept;
	static void setBackgroundColor(AnsiStyle::Backcolors color) noexcept;

	static void reset() noexcept;
	static void clear() noexcept;

	static std::size_t getWidth() noexcept;
	static std::size_t getHeight() noexcept;
	static std::pair<std::size_t, std::size_t> getSize() noexcept;

	static void fill(std::size_t count = 0, char c = ' ') noexcept
	{
		std::string s = std::string(count ? count : getWidth() * getHeight(), c);
		std::cout << s;
	}

	static void fillLine(char c = ' ') noexcept
	{
		fill(getWidth(), c);
	}

	template  <typename... Args>
	static void align(const AlignmentInfo& info, Args... args) noexcept
	{
		std::ios state = std::ios(nullptr);
		state.copyfmt(std::cout);

		switch (info.alignmentMethod)
		{
			case Alignment::Left: std::cout << std::left; break;
			case Alignment::Right: std::cout << std::right; break;
		}

		std::cout << std::setw(info.width) << std::setfill(info.fill);
		write(args...);

		std::cout.copyfmt(state);
	}

	template <typename... Args>
	static void alert(Args... args) noexcept
	{
		setForegroundColor(AnsiStyle::Forecolors::Yellow);
		writeLine(args...);
		reset();
	}

	template <typename... Args>
	static void error(Args... args) noexcept
	{
		setForegroundColor(AnsiStyle::Forecolors::Red);
		(std::cerr << ... << args) << '\n';
		reset();
	}

	template <typename... Args>
	static void write(Args... args)
	{
		(std::cout << ... << args);
	}

	template <typename... Args>
	static void writeColored(AnsiStyle::Forecolors color, Args... args) noexcept
	{
		setForegroundColor(color);
		write(args...);
		reset();
	}

	template <typename... Args>
	static void writeLine(Args... args) noexcept
	{
		(std::cout << ... << args) << '\n';
	}

	template <typename... Args>
	static void writeColoredLine(AnsiStyle::Forecolors color, Args... args) noexcept
	{
		setForegroundColor(color);
		writeLine(args...);
		reset();
	}

};
