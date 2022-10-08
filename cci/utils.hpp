#pragma once

#include <concepts>
#include <iostream>
#include <ranges>

template <typename TContainer>
requires std::ranges::input_range<const TContainer> &&(
    !std::convertible_to<const TContainer,
                         std::string_view>)void PrintContainer(const TContainer&
                                                                   cont) {
  for (const auto& elem : cont) {
    std::cout << elem << ", ";
  }
  std::cout << std::endl;
}
