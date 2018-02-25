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

typedef HalfFp HalfFp_Sign;
typedef int HalfFp_Fraction;
typedef int HalfFp_Exponent;
/* }}} */

/* enum definitions by typedef{{{ */
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
extern const HalfFp_Exponent HalfFp_EXPONENT_BIAS;
/* extern const HalfFp_Exponent HalfFp_EXPONENT_MAX; */
/* extern const HalfFp_Exponent HalfFp_EXPONENT_MIN; */
extern const int HalfFp_FRACTION_BITS;
extern const int HalfFp_EXPONENT_BITS;
extern const HalfFp_Sign HalfFp_Sign_PLUS;
extern const HalfFp_Sign HalfFp_Sign_MINUS;

/* }}} */

/* function prototypes {{{ */
void HalfFp_Create(void);
void HalfFp_Destroy(void);

HalfFp HalfFp_SetSign(HalfFp source, HalfFp_Sign sign);
HalfFp_Sign HalfFp_GetSign(HalfFp source);
HalfFp HalfFp_SetExponent(HalfFp source, HalfFp_Exponent exponent);
HalfFp_Exponent HalfFp_GetExponent(HalfFp source);
HalfFp HalfFp_SetFraction(HalfFp source, HalfFp_Fraction fraction);
HalfFp_Fraction HalfFp_GetFraction(HalfFp source);
HalfFp HalfFp_FromFloat(float source);
HalfFp HalfFp_Normalize(HalfFp source);
unsigned int HalfFp_Nlz(HalfFp source);
float HalfFp_ToFloat(HalfFp source);
/* }}} */

/* inline functions {{{ */
/* }}} */

#ifdef __cplusplus
}
#endif

#endif /* HALFFP_H */
/** @} */
