#pragma once

#include <type_traits>
#include <raylib.h>
#include <ostream>
#include <iostream>

namespace RL {

    // These Classes encapsulate Raylib's Vector2 and Vector3 structures
    //
    // Templating allows for the use to choose the numerical type of the vector
    // Note: It will not compile with non numerical types
    //
    // For simplicity, use the typedefed Vector2i, Vector2f...
    //
    // These can be passed to functions taking traditional raylib Vector2 and 3
    // structures and will be converted automatically

    template<class T>
    //requires std::is_arithmetic_v<T>
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

        // Allows for passing this class as Vector2 struct without calling getStruct
        operator ::Vector2() {
            return {this->x, this->y};
        }

        friend std::ostream &operator<<(std::ostream &os, Vector2<T> vect) {
            os << "(Vector2) {x:" << vect.x << " y:" << vect.y << "}";

            return os;
        }

        T x = 0;
        T y = 0;
    };

    template<class T>
    //requires std::is_arithmetic_v<T>
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

        // Allows for passing this class as Vector2 struct without calling getStruct
        operator ::Vector3() {
            return {this->x, this->y, this->z};
        }

        // template<class X>
        friend std::ostream &operator<<(std::ostream &os, Vector3<T> vect) {
            os << "(Vector3) {x:" << vect.x << " y:" << vect.y;
            os << " z:" << vect.z << "}";

            return os;
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

// operator conversion
