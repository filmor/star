#ifndef STAR_MATH_HPP
#define STAR_MATH_HPP

#include <boost/numeric/ublas/vector.hpp>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/math/quaternion.hpp>

namespace star
{

    typedef double scalar;

    typedef boost::math::quaternion<scalar> quaternion;

    typedef boost::numeric::ublas::bounded_vector<scalar, 3> vector;

    struct zero_vector : public boost::numeric::ublas::zero_vector<scalar>
    {
        zero_vector () : boost::numeric::ublas::zero_vector<scalar> (3) {}
    };

    struct identity_matrix : public boost::numeric::ublas::identity_matrix<scalar>
    {
        identity_matrix () : boost::numeric::ublas::identity_matrix<scalar> (4) {}
    };

    typedef boost::numeric::ublas::bounded_matrix<scalar, 4, 4,
                                                boost::numeric::ublas::column_major
                                                >
        matrix;

    using boost::numeric::ublas::prod;

    template <typename Vector>
    matrix translation_from_vector (Vector const& v)
    {
        matrix res = identity_matrix ();
        res(0, 3) = v[0];
        res(1, 3) = v[1];
        res(2, 3) = v[2];
        return res;
    }

    inline matrix rotation_from_quaternion (quaternion q)
    {
        using namespace boost;

        scalar const& w = q.R_component_1 ();
        scalar const& x = q.R_component_2 ();
        scalar const& y = q.R_component_3 ();
        scalar const& z = q.R_component_4 ();

        matrix res;

        res(0, 0) = 1 -  2. * (y*y + z*z);
        res(0, 1) = 2. * (x*y - w*z);
        res(0, 2) = 2. * (w*y + x*z);

        res(1, 0) = 2. * (w*z + x*y);
        res(1, 1) = 1. - 2. * (x*x + z*z);
        res(1, 2) = 2. * (y*z - w*x);
        
        res(2, 0) = 2. * (x*z - w*y);
        res(2, 1) = 2. * (w*x + y*z);
        res(2, 2) = 1. - 2. * (x*x + y*y);

        return res;
    }

}

#endif
