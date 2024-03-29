#pragma once

#include <string>
#include <variant>

namespace DwarfLang
{
	enum class DataType
	{
		Null, Double, Bool, String
	};

	class Object
	{
	public:
		Object() : m_Value() {}
		Object(std::string str) : m_Value(str) {}
		Object(double d) : m_Value(d) {}
		Object(bool b) : m_Value(b) {}

		DataType GetType() const { return (DataType)m_Value.index(); }

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

		template<typename T>
		T& GetRef()
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
		std::variant<std::monostate, double, bool, std::string> m_Value;
	};
}