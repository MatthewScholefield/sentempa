/*
 * Copyright (C) 2016 Matthew D. Scholefield
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

#include <cmath>
#include <algorithm>

// TODO: Lighten up on the macro hackery
#define _TYPE_VEC_2 Vec2<T>
#define _TYPE_VEC_3 Vec3<T>

#define _OP_UNIT(OP, TN, Z) TN operator OP()const{TN r(*this);r.x=OP x;r.y=OP y;Z;return r;}
#define _OP_UNIT_Z_2(OP)
#define _OP_UNIT_Z_3(OP) r.z=OP z
#define OP_UNIT(OP, N) _OP_UNIT(OP,_TYPE_VEC_##N,_OP_UNIT_Z_##N(OP))

#define _OP_REF(OP, TN, Z1, Z2) TN&operator OP(const TN&o){x OP o.x;y OP o.y;Z1;return*this;}TN&operator OP(const T o){x OP o;y OP o;Z2;return*this;}
#define _OP_REF_Z1_2(OP)
#define _OP_REF_Z2_2(OP)
#define _OP_REF_Z1_3(OP) z OP o.z
#define _OP_REF_Z2_3(OP) z OP o
#define OP_REF(OP, N) _OP_REF(OP,_TYPE_VEC_##N,_OP_REF_Z1_##N(OP),_OP_REF_Z2_##N(OP))

#define _OP_RVAL(OP, TN) TN operator OP(const TN&o)const{TN r(*this);r OP##=o;return r;}TN operator OP(const T o)const{TN r(*this);r OP##=o;return r;}
#define OP_RVAL(OP, N) _OP_RVAL(OP,_TYPE_VEC_##N)

#define OP_ARITH(OP, N) OP_REF(OP##=,N)OP_RVAL(OP,N)

#define CREATE_ALL_OPERATORS(N) \
OP_UNIT(!, N) \
OP_UNIT(+, N) \
OP_REF(=, N) \
OP_UNIT(-, N) \
OP_ARITH(+, N) \
OP_ARITH(-, N) \
OP_ARITH(*, N) \
OP_ARITH(/, N) \
OP_ARITH(%, N) \
OP_ARITH(&, N) \
OP_ARITH(^, N) \
OP_ARITH(|, N)

#define CAST_FN(TS, Z) template<typename U>TS<U>cast()const{TS<U>r((U)x,(U)y Z);return r;}

#define COMMA ,
#define CAST_FN_2 CAST_FN(Vec2,)
#define CAST_FN_3 CAST_FN(Vec3,COMMA(U)z)

#define CREATE_CAST_FN(N) CAST_FN_##N

#define _CONSTRUCTORS(TN, Z1, Z2, Z3) TN(const T x,const T y Z1):x(x),y(y)Z2{}TN():x(0),y(0)Z3{}
#define _CONSTRUCTORS_Z1_2
#define _CONSTRUCTORS_Z2_2
#define _CONSTRUCTORS_Z3_2
#define _CONSTRUCTORS_Z1_3 ,const T z
#define _CONSTRUCTORS_Z2_3 ,z(z)
#define _CONSTRUCTORS_Z3_3 ,z(0)
#define CREATE_CONSTRUCTORS(N) _CONSTRUCTORS(_TYPE_VEC_##N,_CONSTRUCTORS_Z1_##N,_CONSTRUCTORS_Z2_##N,_CONSTRUCTORS_Z3_##N)

#define _DIST_FNS(TN, Z) T dist2(const TN&o)const{return(x-o.x)*(x-o.x)+(y-o.y)*(y-o.y)Z;}T dist(const TN&o)const{return std::sqrt(dist2(o));}
#define _DIST_FNS_Z_2
#define _DIST_FNS_Z_3 +(z-o.z)*(z-o.z);
#define CREATE_DIST_FNS(N) _DIST_FNS(_TYPE_VEC_##N,_DIST_FNS_Z_##N)

#define _VOLUME_FN(Z) T volume()const{return std::abs(x*y Z);}
#define _VOLUME_FN_Z_2
#define _VOLUME_FN_Z_3 *z
#define CREATE_VOLUME_FN(N) _VOLUME_FN(_VOLUME_FN_Z_##N)

#define _ABS_FN(TN, Z) TN abs()const{return{std::abs(x),std::abs(y)Z};}
#define _ABS_FN_Z_2
#define _ABS_FN_Z_3 ,std::abs(z)
#define CREATE_ABS_FN(N) _ABS_FN(_TYPE_VEC_##N,_ABS_FN_Z_##N)

#define _MIN_MAX_FN(TN, Z1, Z2, Z3, Z4) T min()const{return std::min(x,Z1);}T max()const{return std::max(x,Z2);}TN min(const T v)const{return {std::min(x,v),std::min(y,v)Z3};}TN max(const T v)const{return {std::max(x,v),std::max(y,v)Z4};}
#define _MIN_MAX_FN_Z1_2 y
#define _MIN_MAX_FN_Z2_2 y
#define _MIN_MAX_FN_Z3_2
#define _MIN_MAX_FN_Z4_2
#define _MIN_MAX_FN_Z1_3 std::min(y,z)
#define _MIN_MAX_FN_Z2_3 std::max(y,z)
#define _MIN_MAX_FN_Z3_3 ,std::min(z,v)
#define _MIN_MAX_FN_Z4_3 ,std::max(z,v)
#define CREATE_MIN_MAX_FN(N) _MIN_MAX_FN(_TYPE_VEC_##N,_MIN_MAX_FN_Z1_##N,_MIN_MAX_FN_Z2_##N,_MIN_MAX_FN_Z3_##N,_MIN_MAX_FN_Z4_##N)

#define _RAND_FN(TN, Z) TN rand()const{return {std::rand()%x,std::rand()%y Z};}
#define _RAND_FN_Z_2
#define _RAND_FN_Z_3 ,std::rand()%z
#define CREATE_RAND_FN(N) _RAND_FN(_TYPE_VEC_##N,_RAND_FN_Z_##N)

#define _MAG_FN(Z) T mag()const{return sqrtf(x*x+y*y Z);}
#define _MAG_FN_Z_2
#define _MAG_FN_Z_3 +z*z
#define CREATE_MAG_FN(N) _MAG_FN(_MAG_FN_Z_##N)

#define _DOT_FN(TN, Z) T dotP(const TN&o)const{return x*o.x+y*o.y Z;}
#define _DOT_FN_Z_2
#define _DOT_FN_Z_3 +z*o.z
#define CREATE_DOT_FN(N) _DOT_FN(_TYPE_VEC_##N,_DOT_FN_Z_##N)

#define _CROSS_FN_3(TN) TN crossP(const TN&o)const{return {y*o.z-z*o.y,z*o.x-x*o.z,x*o.y-y*o.x};}
#define CREATE_CROSS_FN(N) _CROSS_FN_##N(_TYPE_VEC_##N)

#define _CREATE_ALIAS(ST, T, N) using Vec##N##ST=Vec##N<T>;using cVec##N##ST=const Vec##N<T>;
#define CREATE_ALIAS(ST, T) _CREATE_ALIAS(ST,T,2)_CREATE_ALIAS(ST,T,3)
