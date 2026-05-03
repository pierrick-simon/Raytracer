/*
** EPITECH PROJECT, 2026
** RayTracer
** File description:
** DESCRIPTION
*/

#ifndef QUATERNION_HPP
    #define QUATERNION_HPP

namespace Maths {
    class Quaternion {
    public:
        Quaternion() = delete;

        bool operator==(const Quaternion &rhs) const;

        bool operator!=(const Quaternion &rhs) const;

        /**
         * Creates new Quaternion representing the rotation of this rotated by
         * \p rhs.
         *
         * As rotations are applied in sequence, it means that \code lhs
         * * rhs\endcode is different from \code rhs * lhs\endcode.
         * @param rhs The right-hand-side Quaternion
         * @return A new Quaternion representing the rotation of this rotated
         * by \p rhs
         */
        Quaternion operator*(const Quaternion &rhs) const;

        /**
         * Rotates the current Quaternion by \p rhs.
         * Note that rotations are applied in sequence, so you might need to
         * swap the orders of the Quaternions.
         * @param rhs The right-hand-side Quaternion
         * @return this but rotated.
         */
        Quaternion &operator*=(const Quaternion &rhs);

        /**
         * When normalized, a quaternion keeps the same rotation, but its
         * magnitude is 1.0.
         *
         * As a rotation Quaternion always has a length of 1, this function is
         * mainly used to fix floating-point errors.
         *
         * This method doesn't modify the current Quaternion. Use normalize()
         * if you want to modify it.
         * @return The normalized version of the current Quaternion.
         * @see Quaternion::normalize()
         */
        [[nodiscard]] Quaternion normalized() const;

        /**
         * When normalized, a quaternion keeps the same rotation, but its
         * magnitude is 1.0.
         *
         * As a rotation Quaternion always has a length of 1, this function is
         * mainly used to fix floating-point errors.
         *
         * This method modifies the current Quaternion. Use normalized() if you
         * don't want to modify it.
         * @return The normalized version of the current Quaternion.
         * @see Quaternion::normalized()
         * @i
         */
        Quaternion &normalize();

        /**
         * Converts an input Euler angle rotation specified as three doubles to
         * a Quaternion.
         * @param x Rotation in degrees around the X axis
         * @param y Rotation in degrees around the Y axis
         * @param z Rotation in degrees around the Z axis
         * @return A Quaternion converted from an Euler angle rotation.
         */
        static Quaternion fromEuler(double x, double y, double z);


        /**
         * The identity Quaternion means zero rotation.
         * It is mainly used for a default rotation, to reset the rotation,
         * or as a starting point for calculations.
         * @return The identity Quaternion.
         */
        static Quaternion identity();
    private:
        double _w;
        double _x;
        double _y;
        double _z;
    };
} // Maths

#endif
