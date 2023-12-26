#pragma once

#include "Types.h"
#include "Token.h"

namespace HasteLang
{
	class Environment
	{
	public:
		Environment() = default;

		void Assign(const String& name, const Object& value);
		void Define(const String& name, const Object& value);
		Object Get(const String& name);
		Object Get(const Token& token);

	private:
		HashMap<String, Object> m_Values;
	};
}