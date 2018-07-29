#ifndef VECTOR_H
#define VECTOR_H

#include "common.h"


namespace ResidentEvil4
{
    template <class T>
    class Vector3
    {
    public:
        T m_y, m_z, m_x;


        Vector3 () {}
        Vector3 (const T x, const T y, const T z) :
            m_x { x }, m_y { y }, m_z { z }
        {
        }

        ~Vector3 () {}


        Vector3& operator = (const Vector3 &v)
        {
            m_x = v.m_x;
            m_y = v.m_y;
            m_z = v.m_z;
            return *this;
        }
        
        Vector3& operator + (const Vector3 &v) const
        {
            return Vector3 { m_x + v.m_x, m_y + v.m_y, m_z + v.m_z };
        }

        Vector3& operator += (const Vector3 &v)
        {
            m_x += v.m_x;
            m_y += v.m_y;
            m_z += v.m_z;
            return *this;
        }

        Vector3& operator - (const Vector3 &v) const
        {
            return Vector3 { m_x - v.m_x, m_y - v.m_y, m_z - v.m_z };
        }

        Vector3& operator -= (const Vector3 &v)
        {
            m_x -= v.m_x;
            m_y -= v.m_y;
            m_z -= v.m_z;
            return *this;
        }

        Vector3& operator * (const T k) const
        {
            return Vector3 { m_x * k, m_y * k, m_z * k };
        }

        Vector3& operator *= (const T k)
        {
            m_x *= k;
            m_y *= k;
            m_z *= k;
            return *this;
        }

        Vector3& operator / (const T k) const
        {
            return Vector3 { m_x / k, m_y / k, m_z / k };
        }

        Vector3& operator /= (const T k)
        {
            m_x /= k;
            m_y /= k;
            m_z /= k;
            return *this;
        }


        T getMagnitude () const
        {
            return std::sqrt( dot(*this) );
        }

        void normalize ()
        {
            *this /= getMagnitude();
        }

        T dot (const Vector3 &v) const
        {
            return m_x * v.m_x + m_y * v.m_y + m_z * v.m_z;
        }

        T getAngle (const Vector3 &v) const
        {
            return std::acos( dot(v) / ( getMagnitude() * v.getMagnitude() ) );
        }

        void print () const
        {
            std::cout << "(" << m_x << ", " << m_y << ", " << m_z << ")" << std::endl;
        }

    protected:
    private:

    };

}

#endif