#include <algorithm>
#include <iterator>
#include <ranges>
#include <vector>

//ideally most of this is abstracted so that user does not need to worry about data types

//returns the same type if type given is dynamic, if not returns a vector array
//allows for user freedom when writing abstract maths functions
//writen by claude and so needs testing

template <class C>
concept Growable = std::ranges::range<C> &&
    requires(C c, std::ranges::range_value_t<C> x) { c.insert(c.end(), x); };

template <class Like, std::ranges::input_range S>
auto collect_like(S&& src) {
    using L = std::remove_cvref_t<Like>;
    using T = std::ranges::range_value_t<S>;
    if constexpr (Growable<L> && std::convertible_to<T, std::ranges::range_value_t<L>>)
        return std::ranges::to<L>(std::forward<S>(src));
    else
        return std::ranges::to<std::vector<T>>(std::forward<S>(src));
}


//vector and mat templates, actual data structure is defined by users based on their needs
template <class C>
concept Associative = requires { typename std::remove_cvref_t<C>::key_type; };

template <class V>
concept Vec = std::ranges::forward_range<V> && !Associative<V> &&
              std::is_arithmetic_v<std::ranges::range_value_t<V>>;

template <class M>
concept Mat = std::ranges::forward_range<M> && !Associative<M> &&
              Vec<std::ranges::range_reference_t<M>>;

// end of claude written code


//maths functions

template<Vec A,Vec B>
auto dot(const A& a, const B& b)
{
  using T = std::common_type_t<std::ranges::range_value_t<A>,std::ranges::range_value_t<B>>;
  
  if (std::ranges::distance(a) != std::ranges::distance(b))
  {
    //TODO handle this without crashing completely
    throw std::invalid_argument("dot product input vectors are not the same length");
  }

  T output{};
  auto ib = std::ranges::begin(b);
  for(const auto& x : a)
  {
    output += x * *ib;    //ib is a pointer and is being dereferenced
    ib++;
  }
  return output;
}
