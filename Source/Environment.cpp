#include "Environment.h"

namespace HasteLang
{
	void Environment::Define(const String& name, const Object& value)
	{
		m_Values[name] = value;
	}

	Object Environment::Get(const String& name)
	{
		if (m_Values.find(name) != m_Values.end()) return m_Values[name];
		return Object();
	}

	Object Environment::Get(const Token& token)
	{
		auto name = token.Value.ToString();

		if (m_Values.find(name) != m_Values.end()) return m_Values[name];
		return Object();
	}
}