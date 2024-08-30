#pragma once

#include "Forwards.h"

namespace zeus::math
{

struct Vector3
{
    double x = 0.0f;
    double y = 0.0f;
    double z = 0.0f;

    // 构造函数
    Vector3(double x = 0.0f, double y = 0.0f, double z = 0.0f)
        : x(x)
        , y(y)
        , z(z)
    {
    }

    // 向量加法
    Vector3 operator+(const Vector3& v) const
    {
        return Vector3(x + v.x, y + v.y, z + v.z);
    }

    // 向量加法赋值
    Vector3& operator+=(const Vector3& v) 
    {
        x += v.x;
        y += v.y;
        z += v.z;
        return *this;
    }

    // 向量减法
    Vector3 operator-(const Vector3& v) const
    {
        return Vector3(x - v.x, y - v.y, z - v.z);
    }

    // 向量减法赋值
    Vector3& operator-=(const Vector3& v)
    {
        x -= v.x;
        y -= v.y;
        z -= v.z;
        return *this;
    }

    // 向量负号
    Vector3 operator-() const 
    {
        return Vector3(-x, -y, -z);
    }

    // 向量标量乘法
    Vector3 operator*(double scalar) const 
    {
        return Vector3(x * scalar, y * scalar, z * scalar);
    }

    // 向量标量乘法赋值
    Vector3& operator*=(double scalar) 
    {
        x *= scalar;
        y *= scalar;
        z *= scalar;
        return *this;
    }

    // 标量在左侧的向量标量乘法
    friend Vector3 operator*(double scalar, const Vector3& v)
    {
        return v * scalar;
    }

    // 向量标量除法
    Vector3 operator/(double scalar) const 
    {
        return Vector3(x / scalar, y / scalar, z / scalar);
    }

    // 向量标量除法赋值
    Vector3& operator/=(double scalar) 
    {
        x /= scalar;
        y /= scalar;
        z /= scalar;
        return *this;
    }

    // 标量在左侧的向量标量除法，虽然数学上不常见，提供一个示例实现
    friend Vector3 operator/(double scalar, const Vector3& v)
    {
        return Vector3(scalar / v.x, scalar / v.y, scalar / v.z);
    }

    // 向量比较相等
    bool operator==(const Vector3& v) const 
    {
        return x == v.x && y == v.y && z == v.z;
    }

    // 向量比较不等
    bool operator!=(const Vector3& v) const 
    {
        return !(*this == v);
    }

    // 向量点乘
    double Dot(const Vector3& v) const
    {
        return x * v.x + y * v.y + z * v.z;
    }

    // 向量叉乘
    Vector3 Cross(const Vector3& v) const
    {
        return Vector3(y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x);
    }

    // 向量长度
    double Length() const
    {
        return sqrt(x * x + y * y + z * z);
    }

    // 向量归一化
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

    // 输出向量
    friend std::ostream& operator<<(std::ostream& os, const Vector3& v)
    {
        os << "(" << v.x << ", " << v.y << ", " << v.z << ")";
        return os;
    }
};

} // namespace zeus::math