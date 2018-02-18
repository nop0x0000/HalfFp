/* Test list
 * o 符号を設定できる
 * o 符号を取得できる
 * o 指数部を設定できる
 * o 指数部を取得できる
 * o オフセットされた指数部を設定できる
 * o オフセットされた指数部を取得できる
 * o 仮数部を設定できる
 * - ビットパターン生成用のユーティリティ関数を作成する
 * - HalfFpの定数のテストを追加する
 * - 仮数部を取得できる
 * - floatから変換できる
 * - floatへ変換できる
 * - 加算が計算できる
 * - 減算が計算できる
 * - 符号反転ができる
 * - 同値判定ができる
 * - 大小比較ができる
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
    HalfFp halfFp = 0;
    HalfFp halfFpMinus = HalfFp_SetSign(halfFp, HalfFp_Sign_Minus);
    HalfFp halfFpPlus = HalfFp_SetSign(halfFpMinus, HalfFp_Sign_Plus);
    CHECK_EQUAL(0x8000, halfFpMinus);
    CHECK_EQUAL(0x0000, halfFpPlus);
}

TEST(HalfFp, GetSignBit)
{
    HalfFp halfFp = 0;
    HalfFp_Sign sign;

    HalfFp halfFpMinus = HalfFp_SetSign(halfFp, HalfFp_Sign_Minus);
    sign = HalfFp_GetSign(halfFpMinus);
    CHECK_EQUAL(HalfFp_Sign_Minus, sign);

    HalfFp halfFpPlus = HalfFp_SetSign(halfFpMinus, HalfFp_Sign_Plus);
    sign = HalfFp_GetSign(halfFpPlus);
    CHECK_EQUAL(HalfFp_Sign_Plus, sign);
}

TEST(HalfFp, SetExponent)
{
    HalfFp halfFp = 0xffff;
    HalfFp halfFpUpdated = HalfFp_SetExponent(halfFp, HalfFp_EXPONENT_MAX);
    CHECK_EQUAL(HalfFp_EXPONENT_MAX, ((halfFpUpdated & ~HalfFp_SIGN_MASK)>>HalfFp_FRACTION_BITS) - HalfFp_EXPONENT_BIAS);

    HalfFp halfFpUpdated2 = HalfFp_SetExponent(halfFp, HalfFp_EXPONENT_MIN);
    CHECK_EQUAL(HalfFp_EXPONENT_MIN, ((halfFpUpdated2 & 0x7fff)>>HalfFp_FRACTION_BITS) - HalfFp_EXPONENT_BIAS);
}

TEST(HalfFp, GetExponent)
{
    HalfFp halfFp = 0;
    HalfFp halfFpUpdated = HalfFp_SetExponent(halfFp, 15);
    signed char exponent = HalfFp_GetExponent(halfFpUpdated);

    CHECK_EQUAL(15, exponent);
}

TEST(HalfFp, SetOffsetExponent)
{
    HalfFp halfFp = 0xffff;
    HalfFp halfFpUpdated = HalfFp_SetOffsetExponent(halfFp, HalfFp_OFFSET_EXPONENT_MAX);
    CHECK_EQUAL(HalfFp_OFFSET_EXPONENT_MAX, (halfFpUpdated & ~ HalfFp_SIGN_MASK)>>(HalfFp_FRACTION_BITS));

    HalfFp halfFpUpdated2 = HalfFp_SetOffsetExponent(halfFp, HalfFp_OFFSET_EXPONENT_MIN);
    CHECK_EQUAL(HalfFp_OFFSET_EXPONENT_MIN, (halfFpUpdated2 & ~ HalfFp_SIGN_MASK)>>(HalfFp_FRACTION_BITS));
}

TEST(HalfFp, GetOffsetExponent)
{
    HalfFp halfFp = 0;
    HalfFp halfFpUpdated = HalfFp_SetOffsetExponent(halfFp, HalfFp_OFFSET_EXPONENT_MAX);
    unsigned char exponent = HalfFp_GetOffsetExponent(halfFpUpdated);

    CHECK_EQUAL(HalfFp_OFFSET_EXPONENT_MAX, exponent);
}

TEST(HalfFp, SetFraction)
{
    HalfFp halfFp = 0xffff;
    HalfFp halfFpUpdated = HalfFp_SetFraction(halfFp, 0x03ff);
    unsigned int fraction = halfFpUpdated & HalfFp_FRACTION_MASK;
    CHECK_EQUAL(0x03ff, fraction);

    HalfFp halfFpUpdated2 = HalfFp_SetFraction(halfFp, 0x0000);
    unsigned int fraction2 = halfFpUpdated2 & HalfFp_FRACTION_MASK;
    CHECK_EQUAL(0x0000, fraction2);
}

/*
IGNORE_TEST(HalfFp, FloatToHalfFp)
{
    float fVal = 0.2;
    HalfFp halfFp = HalfFp_FromFlaot(fVal);
    int sign = HalfFp_GetSign(halfFp);
    int exponent = HalfFp_GetExponent(halfFp);
    int fraction = halfFp_GetFraction(halfFp);
    CHECK_EQUAL(0, sign);
    CHECK_EQUAL(0, exponent);
    CHECK_EQUAL(0, fraction);
}
*/
