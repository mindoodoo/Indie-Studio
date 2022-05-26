#ifndef BOMBERMAN_VECTORTYPES_HPP
#define BOMBERMAN_VECTORTYPES_HPP

#include <type_traits>
#include <raylib.h>

namespace RL {

    // This defines a "concept" (c++ 20) Numerical that allows us to constrain
    // templates to only be of numerical values
    template<typename T>
    concept Numerical = requires(T)
    {
        requires std::is_arithmetic_v<T>;
    };

    template<Numerical T>
    class Vector2 {
    public:
        Vector2(T x, T y) {
            this->x = x;
            this->y = y;
        };
        Vector2() = default;

        struct Vector2 getStruct() const {
            return {this->x, this->y}
        }

    private:
        T _x = 0;
        T _y = 0;
    };
}

#endif
