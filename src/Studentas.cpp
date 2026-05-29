#include "Studentas.h"
#include <algorithm>
#include <iomanip>
#include <numeric>
#include <ostream>
#include <sstream>
#include <string>

using std::cout;
using std::fixed;
using std::istream;
using std::istringstream;
using std::left;
using std::ostream;
using std::setprecision;
using std::setw;
using std::sort;
using std::string;
using std::vector;

/**
 * @brief Šiame faile yra įgyvendinami Studentas klasės metodai, įskaitant
 * konstruktorius, priskyrimo operatorius, destruktorių, bei perdengtus
 * įvedimo ir išvedimo operatorius. Taip pat yra metodai pažymių tvarkymui ir
 * galutinių rezultatų skaičiavimui.
 *
 * Ši klasė paveldi iš abstrakčios Zmogus klasės, todėl turi įgyvendinti WhoamI
 * metodą. Klasė taip pat turi savo specifinius duomenis, tokius kaip namų
 * darbų skaičius, pažymiai, egzamino balas, galutinis vidurkis ir mediana.
 *
 * Konstruktoriai ir priskyrimo operatoriai užtikrina tinkamą resursų valdymą,
 * o destruktorius užtikrina, kad visi resursai būtų tinkamai atlaisvinti.
 *
 * Perdengti įvedimo ir išvedimo operatoriai leidžia lengvai skaityti ir rašyti
 * Studentas objektus naudojant standartinius srautus.
 *
 * Ši klasė yra testuojama naudojant Google Test framework'ą, siekiant
 * užtikrinti, kad visi metodai veiktų teisingai įvairiais scenarijais.
 *
 */

ostream &operator<<(ostream &out, const Studentas &studentas) {
  out << left << fixed << setprecision(2);
  out << setw(20) << studentas.getVardas() << setw(20) << studentas.getPavarde()
      << setw(20) << studentas.getGalutinisVidurkis() << setw(20)
      << studentas.getGalutinisMediana();

  return out;
}

istream &operator>>(std::istream &in, Studentas &s) {
  string eilute;
  if (!getline(in, eilute)) {
    return in;
  }

  istringstream ss(eilute);
  string vardas, pavarde;
  ss >> vardas >> pavarde;
  s.setVardas(vardas);
  s.setPavarde(pavarde);

  int temp;
  vector<int> pazymiai;

  while (ss >> temp) {
    pazymiai.push_back(temp);
  }

  if (!pazymiai.empty()) {
    int egz = pazymiai.back();
    pazymiai.pop_back();
    s.setEgzaminoBalas(egz);
    s.setPazymiai(pazymiai);
  }

  return in;
}

void Studentas::surusiuotiPazymius() {
  sort(pazymiai_.begin(), pazymiai_.end());
}

double Studentas::gautiVidurkiVidutini() const {
  if (pazymiai_.empty()) {
    return 0.0;
  }

  int pazymiuSuma = std::accumulate(pazymiai_.begin(), pazymiai_.end(), 0);
  double vidurkisVidutinis = (pazymiuSuma * 1.0) / (pazymiai_.size() * 1.0);

  return vidurkisVidutinis;
}

double Studentas::gautiVidurkiMediana() const {
  if (pazymiai_.empty()) {
    return 0.0;
  }

  auto size = pazymiai_.size();
  if (size % 2 != 0) {
    return pazymiai_[size / 2];
  } else {
    int number1 = pazymiai_[(size - 1) / 2];
    int number2 = pazymiai_[size / 2];
    return (number1 + number2) / 2.0;
  }
}