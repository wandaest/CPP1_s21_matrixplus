#include <gtest/gtest.h>

#include "../s21_matrix_oop.h"

TEST(DefaultConstructor, Test_1) {
  auto matrix = S21Matrix();
  ASSERT_EQ(matrix.GetCols(), 2);
  ASSERT_EQ(matrix.GetRows(), 2);
}

TEST(ParameterizedConstructor, Test_1) {
  auto matrix = S21Matrix(2, 3);
  ASSERT_EQ(matrix.GetCols(), 3);
  ASSERT_EQ(matrix.GetRows(), 2);
}
TEST(ParameterizedConstructor, Test_2) { ASSERT_ANY_THROW(S21Matrix(-3, -3)); }

TEST(MoveConstructor, Test_1) {
  auto matrix = S21Matrix(3, 3);
  auto matrix2 = std::move(matrix);

  ASSERT_EQ(matrix2.GetCols(), 3);
  ASSERT_EQ(matrix2.GetRows(), 3);
}

TEST(Mutator, Test_1) {
  auto matrix = S21Matrix(3, 3);
  matrix.SetCols(4);
  matrix.SetRows(4);
  ASSERT_EQ(matrix.GetCols(), 4);
  ASSERT_EQ(matrix.GetRows(), 4);
}

TEST(Determinant, Test_1) {
  S21Matrix matrix(3, 3);
  matrix(0, 0) = 1;
  matrix(0, 1) = 2;
  matrix(0, 2) = 3;
  matrix(1, 0) = 0;
  matrix(1, 1) = 4;
  matrix(1, 2) = 2;
  matrix(2, 0) = 5;
  matrix(2, 1) = 2;
  matrix(2, 2) = 1;
  EXPECT_DOUBLE_EQ(matrix.Determinant(), -40);
}
TEST(Determinant, Test_3) { ASSERT_ANY_THROW(S21Matrix(3, 4).Determinant()); }

TEST(CalcComplements, Test_1) {
  auto matrix = S21Matrix(3, 3);
  auto m1 = S21Matrix(3, 3);
  matrix(0, 0) = 9.78234;
  matrix(0, 1) = 17.3069996;
  matrix(0, 2) = -7.6309044;
  matrix(1, 0) = -47.1948324;
  matrix(1, 1) = 27.7634971;
  matrix(1, 2) = 32.8135316;
  matrix(2, 0) = 57.5462111;
  matrix(2, 1) = -58.3033974;
  matrix(2, 2) = -5.9470455;
  m1(0, 0) = 9.197938;
  m1(0, 1) = 8.4591425;
  m1(0, 2) = 6.0718781;
  m1(1, 0) = 2.8826374;
  m1(1, 1) = 2.0045357;
  m1(1, 2) = 8.2416755;
  m1(2, 0) = 4.1030337;
  m1(2, 1) = 0.2059826;
  m1(2, 2) = 5.7270029;
  S21Matrix res = m1.CalcComplements();
  ASSERT_TRUE(res == matrix);
}
TEST(CalcComplements, Test_2) {
  ASSERT_ANY_THROW(S21Matrix(3, 4).CalcComplements());
}

TEST(OperatorBrct, Test_1) {
  auto matrix = S21Matrix(2, 2);
  matrix(0, 0) = 1;
  const auto m1 = S21Matrix(matrix);

  ASSERT_EQ(m1(0, 0), 1);
}
TEST(OperatorBrct, Test_2) {
  auto matrix = S21Matrix(2, 2);
  matrix(0, 0) = 1;
  const auto m1 = S21Matrix(matrix);

  ASSERT_ANY_THROW(m1(0, 7));
}
TEST(OperatorBrct, Test_3) {
  auto matrix = S21Matrix(2, 2);
  ASSERT_ANY_THROW(matrix(0, 7));
}

TEST(OperatorPlus, Test_1) {
  auto matrix = S21Matrix(3, 3);
  auto m1 = S21Matrix(3, 4);
  ASSERT_ANY_THROW(matrix + m1);
}

TEST(OperatorMinus, Test_1) {
  auto matrix = S21Matrix(3, 3);
  auto m1 = S21Matrix(3, 4);
  ASSERT_ANY_THROW(matrix - m1);
}

TEST(Operator_Ravno, Test_1) {
  auto matrix = S21Matrix(3, 3);
  auto m1 = S21Matrix(3, 5);
  m1 = matrix;
  ASSERT_TRUE(matrix == m1);
}

TEST(OperatorMul, Test_1) {
  auto matrix = S21Matrix(3, 3);
  auto m1 = S21Matrix(5, 4);
  ASSERT_ANY_THROW(matrix * m1);
}

TEST(OperatotMulNumber, Test_1) {
  auto matrix = S21Matrix(3, 3);
  auto res = S21Matrix(3, 3);
  matrix(0, 0) = 1;
  matrix(0, 1) = 2;
  matrix(0, 2) = 3;
  matrix(1, 0) = 0;
  matrix(1, 1) = 4;
  matrix(1, 2) = 2;
  matrix(2, 0) = 5;
  matrix(2, 1) = 2;
  matrix(2, 2) = 1;
  res(0, 0) = 5;
  res(0, 1) = 10;
  res(0, 2) = 15;
  res(1, 0) = 0;
  res(1, 1) = 20;
  res(1, 2) = 10;
  res(2, 0) = 25;
  res(2, 1) = 10;
  res(2, 2) = 5;
  ASSERT_TRUE(res == matrix * 5);
}

TEST(OperatorPlusRavno, Test_1) {
  auto matrix = S21Matrix(2, 2);
  matrix(0, 0) = 1;
  matrix(0, 1) = 2;
  matrix(1, 0) = 3;
  matrix(1, 1) = 4;
  auto m1 = S21Matrix(2, 2);
  m1(0, 0) = 1;
  m1(0, 1) = 2;
  m1(1, 0) = 3;
  m1(1, 1) = 4;
  matrix += m1;
  auto res = S21Matrix(2, 2);
  res(0, 0) = 2;
  res(0, 1) = 4;
  res(1, 0) = 6;
  res(1, 1) = 8;
  ASSERT_TRUE(res == matrix);
}

TEST(OperatorMinusRavno, Test_1) {
  auto matrix = S21Matrix(2, 2);
  matrix(0, 0) = 1;
  matrix(0, 1) = 2;
  matrix(1, 0) = 3;
  matrix(1, 1) = 4;
  auto m1 = S21Matrix(2, 2);
  m1(0, 0) = 1;
  m1(0, 1) = 2;
  m1(1, 0) = 3;
  m1(1, 1) = 4;
  matrix -= m1;
  auto res = S21Matrix(2, 2);
  res(0, 0) = 0;
  res(0, 1) = 0;
  res(1, 0) = 0;
  res(1, 1) = 0;
  ASSERT_TRUE(res == matrix);
}

TEST(OperatorMulRavno, Test_1) {
  auto matrix = S21Matrix(2, 2);
  matrix(0, 0) = 1;
  matrix(0, 1) = 2;
  matrix(1, 0) = 3;
  matrix(1, 1) = 4;
  auto m1 = S21Matrix(2, 2);
  m1(0, 0) = 1;
  m1(0, 1) = 2;
  m1(1, 0) = 3;
  m1(1, 1) = 4;
  matrix *= m1;
  auto res = S21Matrix(2, 2);
  res(0, 0) = 7;
  res(0, 1) = 10;
  res(1, 0) = 15;
  res(1, 1) = 22;
  ASSERT_TRUE(res == matrix);
}

TEST(OperatorMulRavoNum, Test_1) {
  auto matrix = S21Matrix(2, 2);
  matrix(0, 0) = 1;
  matrix(0, 1) = 2;
  matrix(1, 0) = 3;
  matrix(1, 1) = 4;
  matrix *= 5;
  auto res = S21Matrix(2, 2);
  res(0, 0) = 5;
  res(0, 1) = 10;
  res(1, 0) = 15;
  res(1, 1) = 20;
  ASSERT_TRUE(res == matrix);
}

TEST(Eqmatrix, Test_1) {
  auto matrix = S21Matrix(3, 3);
  auto m1 = S21Matrix(3, 3);
  for (auto n = 0; n < matrix.GetRows(); n++) {
    for (auto m = 0; m < matrix.GetCols(); m++) {
      matrix(n, m) = 2 + n * m + 0.567882 * n;
      m1(n, m) = 5 + n * m + 0.567882 * n;
    }
  }

  ASSERT_FALSE(matrix.EqMatrix(m1));
}

TEST(Eqmatrix, Test_2) {
  auto matrix = S21Matrix(3, 3);
  auto m1 = S21Matrix(3, 3);
  for (auto n = 0; n < matrix.GetRows(); n++) {
    for (auto m = 0; m < matrix.GetCols(); m++) {
      matrix(n, m) = 2 + n * m + 0.567882 * n;
      m1(n, m) = 2 + n * m + 0.567882 * n;
    }
  };
  ASSERT_TRUE(matrix.EqMatrix(m1));
}
TEST(Eqmatrix, Test_3) {
  auto matrix = S21Matrix(3, 3);
  auto m1 = S21Matrix(5, 7);
  ASSERT_FALSE(matrix.EqMatrix(m1));
}
TEST(SumMatrix, Test_1) {
  auto matrix = S21Matrix(5, 7);
  auto m1 = S21Matrix(5, 7);
  auto res = S21Matrix(5, 7);
  matrix(0, 0) = 1.6798966;
  matrix(0, 1) = 0.0437727;
  matrix(0, 2) = 4.3593647;
  matrix(0, 3) = 4.5170551;
  matrix(0, 4) = 1.834453;
  matrix(0, 5) = 5.3299626;
  matrix(0, 6) = 9.4344051;
  matrix(1, 0) = 7.8973326;
  matrix(1, 1) = 2.7545705;
  matrix(1, 2) = 0.0068284;
  matrix(1, 3) = 3.195062;
  matrix(1, 4) = 3.7820706;
  matrix(1, 5) = 4.87188;
  matrix(1, 6) = 1.6332084;
  matrix(2, 0) = 4.0080533;
  matrix(2, 1) = 5.1824983;
  matrix(2, 2) = 1.8709348;
  matrix(2, 3) = 1.7129437;
  matrix(2, 4) = 7.0195318;
  matrix(2, 5) = 8.5233362;
  matrix(2, 6) = 1.4730998;
  matrix(3, 0) = 7.8966359;
  matrix(3, 1) = 3.1110179;
  matrix(3, 2) = 2.1897596;
  matrix(3, 3) = 1.3395454;
  matrix(3, 4) = 2.5424386;
  matrix(3, 5) = 7.5881703;
  matrix(3, 6) = 3.6708998;
  matrix(4, 0) = 2.0189955;
  matrix(4, 1) = 1.2468616;
  matrix(4, 2) = 7.8768535;
  matrix(4, 3) = 3.939061;
  matrix(4, 4) = 9.8289351;
  matrix(4, 5) = 7.9362708;
  matrix(4, 6) = 8.860881;

  m1(0, 0) = 3.270204;
  m1(0, 1) = 0.3581267;
  m1(0, 2) = 7.3521976;
  m1(0, 3) = 3.4514901;
  m1(0, 4) = 9.0048447;
  m1(0, 5) = 3.1977996;
  m1(0, 6) = 4.9368808;
  m1(1, 0) = 7.8835964;
  m1(1, 1) = 1.1313949;
  m1(1, 2) = 2.920701;
  m1(1, 3) = 7.1700057;
  m1(1, 4) = 6.7271962;
  m1(1, 5) = 0.3100228;
  m1(1, 6) = 0.6484982;
  m1(2, 0) = 1.3262252;
  m1(2, 1) = 3.1106793;
  m1(2, 2) = 9.2646967;
  m1(2, 3) = 9.2467849;
  m1(2, 4) = 1.8371872;
  m1(2, 5) = 4.2508168;
  m1(2, 6) = 4.3476804;
  m1(3, 0) = 2.4225618;
  m1(3, 1) = 7.8125904;
  m1(3, 2) = 8.4664914;
  m1(3, 3) = 7.4502609;
  m1(3, 4) = 3.1927254;
  m1(3, 5) = 9.6575278;
  m1(3, 6) = 6.5443696;
  m1(4, 0) = 2.783262;
  m1(4, 1) = 4.2558604;
  m1(4, 2) = 0.7215911;
  m1(4, 3) = 5.6422099;
  m1(4, 4) = 6.2070837;
  m1(4, 5) = 4.4492828;
  m1(4, 6) = 2.6642072;

  res(0, 0) = 4.9501006;
  res(0, 1) = 0.4018994;
  res(0, 2) = 11.7115623;
  res(0, 3) = 7.9685452;
  res(0, 4) = 10.8392977;
  res(0, 5) = 8.5277622;
  res(0, 6) = 14.3712859;
  res(1, 0) = 15.780929;
  res(1, 1) = 3.8859654;
  res(1, 2) = 2.9275294;
  res(1, 3) = 10.3650677;
  res(1, 4) = 10.5092668;
  res(1, 5) = 5.1819028;
  res(1, 6) = 2.2817066;
  res(2, 0) = 5.3342785;
  res(2, 1) = 8.2931776;
  res(2, 2) = 11.1356315;
  res(2, 3) = 10.9597286;
  res(2, 4) = 8.856719;
  res(2, 5) = 12.774153;
  res(2, 6) = 5.8207802;
  res(3, 0) = 10.3191977;
  res(3, 1) = 10.9236083;
  res(3, 2) = 10.656251;
  res(3, 3) = 8.7898063;
  res(3, 4) = 5.735164;
  res(3, 5) = 17.2456981;
  res(3, 6) = 10.2152694;
  res(4, 0) = 4.8022575;
  res(4, 1) = 5.502722;
  res(4, 2) = 8.5984446;
  res(4, 3) = 9.5812709;
  res(4, 4) = 16.0360188;
  res(4, 5) = 12.3855536;
  res(4, 6) = 11.5250882;

  matrix.SumMatrix(m1);
  ASSERT_TRUE(res == matrix);
}
TEST(SumMatrix, Test_2) {
  auto matrix = S21Matrix(1, 6);
  auto m1 = S21Matrix(1, 6);
  auto res = S21Matrix(1, 6);

  matrix(0, 0) = 0.0427698;
  matrix(0, 1) = 1.8969589;
  matrix(0, 2) = 6.7891406;
  matrix(0, 3) = 7.3300576;
  matrix(0, 4) = 3.5799323;
  matrix(0, 5) = 5.6782038;

  m1(0, 0) = 8.2910519;
  m1(0, 1) = 1.5890623;
  m1(0, 2) = 5.3272862;
  m1(0, 3) = 3.2605317;
  m1(0, 4) = 4.3381494;
  m1(0, 5) = 2.3604244;

  res(0, 0) = 8.3338217;
  res(0, 1) = 3.4860212;
  res(0, 2) = 12.1164268;
  res(0, 3) = 10.5905893;
  res(0, 4) = 7.9180817;
  res(0, 5) = 8.0386282;
  matrix.SumMatrix(m1);
  ASSERT_TRUE(res == matrix);
}
TEST(SubMatrix, Test_1) {
  auto matrix = S21Matrix(4, 4);
  auto m1 = S21Matrix(4, 4);
  auto res = S21Matrix(4, 4);
  matrix(0, 0) = 5.137336;
  matrix(0, 1) = 8.2137853;
  matrix(0, 2) = 3.7607755;
  matrix(0, 3) = 0.6711109;
  matrix(1, 0) = 5.8220309;
  matrix(1, 1) = 4.9619391;
  matrix(1, 2) = 4.0484669;
  matrix(1, 3) = 1.3162821;
  matrix(2, 0) = 5.8403124;
  matrix(2, 1) = 7.8902187;
  matrix(2, 2) = 7.4492055;
  matrix(2, 3) = 9.2927833;
  matrix(3, 0) = 9.0294584;
  matrix(3, 1) = 8.5052875;
  matrix(3, 2) = 3.8853253;
  matrix(3, 3) = 3.3480819;

  m1(0, 0) = 2.7048905;
  m1(0, 1) = 6.3733706;
  m1(0, 2) = 4.3520822;
  m1(0, 3) = 1.9555814;
  m1(1, 0) = 0.93011;
  m1(1, 1) = 1.6723631;
  m1(1, 2) = 7.8941219;
  m1(1, 3) = 0.6821209;
  m1(2, 0) = 1.8145256;
  m1(2, 1) = 9.3099287;
  m1(2, 2) = 1.8274244;
  m1(2, 3) = 9.3607277;
  m1(3, 0) = 9.2529804;
  m1(3, 1) = 7.5253146;
  m1(3, 2) = 4.342841;
  m1(3, 3) = 0.0570693;

  res(0, 0) = 2.4324455;
  res(0, 1) = 1.8404147;
  res(0, 2) = -0.5913067;
  res(0, 3) = -1.2844705;
  res(1, 0) = 4.8919209;
  res(1, 1) = 3.289576;
  res(1, 2) = -3.845655;
  res(1, 3) = 0.6341612;
  res(2, 0) = 4.0257868;
  res(2, 1) = -1.41971;
  res(2, 2) = 5.6217811;
  res(2, 3) = -0.0679444;
  res(3, 0) = -0.223522;
  res(3, 1) = 0.9799729;
  res(3, 2) = -0.4575157;
  res(3, 3) = 3.2910126;

  matrix.SubMatrix(m1);
  ASSERT_TRUE(res == matrix);
}

TEST(MulNumber, Test_1) {
  auto m1 = S21Matrix(3, 3);
  auto res = S21Matrix(3, 3);

  m1(0, 0) = 5;
  m1(0, 1) = 8;
  m1(0, 2) = 3;
  m1(1, 0) = 5;
  m1(1, 1) = 4;
  m1(1, 2) = 4;
  m1(2, 0) = 5;
  m1(2, 1) = 7;
  m1(2, 2) = 7;
  res(0, 0) = 25;
  res(0, 1) = 40;
  res(0, 2) = 15;
  res(1, 0) = 25;
  res(1, 1) = 20;
  res(1, 2) = 20;
  res(2, 0) = 25;
  res(2, 1) = 35;
  res(2, 2) = 35;
  m1.MulNumber(5);
  ASSERT_TRUE(res == m1);
}

TEST(MulMatrix, Test_1) {
  auto matrix = S21Matrix(3, 4);
  auto m1 = S21Matrix(4, 1);
  auto res = S21Matrix(3, 1);
  matrix(0, 0) = 9.5124304;
  matrix(0, 1) = 6.3230843;
  matrix(0, 2) = 0.7541055;
  matrix(0, 3) = 1.641339;
  matrix(1, 0) = 6.734639;
  matrix(1, 1) = 8.1589636;
  matrix(1, 2) = 2.5854905;
  matrix(1, 3) = 5.7990419;
  matrix(2, 0) = 0.606489;
  matrix(2, 1) = 3.0376417;
  matrix(2, 2) = 9.6932691;
  matrix(2, 3) = 0.4120328;
  m1(0, 0) = 4.0741263;
  m1(1, 0) = 2.3079144;
  m1(2, 0) = 4.2783473;
  m1(3, 0) = 3.8037133;
  res(0, 0) = 62.8174884;
  res(1, 0) = 79.3874786;
  res(2, 0) = 52.5199561;
  matrix.MulMatrix(m1);
  ASSERT_TRUE(res == matrix);
}

TEST(Transpose, Test_1) {
  auto matrix = S21Matrix(4, 1);
  auto res = S21Matrix(1, 4);
  matrix(0, 0) = 1.0773244;
  matrix(1, 0) = 8.1645;
  matrix(2, 0) = 6.0228517;
  matrix(3, 0) = 8.8354206;
  res(0, 0) = 1.0773244;
  res(0, 1) = 8.1645;
  res(0, 2) = 6.0228517;
  res(0, 3) = 8.8354206;
  ASSERT_TRUE(res == matrix.Transpose());
}

TEST(Determinant, Test_2) {
  auto matrix = S21Matrix(5, 5);
  matrix(0, 0) = 6.8990756;
  matrix(0, 1) = 0.2088484;
  matrix(0, 2) = 7.682689;
  matrix(0, 3) = 8.7141331;
  matrix(0, 4) = 2.3838878;
  matrix(1, 0) = 7.4754983;
  matrix(1, 1) = 5.8375626;
  matrix(1, 2) = 2.1010049;
  matrix(1, 3) = 2.5093676;
  matrix(1, 4) = 9.7080018;
  matrix(2, 0) = 6.0319614;
  matrix(2, 1) = 9.5180821;
  matrix(2, 2) = 4.2340779;
  matrix(2, 3) = 5.2743132;
  matrix(2, 4) = 4.3168214;
  matrix(3, 0) = 7.336647;
  matrix(3, 1) = 3.4249628;
  matrix(3, 2) = 9.1271946;
  matrix(3, 3) = 4.0004491;
  matrix(3, 4) = 4.4558972;
  matrix(4, 0) = 1.9246572;
  matrix(4, 1) = 9.8871218;
  matrix(4, 2) = 1.0733786;
  matrix(4, 3) = 0.7351468;
  matrix(4, 4) = 5.9620428;
  double res = -8627.026703761681;
  ASSERT_DOUBLE_EQ(res, matrix.Determinant());
}

TEST(InverseMatrix, Test_1) {
  auto matrix = S21Matrix(6, 6);
  auto res = S21Matrix(6, 6);
  matrix(0, 0) = 3.4840239;
  matrix(0, 1) = 9.9109435;
  matrix(0, 2) = 2.7588375;
  matrix(0, 3) = 3.4660608;
  matrix(0, 4) = 4.311227;
  matrix(0, 5) = 4.951912;
  matrix(1, 0) = 2.3878109;
  matrix(1, 1) = 4.6022725;
  matrix(1, 2) = 1.4454429;
  matrix(1, 3) = 4.1621992;
  matrix(1, 4) = 4.7599256;
  matrix(1, 5) = 9.9804159;
  matrix(2, 0) = 8.9407511;
  matrix(2, 1) = 3.9794991;
  matrix(2, 2) = 8.8307839;
  matrix(2, 3) = 0.5345596;
  matrix(2, 4) = 6.7304441;
  matrix(2, 5) = 3.3783026;
  matrix(3, 0) = 8.0770786;
  matrix(3, 1) = 1.2032909;
  matrix(3, 2) = 5.4457859;
  matrix(3, 3) = 0.4735998;
  matrix(3, 4) = 9.8548829;
  matrix(3, 5) = 2.1114585;
  matrix(4, 0) = 9.0839935;
  matrix(4, 1) = 7.6142158;
  matrix(4, 2) = 5.4558798;
  matrix(4, 3) = 9.1462514;
  matrix(4, 4) = 6.654701;
  matrix(4, 5) = 9.0628095;
  matrix(5, 0) = 6.3355404;
  matrix(5, 1) = 2.0121068;
  matrix(5, 2) = 6.7168323;
  matrix(5, 3) = 0.6414603;
  matrix(5, 4) = 8.8703062;
  matrix(5, 5) = 2.4807336;

  res(0, 0) = -0.0138457;
  res(0, 1) = -0.0124876;
  res(0, 2) = 0.1476798;
  res(0, 3) = 0.2939999;
  res(0, 4) = 0.0178383;
  res(0, 5) = -0.438639;
  res(1, 0) = 0.1500769;
  res(1, 1) = -0.0333111;
  res(1, 2) = 0.0144463;
  res(1, 3) = 0.0165966;
  res(1, 4) = -0.0395763;
  res(1, 5) = -0.0547757;
  res(2, 0) = -0.0601983;
  res(2, 1) = -0.0302436;
  res(2, 2) = 0.0566365;
  res(2, 3) = -0.338242;
  res(2, 4) = 0.0255952;
  res(2, 5) = 0.3590975;
  res(3, 0) = -0.0494099;
  res(3, 1) = -0.1085337;
  res(3, 2) = -0.1704801;
  res(3, 3) = -0.1503209;
  res(3, 4) = 0.1780094;
  res(3, 5) = 0.2450685;
  res(4, 0) = 0.0406523;
  res(4, 1) = 0.0002179;
  res(4, 2) = -0.1675007;
  res(4, 3) = 0.0505695;
  res(4, 4) = -0.0209201;
  res(4, 5) = 0.1794657;
  res(5, 0) = -0.0559565;
  res(5, 1) = 0.1680834;
  res(5, 2) = 0.1007855;
  res(5, 3) = 0.0095657;
  res(5, 4) = -0.053984;
  res(5, 5) = -0.1095989;

  ASSERT_TRUE(res == matrix.InverseMatrix());
}
TEST(InverseMatrix, Test_2) {
  auto matrix = S21Matrix(2, 2);
  matrix(0, 0) = 4;
  matrix(0, 1) = 4;
  matrix(1, 0) = 2;
  matrix(1, 1) = 2;
  ASSERT_ANY_THROW(matrix.InverseMatrix());
}