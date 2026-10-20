#pragma once

#include <string>
#include <vector>
#include <unordered_map>


#define DSA_NAMESPACE_BEGIN namespace dsa {
#define DSA_NAMESPACE_END   }

using fstring = std::string;

template <typename T>
using fvector = std::vector<T>;

template <class K, class V>
using hash_map = std::unordered_map<K, V>;


