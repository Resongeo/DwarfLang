#pragma once

#include <string>

namespace HasteLang
{
	enum class SourceType
	{
		String, Filepath
	};

	class Haste
	{
	public:
		Haste(const std::string& source, SourceType sourceType);

		void Run();
		static void PrintInfo();

	private:
		std::string ReadFile(const std::string& filepath);

	private:
		std::string m_Source;
	};
}