#pragma once

#include "Types.h"
#include "Lexer.h"

namespace HasteLang
{
	class Haste
	{
	public:
		Haste(const String& filepath);

		void Run();
		static void PrintInfo();
		static void Error(const String& message, int line);

	private:
		String ReadFile(const String& filepath);

	private:
		static Haste* s_Instance;
		String m_Source;
		bool m_Error = false;
	};
}