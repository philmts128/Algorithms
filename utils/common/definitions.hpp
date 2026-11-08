#pragma once

#include <string>
#include <vector>
#include <stack>
#include <queue>
#include <unordered_map>


#define DSA_NAMESPACE_BEGIN namespace dsa {
#define DSA_NAMESPACE_END   }

using u8 = std::uint8_t;
using u16 = std::uint16_t;
using u32 = std::uint32_t;
using u64 = std::uint64_t;

using fstring = std::string;
using fstr_view = std::string_view;

template <typename T>
using fvector = std::vector<T>;

template <typename T>
using fstack = std::stack<T>;

template <typename T>
using fqueue = std::queue<T>;

template <class K, class V>
using hash_map = std::unordered_map<K, V>;


