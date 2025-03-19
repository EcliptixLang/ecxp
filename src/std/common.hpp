#pragma once
#include <memory>

template <typename T>
std::shared_ptr<T> createValue(T thing);