#pragma once

#include "Forwards.h"

namespace zeus::math
{

struct Vector3
{
    double x = 0.0f;
    double y = 0.0f;
    double z = 0.0f;

    // 鏋勯€犲嚱鏁?
    Vector3(double x = 0.0f, double y = 0.0f, double z = 0.0f)
        : x(x)
        , y(y)
        , z(z)
    {
    }

    // 鍚戦噺鍔犳硶
    Vector3 operator+(const Vector3& v) const
    {
        return Vector3(x + v.x, y + v.y, z + v.z);
    }

    // 鍚戦噺鍔犳硶璧嬪€?
    Vector3& operator+=(const Vector3& v) 
    {
        x += v.x;
        y += v.y;
        z += v.z;
        return *this;
    }

    // 鍚戦噺鍑忔硶
    Vector3 operator-(const Vector3& v) const
    {
        return Vector3(x - v.x, y - v.y, z - v.z);
    }

    // 鍚戦噺鍑忔硶璧嬪€?
    Vector3& operator-=(const Vector3& v)
    {
        x -= v.x;
        y -= v.y;
        z -= v.z;
        return *this;
    }

    // 鍚戦噺璐熷彿
    Vector3 operator-() const 
    {
        return Vector3(-x, -y, -z);
    }

    // 鍚戦噺鏍囬噺涔樻硶
    Vector3 operator*(double scalar) const 
    {
        return Vector3(x * scalar, y * scalar, z * scalar);
    }

    // 鍚戦噺鏍囬噺涔樻硶璧嬪€?
    Vector3& operator*=(double scalar) 
    {
        x *= scalar;
        y *= scalar;
        z *= scalar;
        return *this;
    }

    // 鏍囬噺鍦ㄥ乏渚х殑鍚戦噺鏍囬噺涔樻硶
    friend Vector3 operator*(double scalar, const Vector3& v)
    {
        return v * scalar;
    }

    // 鍚戦噺鏍囬噺闄ゆ硶
    Vector3 operator/(double scalar) const 
    {
        return Vector3(x / scalar, y / scalar, z / scalar);
    }

    // 鍚戦噺鏍囬噺闄ゆ硶璧嬪€?
    Vector3& operator/=(double scalar) 
    {
        x /= scalar;
        y /= scalar;
        z /= scalar;
        return *this;
    }

    // 鏍囬噺鍦ㄥ乏渚х殑鍚戦噺鏍囬噺闄ゆ硶锛岃櫧鐒舵暟瀛︿笂涓嶅父瑙侊紝鎻愪緵涓€涓ず渚嬪疄鐜?
    friend Vector3 operator/(double scalar, const Vector3& v)
    {
        return Vector3(scalar / v.x, scalar / v.y, scalar / v.z);
    }

    // 鍚戦噺姣旇緝鐩哥瓑
    bool operator==(const Vector3& v) const 
    {
        return x == v.x && y == v.y && z == v.z;
    }

    // 鍚戦噺姣旇緝涓嶇瓑
    bool operator!=(const Vector3& v) const 
    {
        return !(*this == v);
    }

    // 鍚戦噺鐐逛箻
    double Dot(const Vector3& v) const
    {
        return x * v.x + y * v.y + z * v.z;
    }

    // 鍚戦噺鍙変箻
    Vector3 Cross(const Vector3& v) const
    {
        return Vector3(y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x);
    }

    // 鍚戦噺闀垮害
    double Length() const
    {
        return sqrt(x * x + y * y + z * z);
    }

    // 鍚戦噺褰掍竴鍖?
    Vector3 Normalize() const
    {
        double len = Length();
        if (len == 0) return *this;
        return *this / len;
    }

    void Swap(Vector3& other)
    {
        std::swap(x, other.x);
        std::swap(y, other.y);
        std::swap(y, other.z);
    }

    // 杈撳嚭鍚戦噺
    friend std::ostream& operator<<(std::ostream& os, const Vector3& v)
    {
        os << "(" << v.x << ", " << v.y << ", " << v.z << ")";
        return os;
    }
};

} // namespace zeus::math
