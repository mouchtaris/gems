# https://stackoverflow.com/questions/19071268

All these answers (and question) become irrelevant with modern (c++17+) C++.

If, however, you find that you compose functions a lot, this is the C++17 most correct solution:

```cpp
// compose.h
#include <utility>
template <
    typename F,
    typename G
>
constexpr auto compose(F&& f, G&& g)
{
    // Necessarily capture functions by copy.
    return [f, g](auto&& x)
    {
        // Forward argument properly.
        return g(f(std::forward<decltype(x)>(x)));
    };
}
```

This solution is succinct, forwards arguments perfectly, and would not even require any
heavy-weight header includes (as heavy-weight as `<utility>` can be considered) if it
wasn't for the three-line-implementation utility template function `std::forward`.
It also works as a `constexpr`.

To ensure yourself, testing it is also trivial:

```cpp
// test.cpp
#include "compose.h"
constexpr auto f = [](int x) { return x + 1; };
constexpr auto g = [](int x) { return x - 1; };
constexpr auto fog = compose(f, g);
static_assert(fog(0) == 0, "");
```

```Makefile
# Makefile
check:
	@g++ -pedantic -ansi -Wall -Wextra -Werror \
	    -std=c++17 -c -o /dev/null test.cpp   \
	&& echo ok   \
	|| echo fail
```

If `g++ -pedantic -ansi -Wall -Wextra -Werror -std=c++17 -c -o /dev/null test.cpp` returns success, then this implementation works as intended.
Run `make check` to check. Change `fog(0) == 0` to `fog(0) == 1` to reassure yourself even more.

