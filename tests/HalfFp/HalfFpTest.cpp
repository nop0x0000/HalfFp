/* Test list
 * o 符号を設定できる(SetSignBit)
 * o 符号を取得できる(GetSignBit)
 * o 指数部を設定できる(SetExponent)
 * o 指数部を取得できる(GetExponent)
 * o 仮数部を設定できる(SetFraction)
 * o 仮数部を取得できる(GetFraction)
 * o floatから変換できる(FloatToHalfFp)
 * - floatへ変換できる
 * - 正規化ができる
 * - 同値判定ができる
 * - 符号反転ができる
 * - 大小比較ができる
 * - 加算が計算できる
 * - 減算が計算できる
 * - 乗算が計算できる
 * - 除算が計算できる
 * - オーバーフローが検知できる
 * - アンダーフローが検知できる
 * - ゼロ除算が検知できる
 * - 情報落ちが検知できる
 * - 桁落ちが検知できる
 * - 累乗が計算できる
 * - 累乗根が計算できる
 */
extern "C"
{
#include "HalfFp.h"
}

#include "CppUTest/TestHarness.h"

TEST_GROUP(HalfFp)
{
    void setup()
    {
      HalfFp_Create();
    }

    void teardown()
    {
       HalfFp_Destroy();
    }
};

IGNORE_TEST(HalfFp, Create)
{
    FAIL("Start here");
}

TEST(HalfFp, SetSignBit)
{
    HalfFp halfFp = 0x5555;

    HalfFp halfFpMinus = HalfFp_SetSign(halfFp, HalfFp_Sign_MINUS);
    BITS_EQUAL(HalfFp_Sign_MINUS, halfFpMinus, HalfFp_SIGN_MASK);
    BITS_EQUAL(halfFp, halfFpMinus, ~HalfFp_SIGN_MASK);

    HalfFp halfFpPlus = HalfFp_SetSign(halfFpMinus, HalfFp_Sign_PLUS);
    BITS_EQUAL(HalfFp_Sign_PLUS, halfFpPlus, HalfFp_SIGN_MASK);
    BITS_EQUAL(halfFpMinus, halfFpPlus, ~HalfFp_SIGN_MASK);
}

TEST(HalfFp, GetSignBit)
{
    HalfFp halfFp = 0xffff;
    HalfFp_Sign sign;

    HalfFp halfFpMinus = HalfFp_SetSign(halfFp, HalfFp_Sign_MINUS);
    sign = HalfFp_GetSign(halfFpMinus);
    CHECK_EQUAL(HalfFp_Sign_MINUS, sign);

    HalfFp halfFp2 = 0xaaaa;
    HalfFp halfFpPlus = HalfFp_SetSign(halfFp2, HalfFp_Sign_PLUS);
    sign = HalfFp_GetSign(halfFpPlus);
    CHECK_EQUAL(HalfFp_Sign_PLUS, sign);
}

TEST(HalfFp, SetExponent)
{
    HalfFp halfFp = 0xaaaa;
    HalfFp halfFpUpdated = HalfFp_SetExponent(halfFp, 0x15);
    BITS_EQUAL((0x15<<HalfFp_FRACTION_BITS), halfFpUpdated, HalfFp_EXPONENT_MASK);
    BITS_EQUAL(halfFp, halfFpUpdated ,~HalfFp_EXPONENT_MASK);

    HalfFp halfFp2 = 0x5555;
    HalfFp halfFpUpdated2 = HalfFp_SetExponent(halfFp2, 0x0a);
    BITS_EQUAL((0x0a<<HalfFp_FRACTION_BITS), halfFpUpdated2, HalfFp_EXPONENT_MASK);
    BITS_EQUAL(halfFp, halfFpUpdated ,~HalfFp_EXPONENT_MASK);
}

TEST(HalfFp, GetExponent)
{
    HalfFp halfFp = 0xffff;
    HalfFp halfFpUpdated = HalfFp_SetExponent(halfFp, 0x1a);
    int exponent = HalfFp_GetExponent(halfFpUpdated);

    CHECK_EQUAL(0x1a, exponent);
}

TEST(HalfFp, SetFraction)
{
    HalfFp halfFp = 0xaaaa;
    HalfFp halfFpUpdated = HalfFp_SetFraction(halfFp, 0x03ff);
    BITS_EQUAL(0x03ff, halfFpUpdated, HalfFp_FRACTION_MASK);
    BITS_EQUAL(halfFp, halfFpUpdated, ~HalfFp_FRACTION_MASK);


    HalfFp halfFp2 = 0x5555;
    HalfFp halfFpUpdated2 = HalfFp_SetFraction(halfFp2, 0x0155);
    BITS_EQUAL(0x0155, halfFpUpdated2, HalfFp_FRACTION_MASK);
    BITS_EQUAL(halfFp2, halfFpUpdated2, ~HalfFp_FRACTION_MASK);
}

TEST(HalfFp, GetFraction)
{
    HalfFp halfFp = 0xffff;
    HalfFp halfFpUpdated = HalfFp_SetFraction(halfFp, 0x02aa);
    CHECK_EQUAL(0x02aa, HalfFp_GetFraction(halfFpUpdated));
}

TEST(HalfFp, FloatToHalfFp)
{
    float fVal = -0.2f;
    HalfFp halfFp = HalfFp_FromFloat(fVal);

    HalfFp_Sign sign = HalfFp_GetSign(halfFp);
    HalfFp_Exponent exponent = HalfFp_GetExponent(halfFp);
    HalfFp_Fraction fraction = HalfFp_GetFraction(halfFp);

    CHECK_EQUAL(HalfFp_Sign_MINUS, sign);
    CHECK_EQUAL(-3 + HalfFp_EXPONENT_BIAS, exponent);
    CHECK_EQUAL(614, fraction);
}

TEST(HalfFp, HalfFpToFloat)
{
    /* float fVal = (float)(-0.1 / i); */
    float fVal = 6.5504e+4f;
    /* HalfFp halfFp = HalfFp_FromFloat(fVal); */
    HalfFp halfFp = 0x7bff;
    float fVal2 = HalfFp_ToFloat(halfFp);

    DOUBLES_EQUAL(fVal, fVal2, 1.0/(1<<HalfFp_FRACTION_BITS));

}

/* TEST(HalfFp, FromENotation)                                                */
/* {                                                                          */
/*     HalfFp halfFp = 0;                                                     */
/*     HalfFp normalized = 0;                                                 */

/*     HalfFp_FromENotation(-1.23, 9);                                        */

/*     CHECK_EQUAL(HalfFp_Sign_MINUS, HalfFp_GetSign(normalized));            */
/*     CHECK_EQUAL(4 + HalfFp_EXPONENT_BIAS, HalfFp_GetExponent(normalized)); */
/*     CHECK_EQUAL(0x154, HalfFp_GetFraction(normalized));                    */
/* }                                                                          */

TEST(HalfFp, Nlz)
{
    CHECK_EQUAL( 0, HalfFp_Nlz(0xffff));
    CHECK_EQUAL( 1, HalfFp_Nlz(0xffff>>1));
    CHECK_EQUAL( 2, HalfFp_Nlz(0xffff>>2));
    CHECK_EQUAL( 3, HalfFp_Nlz(0xffff>>3));
    CHECK_EQUAL( 4, HalfFp_Nlz(0xffff>>4));
    CHECK_EQUAL( 5, HalfFp_Nlz(0xffff>>5));
    CHECK_EQUAL( 6, HalfFp_Nlz(0xffff>>6));
    CHECK_EQUAL( 7, HalfFp_Nlz(0xffff>>7));
    CHECK_EQUAL( 8, HalfFp_Nlz(0xffff>>8));
    CHECK_EQUAL( 9, HalfFp_Nlz(0xffff>>9));
    CHECK_EQUAL(10, HalfFp_Nlz(0xffff>>10));
    CHECK_EQUAL(11, HalfFp_Nlz(0xffff>>11));
    CHECK_EQUAL(12, HalfFp_Nlz(0xffff>>12));
    CHECK_EQUAL(13, HalfFp_Nlz(0xffff>>13));
    CHECK_EQUAL(14, HalfFp_Nlz(0xffff>>14));
    CHECK_EQUAL(15, HalfFp_Nlz(0xffff>>15));
}

