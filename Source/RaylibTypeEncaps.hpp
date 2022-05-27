#ifndef BOMBERMAN_VECTORTYPES_HPP
#define BOMBERMAN_VECTORTYPES_HPP

#include <type_traits>
#include <raylib.h>

namespace RL {

    template<class T>
    requires std::is_arithmetic_v<T>
    class Vector2 {
    public:
        Vector2(T x, T y) {
            this->x = x;
            this->y = y;
        };
        Vector2() = default;

        ::Vector2 getStruct() {
            return {this->x, this->y};
        }

        // Allows for passing this class as Vector2 struct without calling
        // getStruct
        operator ::Vector2() {
            return {this->x, this->y};
        }

        T x = 0;
        T y = 0;
    };

    template<class T>
    requires std::is_arithmetic_v<T>
    class Vector3 {
    public:
        Vector3(T x, T y, T z) {
            this->x = x;
            this->y = y;
            this->z = z;
        };
        Vector3() = default;

        ::Vector3 getStruct() {
            return {this->x, this->y, this->z};
        }

        // Allows for passing this class as Vector2 struct without calling
        // getStruct
        operator ::Vector3() {
            return {this->x, this->y};
        }

        T x = 0;
        T y = 0;
        T z = 0;
    };

    // Utilitarian typedefs
    // USE THESE FOR CLARITY
    typedef Vector2<int> Vector2i;
    typedef Vector3<int> Vector3i;
    typedef Vector2<float> Vector2f;
    typedef Vector3<float> Vector3f;
}

#endif

// operator conversion
