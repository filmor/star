#ifndef STAR_MATH_HPP
#define STAR_MATH_HPP

#include <boost/numeric/ublas/vector.hpp>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/math/quaternion.hpp>

namespace star
{

    /// Scalar data type. As it is likely that OpenGL3 won't have support for double
    /// this can be changed here easily.
    typedef double scalar;

    /// Quaternion type, used for rotations.
    typedef boost::math::quaternion<scalar> quaternion;

    /// Vector type (in the mathematical sense), used for translations.
    typedef boost::numeric::ublas::bounded_vector<scalar, 3> vector;

    /// Zero vector type, default translation.
    struct zero_vector : public boost::numeric::ublas::zero_vector<scalar>
    {
        zero_vector () : boost::numeric::ublas::zero_vector<scalar> (3) {}
    };

    /// Identity matrix type.
    struct identity_matrix : public boost::numeric::ublas::identity_matrix<scalar>
    {
        identity_matrix () : boost::numeric::ublas::identity_matrix<scalar> (4) {}
    };

    /// Matrix type (4x4, column major), to be used with OpenGL.
    typedef boost::numeric::ublas::bounded_matrix<scalar, 4, 4,
                                                boost::numeric::ublas::column_major
                                                >
        matrix;

    /// Matrix product function.
    using boost::numeric::ublas::prod;

    /**
     * Function to produce a translation matrix from a vector.
     *
     * \param v Translation vector.
     * \return Translation matrix.
     */
    template <typename Vector>
    matrix translation_from_vector (Vector const& v)
    {
        matrix res = identity_matrix ();
        res(0, 3) = v[0];
        res(1, 3) = v[1];
        res(2, 3) = v[2];
        return res;
    }

    /// Returns a rotation matrix from a quaternion.
    inline matrix rotation_from_quaternion (quaternion q)
    {
        using namespace boost;

        scalar const& w = q.R_component_1 ();
        scalar const& x = q.R_component_2 ();
        scalar const& y = q.R_component_3 ();
        scalar const& z = q.R_component_4 ();

        matrix res = identity_matrix ();

        res(0, 0) -= 2. * (y*y + z*z);
        res(0, 1) =  2. * (x*y - w*z);
        res(0, 2) =  2. * (w*y + x*z);

        res(1, 0) =  2. * (w*z + x*y);
        res(1, 1) -= 2. * (x*x + z*z);
        res(1, 2) =  2. * (y*z - w*x);
        
        res(2, 0) =  2. * (x*z - w*y);
        res(2, 1) =  2. * (w*x + y*z);
        res(2, 2) -= 2. * (x*x + y*y);

        return res;
    }

    /// Create an orthogonal projection matrix
    inline matrix orthogonal_projection (scalar right, scalar left, scalar bottom,
                                         scalar top, scalar near_val, scalar far_val)
    {
        matrix res = identity_matrix ();

        res(0, 0) = right - left;
        res(0, 3) = -res(0, 0);
        res(1, 1) = top - bottom;
        res(1, 3) = -res(1, 1);
        res(2, 2) = far_val - near_val;
        res(2, 3) = -res(2, 2);

        return res;
    }

}

#endif
