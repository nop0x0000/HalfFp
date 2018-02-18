/**
 * @file
 * TODO: Write file desctiption here.
 *
 * @addtogroup HalfFp
 * TODO: Write module desctiption here.
 *
 * @{
 */
#ifndef HALFFP_H
#define HALFFP_H

#ifdef __cplusplus
extern "C"
{
#endif

/* includes(system) {{{ */
#include <limits.h>
/* }}} */

/* includes(user) {{{ */
/* }}} */

/* define macros {{{ */
/* }}} */

/* define function macros {{{ */
/* }}} */

/* typedefs for basic types{{{ */
#if USHRT_MAX == 0xffff
typedef unsigned short HalfFp;
#elif UINT_MAX == 0xffff
typedef unsigned int HalfFp;
#elif ULONG_MAX == 0xffff
typedef unsigned long HalfFp;
#else
#error Could not find 2 byte basic type.
#endif

/* }}} */

/* enum definitions by typedef{{{ */
typedef enum
{
    HalfFp_Sign_Plus = 0,
    HalfFp_Sign_Minus = 0x8000
} HalfFp_Sign;

typedef enum
{
    HalfFp_Error_IgnoreSignEnum,
} HalfFp_Error;
/* }}} */

/* struct / union definitions by typedef{{{ */
/* }}} */

/* extern variable declarations{{{ */
extern const HalfFp HalfFp_SIGN_MASK;
extern const HalfFp HalfFp_EXPONENT_MASK;
extern const HalfFp HalfFp_FRACTION_MASK;
extern const unsigned char HalfFp_EXPONENT_BIAS;
extern const signed char HalfFp_EXPONENT_MAX;
extern const signed char HalfFp_EXPONENT_MIN;
extern const unsigned char HalfFp_FRACTION_BITS;
extern const unsigned char HalfFp_EXPONENT_BITS;
extern const signed char HalfFp_OFFSET_EXPONENT_MAX;
extern const signed char HalfFp_OFFSET_EXPONENT_MIN;
/* }}} */

/* function prototypes {{{ */
void HalfFp_Create(void);
void HalfFp_Destroy(void);

HalfFp      HalfFp_SetSign(HalfFp source, HalfFp_Sign sign);
HalfFp_Sign HalfFp_GetSign(HalfFp source);
HalfFp      HalfFp_SetExponent(HalfFp source, signed char exponent);
signed char HalfFp_GetExponent(HalfFp source);
HalfFp HalfFp_SetOffsetExponent(HalfFp source, signed char exponent);
unsigned char HalfFp_GetOffsetExponent(HalfFp source);
HalfFp      HalfFp_SetFraction(HalfFp source, HalfFp fraction);
/* }}} */

/* inline functions {{{ */
/* }}} */

#ifdef __cplusplus
}
#endif

#endif /* HALFFP_H */
/** @} */
