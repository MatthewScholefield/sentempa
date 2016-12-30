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

#define _OP_RVAL(OP, TN) TN operator OP(const TN&o)const{TN r(o);r OP##= *this;return r;}TN operator OP(const T o)const{TN r(*this);r OP##=o;return r;}
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

#define CAST_FN(TS,Z) template<typename U>TS<U>cast()const{TS<U>r((U)x,(U)y Z);return r;}

#define COMMA ,
#define CAST_FN_2 CAST_FN(Vec2,)
#define CAST_FN_3 CAST_FN(Vec3,COMMA(U)z)

#define CREATE_CAST_FN(N) CAST_FN_##N

#define _CONSTRUCTOR(TN, Z1, Z2) TN(const T x,const T y Z1):x(x),y(y)Z2{}
#define _CONSTRUCTOR_Z1_2
#define _CONSTRUCTOR_Z2_2
#define _CONSTRUCTOR_Z1_3 ,const T z
#define _CONSTRUCTOR_Z2_3 ,z(z)
#define CREATE_CONSTRUCTOR(N) _CONSTRUCTOR(_TYPE_VEC_##N,_CONSTRUCTOR_Z1_##N,_CONSTRUCTOR_Z2_##N)
