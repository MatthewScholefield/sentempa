#pragma once

#include "Vec.inl"

template<typename T>
class Vec2 {
public:
    CREATE_CONSTRUCTORS(2);

    CREATE_ALL_OPERATORS(2);

    CREATE_CAST_FN(2);

    CREATE_DIST_FNS(2);

    CREATE_VOLUME_FN(2);

    CREATE_ABS_FN(2);

    CREATE_MIN_MAX_FN(2);

    CREATE_RAND_FN(2);

    CREATE_MAG_FN(2);

    CREATE_DOT_FN(2);

    T x, y;
};

template<typename T>
class Vec3 {
public:
    CREATE_ALL_OPERATORS(3);
    CREATE_CONSTRUCTORS(3);

    CREATE_CAST_FN(3);

    CREATE_DIST_FNS(3);

    CREATE_VOLUME_FN(3);

    CREATE_ABS_FN(3);

    CREATE_MIN_MAX_FN(3);

    CREATE_RAND_FN(3);

    CREATE_MAG_FN(3);

    CREATE_DOT_FN(3);

    CREATE_CROSS_FN(3);

    T x, y, z;
};

CREATE_ALIAS(u, unsigned int);
CREATE_ALIAS(i, int);
CREATE_ALIAS(f, float);
CREATE_ALIAS(d, double);
