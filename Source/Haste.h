#pragma once

#include "Types.h"
#include "Lexer.h"

namespace HasteLang
{
	enum class InputSource
	{
		File,
		User
	};

	class Haste
	{
	public:
		Haste(const String& source, InputSource inputSource);

		void Run();
		static void PrintInfo();
		static void Error(const String& message, size_t line);
		static void Error(const Token& token, const String& message);

	private:
		String ReadFile(const String& filepath);

	private:
		static Haste* s_Instance;
		String m_Source;
		bool m_Error = false;
	};
}