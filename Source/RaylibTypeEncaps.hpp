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
            this->_x = x;
            this->_y = y;
        };
        Vector2() = default;

        ::Vector2 getStruct() const {
            return {this->_x, this->_y};
        }

        // Allows for passing this class as Vector2 struct without calling
        // getStruct
        ::Vector2 operator(::Vector2)() const {
            return {this->_x, this->_y};
        }

        T _x = 0;
        T _y = 0;
    };

    template<class T>
    requires std::is_arithmetic_v<T>
    class Vector3 {
    public:
        Vector3(T x, T y, T z) {
            this->_x = x;
            this->_y = y;
            this->_z = z;
        };
        Vector3() = default;

        ::Vector3 getStruct() const {
            return {this->_x, this->_y, this->_z};
        }

        // Allows for passing this class as Vector2 struct without calling
        // getStruct
        ::Vector3 operator(::Vector3)() const {
            return {this->_x, this->_y};
        }

        T _x = 0;
        T _y = 0;
        T _z = 0;
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
