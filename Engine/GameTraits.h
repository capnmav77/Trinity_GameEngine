#pragma once
#include <type_traits>

// Helper type trait to check if a type is a pointer to a class derived from Player
template<typename T>
struct IsPointerToPlayerDerived : std::false_type {};

template<typename T>
struct IsPointerToPlayerDerived<T*> : std::is_base_of<Player, typename std::remove_pointer<T>::type> {};
