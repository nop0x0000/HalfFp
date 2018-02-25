/**
 * @file
 * TODO: Write file desctiption here.
 *
 * @addtogroup HalfFp
 * @{
 */

/* includes(system) {{{ */
/* }}} */

/* includes(user) {{{ */
#include "HalfFp.h"
/* }}} */

/* define macros (file scope) {{{ */
/* }}} */

/* define function macros (file scope) {{{ */
/* }}} */

/* typedefs (file scope) {{{ */
#if USHRT_MAX == 0xffffffff
typedef unsigned short FloatBits;
#elif UINT_MAX == 0xffffffff
typedef unsigned int FloatBits;
#elif ULONG_MAX == 0xffffffff
typedef unsigned long FloatBits;
#else
#error Could not find 4 byte basic type.
#endif

typedef int FloatExponent;
/* }}} */

/* enum definitions (file scope) {{{ */
/* }}} */

/* struct / union definitions (file scope) {{{ */
/* }}} */

/* static variables declarations (file scope) {{{ */
static const FloatBits FLOAT_SIGN_MASK = 0x80000000;
static const int FLOAT_FRACTION_BITS = 23;
static const int FLOAT_EXPONENT_BIAS = 127;
/* }}} */

/* static funcsion prototypes {{{ */
/* }}} */

/* variable declarations {{{ */
const HalfFp HalfFp_SIGN_MASK = 0x8000;
const HalfFp HalfFp_EXPONENT_MASK = 0x7c00;
const HalfFp HalfFp_FRACTION_MASK = 0x03ff;
const HalfFp_Exponent HalfFp_EXPONENT_BIAS = 15;
/* const HalfFp_Exponent HalfFp_EXPONENT_MAX = 0x1e; */
/* const HalfFp_Exponent HalfFp_EXPONENT_MIN = 1;    */
const int HalfFp_FRACTION_BITS = 10;
/* const int HalfFp_EXPONENT_BITS = 5; */
const HalfFp_Sign HalfFp_Sign_PLUS = 0;
const HalfFp_Sign HalfFp_Sign_MINUS = 0x8000;
/* }}} */

/* functions {{{ */
void HalfFp_Create(void)
{
}

void HalfFp_Destroy(void)
{
}

HalfFp HalfFp_SetSign(HalfFp source, HalfFp_Sign sign)
{
    /* SetError(HalfFp_Error_IgnoreSignEnum); */ /* TODO: Implement this when implement the error notification mechanism.*/
    return (HalfFp)((source & ~HalfFp_SIGN_MASK) | sign);
}

HalfFp_Sign HalfFp_GetSign(HalfFp source)
{
    return (HalfFp_Sign)(source & 0x8000);
}

HalfFp HalfFp_SetExponent(HalfFp source, HalfFp_Exponent exponent)
{
    return (HalfFp)((source & ~HalfFp_EXPONENT_MASK) | (exponent << HalfFp_FRACTION_BITS));
}

HalfFp_Exponent HalfFp_GetExponent(HalfFp source)
{
    return (HalfFp_Exponent)((source & HalfFp_EXPONENT_MASK) >> HalfFp_FRACTION_BITS);
}

HalfFp HalfFp_SetFraction(HalfFp source, HalfFp_Fraction fraction)
{
    return (HalfFp)((source & ~HalfFp_FRACTION_MASK) | (fraction & HalfFp_FRACTION_MASK));
}

HalfFp_Fraction HalfFp_GetFraction(HalfFp source)
{
    return (HalfFp_Fraction)(source & HalfFp_FRACTION_MASK);
}

HalfFp HalfFp_FromFloat(float source)
{
    HalfFp result = 0x0000;
    FloatExponent floatExponent;
    HalfFp_Exponent halfExponent;
    FloatBits sourceBits = (*(FloatBits*)&source);

    result = HalfFp_SetSign(result, (source >= 0) ? (HalfFp_Sign_PLUS):(HalfFp_Sign_MINUS));

    result = result | (HalfFp)(((sourceBits + (FloatBits)(1 << (FLOAT_FRACTION_BITS - HalfFp_FRACTION_BITS - 1))) >> (FLOAT_FRACTION_BITS - HalfFp_FRACTION_BITS)) & HalfFp_FRACTION_MASK);

    floatExponent = (FloatExponent)((sourceBits & ~FLOAT_SIGN_MASK) >> (FLOAT_FRACTION_BITS));
    halfExponent = (HalfFp_Exponent)((floatExponent + HalfFp_EXPONENT_BIAS) - FLOAT_EXPONENT_BIAS); /* TODO : Add checking out of range here. */
    result = HalfFp_SetExponent(result, halfExponent);
    /* result = result | ((((sourceBits & ~FLOAT_SIGN_MASK) >> (FLOAT_FRACTION_BITS - HalfFp_FRACTION_BITS)) - ((FloatBits)(FLOAT_EXPONENT_BIAS - HalfFp_EXPONENT_BIAS) * ((1<<HalfFp_FRACTION_BITS) - 1))) & HalfFp_EXPONENT_MASK); */

    return result;
}

float HalfFp_ToFloat(HalfFp source)
{
    FloatBits result = 0;
    result = result | (FloatBits)((HalfFp_GetSign(source) == HalfFp_Sign_PLUS) ? (0) : (FLOAT_SIGN_MASK));
    result = result | (FloatBits)((HalfFp_GetExponent(source) + (FLOAT_EXPONENT_BIAS - HalfFp_EXPONENT_BIAS)) << FLOAT_FRACTION_BITS);
    result = result | (FloatBits)(HalfFp_GetFraction(source) << (FLOAT_FRACTION_BITS - HalfFp_FRACTION_BITS));

    return *(float*)(&result);
}

/**
 * Calculating NLZ by binary search.
 */
unsigned int HalfFp_Nlz(HalfFp source)
{
    unsigned int i = 8;
    unsigned int j = 0;
    unsigned int result = 0;
    const HalfFp mask = 0xff00;
    while(i > 0)
    {
        j = i;
        i >>= 1;
        if (source & mask)
        {
            result += j;
            source = (HalfFp)(source >> i);
        }
        else
        {
            source = (HalfFp)(source << i);
        }
    }
    return 15 - result;
}
/* }}} */

/** @} */
