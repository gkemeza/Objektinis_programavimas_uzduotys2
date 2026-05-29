#include "Studentas.h"
#include "functions.h"
#include <gtest/gtest.h>
/**
 * @file tests.cpp
 * @brief Šiame faile yra aprašomi testai, skirti patikrinti Studentas klasės
 * funkcionalumą, įskaitant penkias taisykles (Rule of Five) ir papildomus
 * loginius testus, susijusius su pažymių vidurkiu ir mediana.
 *
 * Testai apima:
 * 1. Konstruktoriumi inicializuojančios laukus teisingai.
 * 2. Numatinis konstruktorius inicializuoja tuščius laukus.
 * 3. Kopijavimo konstruktorius sukuria nepriklausomą kopiją.
 * 4. Kopijavimo priskyrimo operatorius sukuria nepriklausomą kopiją.
 * 5. Perkelimo konstruktorius perkelia savininkystę.
 * 6. Perkelimo priskyrimo operatorius perkelia savininkystę.
 * 7. Destruktorius nesukelia klaidų.
 * 8. Įvedimo operatorius teisingai skaito duomenis.
 * 9. Išvedimo operatorius teisingai formatuoja duomenis.
 * 10. Pažymių vidurkio skaičiavimas yra teisingas.
 * 11. Pažymių medianos skaičiavimas yra teisingas.
 * 12. Tuščių pažymių atveju vidurkis grąžina 0.
 *
 * Šie testai padeda užtikrinti, kad Studentas klasė veikia pagal numatytas
 * taisykles ir logiką, bei kad jos metodai elgiasi teisingai įvairiais
 * scenarijais.
 *
 */
// 0. Constructor
Studentas s1("Jonas", "Jonaitis", 3, {8, 9, 7}, 10);
TEST(RuleOfFive, ConstructorInitializesFields) {
  EXPECT_EQ(s1.getVardas(), "Jonas");
  EXPECT_EQ(s1.getPavarde(), "Jonaitis");
  EXPECT_EQ(s1.getNamuDarbai(), 3);
  EXPECT_EQ(s1.getPazymiai()[0], 8);
  EXPECT_EQ(s1.getPazymiai()[1], 9);
  EXPECT_EQ(s1.getPazymiai()[2], 7);
  EXPECT_EQ(s1.getEgzaminoBalas(), 10);
}

// 0. Default Constructor
Studentas s2;
TEST(RuleOfFive, DefaultConstructorInitializesEmpty) {
  EXPECT_EQ(s2.getVardas(), "");
  EXPECT_EQ(s2.getPavarde(), "");
  EXPECT_EQ(s2.getNamuDarbai(), 0);
  EXPECT_TRUE(s2.getPazymiai().empty());
  EXPECT_EQ(s2.getEgzaminoBalas(), 0);
  EXPECT_EQ(s2.getGalutinisVidurkis(), 0.0);
  EXPECT_EQ(s2.getGalutinisMediana(), 0.0);
}

// ── 1. Copy Constructor
TEST(RuleOfFive, CopyConstructorCreatesIndependentCopy) {
  Studentas s3(s1);

  EXPECT_EQ(s3.getVardas(), "Jonas");
  EXPECT_EQ(s3.getPavarde(), "Jonaitis");
  EXPECT_EQ(s3.getNamuDarbai(), 3);
  EXPECT_EQ(s3.getPazymiai()[0], 8);
  EXPECT_EQ(s3.getPazymiai()[1], 9);
  EXPECT_EQ(s3.getPazymiai()[2], 7);
  EXPECT_EQ(s3.getEgzaminoBalas(), 10);

  s3.setVardas("Petras");

  EXPECT_EQ(s1.getVardas(), "Jonas");
  EXPECT_EQ(s3.getVardas(), "Petras");
}

// ── 2. Copy Assignment
TEST(RuleOfFive, CopyAssignmentCreatesIndependentCopy) {
  Studentas s4("Jonas", "Jonaitis", 3, {8, 9, 7}, 10);
  Studentas s5;

  s5 = s4;
  EXPECT_EQ(s5.getVardas(), "Jonas");
  EXPECT_EQ(s5.getPavarde(), "Jonaitis");
  EXPECT_EQ(s5.getNamuDarbai(), 3);
  EXPECT_EQ(s5.getPazymiai()[0], 8);
  EXPECT_EQ(s5.getPazymiai()[1], 9);
  EXPECT_EQ(s5.getPazymiai()[2], 7);
  EXPECT_EQ(s5.getEgzaminoBalas(), 10);

  s4.setVardas("Antanas");
  EXPECT_EQ(s4.getVardas(), "Antanas");
  EXPECT_EQ(s5.getVardas(), "Jonas");
}

// ── 3. Move Constructor
TEST(RuleOfFive, MoveConstructorTransfersOwnership) {
  Studentas original("Jonas", "Jonaitis", 3, {8, 9, 7}, 10);
  Studentas moved(std::move(original));

  EXPECT_EQ(moved.getVardas(), "Jonas");
  EXPECT_EQ(moved.getPavarde(), "Jonaitis");
  EXPECT_EQ(moved.getNamuDarbai(), 3);
  EXPECT_EQ(moved.getPazymiai()[0], 8);
  EXPECT_EQ(moved.getPazymiai()[1], 9);
  EXPECT_EQ(moved.getPazymiai()[2], 7);
  EXPECT_EQ(moved.getEgzaminoBalas(), 10);

  EXPECT_EQ(original.getVardas(), "");
  EXPECT_EQ(original.getPavarde(), "");
  EXPECT_EQ(original.getNamuDarbai(), 0);
  EXPECT_TRUE(original.getPazymiai().empty());
  EXPECT_EQ(original.getEgzaminoBalas(), 0);
}

// ── 4. Move Assignment
TEST(RuleOfFive, MoveAssignmentTransfersOwnership) {
  Studentas s6("Jonas", "Jonaitis", 3, {8, 9, 7}, 10);
  Studentas s7;

  s7 = std::move(s6);

  EXPECT_EQ(s7.getVardas(), "Jonas");
  EXPECT_EQ(s7.getPavarde(), "Jonaitis");
  EXPECT_EQ(s7.getNamuDarbai(), 3);
  EXPECT_EQ(s7.getPazymiai()[0], 8);
  EXPECT_EQ(s7.getPazymiai()[1], 9);
  EXPECT_EQ(s7.getPazymiai()[2], 7);
  EXPECT_EQ(s7.getEgzaminoBalas(), 10);

  EXPECT_EQ(s6.getVardas(), "");
  EXPECT_EQ(s6.getPavarde(), "");
  EXPECT_EQ(s6.getNamuDarbai(), 0);
  EXPECT_TRUE(s6.getPazymiai().empty());
  EXPECT_EQ(s6.getEgzaminoBalas(), 0);
}

// ── 5. Destructor
TEST(RuleOfFive, DestructorDoesNotCrash) {
  EXPECT_NO_THROW({ Studentas s("Jonas", "Jonaitis", 3, {8, 9, 7}, 10); });
}

// 6. Input Operator Overload
TEST(RuleOfFive, InputOperatorReadsData) {
  std::istringstream iss("Petras Petraitis 6 8 9");
  Studentas s8;
  iss >> s8;

  EXPECT_EQ(s8.getVardas(), "Petras");
  EXPECT_EQ(s8.getPavarde(), "Petraitis");
  EXPECT_EQ(s8.getPazymiai()[0], 6);
  EXPECT_EQ(s8.getPazymiai()[1], 8);
  EXPECT_EQ(s8.getEgzaminoBalas(), 9);
}

// 7. Output Operator Overload
TEST(RuleOfFive, OutputOperatorFormatsData) {
  Studentas s9("Petras", "Petraitis", 2, {6, 8}, 9);
  suskaiciuotiStudentoGalutinius(s9);
  std::ostringstream oss;
  oss << s9;

  std::string expectedOutput = "Petras              Petraitis           8.20   "
                               "             8.20                ";
  EXPECT_EQ(oss.str(), expectedOutput);
}

// 8. Grade Calculation Logic
TEST(StudentLogic, GradeAverageCalculatedCorrectly) {
  Studentas s10("Jonas", "Jonaitis", 3, {8, 9, 7}, 10);
  suskaiciuotiStudentoGalutinius(s10);
  EXPECT_NEAR(s10.getGalutinisVidurkis(), 9.2, 0.001);
}

// 9. Median Calculation Logic
TEST(StudentLogic, GradeMedianCalculatedCorrectly) {
  Studentas s11("Jonas", "Jonaitis", 4, {8, 9, 7, 10}, 10);
  suskaiciuotiStudentoGalutinius(s11);
  EXPECT_NEAR(s11.getGalutinisMediana(), 9.4, 0.001);
}

// 10. Empty Grades
TEST(StudentLogic, EmptyGradesReturnsZero) {
  Studentas s12("Jonas", "Jonaitis", 0, {}, 0);
  suskaiciuotiStudentoGalutinius(s12);
  EXPECT_EQ(s12.getGalutinisVidurkis(), 0.0);
}