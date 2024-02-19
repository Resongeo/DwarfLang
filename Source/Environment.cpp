#include "Environment.h"
#include "Dwarf.h"

namespace DwarfLang
{
	namespace Utils
	{
		inline static String DataTypeToString(DataType type)
		{
			switch (type)
			{
				case DataType::String: return "String";
				case DataType::Double: return "Double";
				case DataType::Bool: return "Bool";
				case DataType::Null: return "Null";
			}

			return "Unknown data type";
		}
	}

	void Environment::Assign(const String& name, const Object& value)
	{
		if (m_Values.find(name) != m_Values.end())
		{
			auto current = m_Values[name];

			if (current.GetType() == DataType::Null || current.GetType() == value.GetType())
			{
				m_Values[name] = value;
				return;
			}

			Dwarf::Error("Cannot change variable '" + name + "' from " + Utils::DataTypeToString(current.GetType()) + " to " + Utils::DataTypeToString(value.GetType()));
			return;
		}

		Dwarf::Error("Undefined variable '" + name + "'");
	}

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