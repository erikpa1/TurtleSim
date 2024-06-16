#pragma once

#include <vector>
#include <unordered_map>
#include <string>
#include <iostream>
#include <memory>
#include <optional>

#include "logging.h"

using String = std::string;

template <typename T>
using HashMap = std::unordered_map<std::string, T>;

template <typename T>
using Array = std::vector<T>;

template <typename T>
using Option = std::optional<T>;

template <typename T>
using Shared = std::shared_ptr<T>;

template <typename T, typename... Args>
std::shared_ptr<T> Share(Args &&...args)
{
    return std::make_shared<T>(std::forward<Args>(args)...);
}
