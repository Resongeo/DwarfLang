#pragma once

#include <string>
#include <variant>

namespace HasteLang
{
	enum class DataType
	{
		String, Double, Bool, Null
	};

	class Object
	{
	public:
		Object(std::string str) : m_Value(str) {}
		Object(double d) : m_Value(d) {}
		Object(bool b) : m_Value(b) {}
		Object() : m_Value() {}

		DataType GetType() { return (DataType)m_Value.index(); }

		std::string ToString() const
		{
			if (std::holds_alternative<std::string>(m_Value))
			{
				return std::get<std::string>(m_Value);
			}
			else if (std::holds_alternative<double>(m_Value))
			{
				return std::to_string(std::get<double>(m_Value));
			}
			else if (std::holds_alternative<bool>(m_Value))
			{
				return std::get<bool>(m_Value) ? "true" : "false";
			}
			else
			{
				return "null";
			}
		}

		template<typename T>
		T Get()
		{
			if (std::holds_alternative<T>(m_Value))
			{
				return std::get<T>(m_Value);
			}
			else
			{
				throw std::bad_variant_access();
			}
		}

	private:
		std::variant<std::string, double, bool, std::monostate> m_Value;
	};
}