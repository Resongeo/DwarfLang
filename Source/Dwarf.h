#pragma once

#include "Types.h"
#include "Lexer.h"

namespace DwarfLang
{
	enum class InputSource
	{
		File,
		User
	};

	class Dwarf
	{
	public:
		Dwarf(const String& source, InputSource inputSource);

		void Run();
		static void PrintInfo();
		static void Error(const String& message);
		static void Error(const String& message, size_t line);
		static void Error(const Token& token, const String& message);

	private:
		String ReadFile(const String& filepath);

	private:
		static Dwarf* s_Instance;
		String m_Source;
		bool m_Error = false;
	};
}