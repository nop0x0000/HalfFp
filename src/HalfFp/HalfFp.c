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
/* }}} */

/* enum definitions (file scope) {{{ */
/* }}} */

/* struct / union definitions (file scope) {{{ */
/* }}} */

/* static variables declarations (file scope) {{{ */
/* }}} */

/* static funcsion prototypes {{{ */
/* }}} */

/* variable declarations {{{ */
const unsigned char HalfFp_FRACTION_BITS = 10;
const unsigned char HalfFp_EXPONENT_BITS = 5;
const HalfFp HalfFp_SIGN_MASK = 0x8000;
const HalfFp HalfFp_EXPONENT_MASK = 0x7c00;
const HalfFp HalfFp_FRACTION_MASK = 0x03ff;
const unsigned char HalfFp_EXPONENT_BIAS = 15;
const signed char HalfFp_EXPONENT_MAX = 15;
const signed char HalfFp_EXPONENT_MIN = -14;
const signed char HalfFp_OFFSET_EXPONENT_MAX = 0x1e;
const signed char HalfFp_OFFSET_EXPONENT_MIN = 1;
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
    return (HalfFp)((source & ~HalfFp_SIGN_MASK) | (HalfFp)sign);
}

HalfFp_Sign HalfFp_GetSign(HalfFp source)
{
    return (HalfFp_Sign)(source & 0x8000);
}

HalfFp HalfFp_SetExponent(HalfFp source, signed char exponent)
{
    /* TODO * Implement the error notification mechanism here. */
    HalfFp exponentProcessed = (HalfFp)((exponent + HalfFp_EXPONENT_BIAS) << HalfFp_FRACTION_BITS);
    return (HalfFp)((source & ~HalfFp_EXPONENT_MASK) | exponentProcessed);
}

signed char HalfFp_GetExponent(HalfFp source)
{
    return (signed char)(((source & HalfFp_SIGN_MASK) >> HalfFp_FRACTION_BITS) + HalfFp_EXPONENT_BIAS);
}

HalfFp HalfFp_SetOffsetExponent(HalfFp source, signed char exponent)
{
    return (HalfFp)((source & ~HalfFp_EXPONENT_MASK) | (exponent << HalfFp_FRACTION_BITS));
}

unsigned char HalfFp_GetOffsetExponent(HalfFp source)
{
    return (unsigned char)((source & HalfFp_EXPONENT_MASK) >> HalfFp_FRACTION_BITS);
}

HalfFp HalfFp_SetFraction(HalfFp source, HalfFp fraction)
{
    return (HalfFp)((source & ~HalfFp_FRACTION_MASK) | (fraction & HalfFp_FRACTION_MASK));
}

/* }}} */

/** @} */
