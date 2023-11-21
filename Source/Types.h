#pragma once

#include <vector>
#include <string>
#include <unordered_map>

using String = std::string;

template<typename T>
using Vector = std::vector<T>;

template<typename K, typename V>
using HashMap = std::unordered_map<K, V>;