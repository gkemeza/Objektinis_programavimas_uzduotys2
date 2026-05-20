#include "Studentas.h"
#include <algorithm>
#include <iomanip>
#include <numeric>
#include <string>

using std::istream;
using std::left;
using std::ostream;
using std::setw;
using std::sort;
using std::string;
using std::vector;

ostream &operator<<(std::ostream &out, const Studentas &s) {
  out << left << setw(20) << "Vardas" << left << setw(20) << "Pavarde" << left
      << setw(20) << "Galutinis (Vid.)" << left << setw(20)
      << "Galutinis (Med.)" << "\n";

  out << string(100, '-') << "\n";

  return out;
}

istream &operator>>(std::istream &in, Studentas &s) {
  string vardas, pavarde;
  in >> vardas >> pavarde;
  s.setVardas(vardas);
  s.setPavarde(pavarde);

  int temp;
  vector<int> pazymiai;
  while (in >> temp) {

    pazymiai.push_back(temp);
  }
  if (!pazymiai.empty()) {

    int egz = pazymiai.back();
    pazymiai.pop_back();
    s.setEgzaminoBalas(egz);

    for (int i : pazymiai) {
      s.addPazymys(i);
    }

    s.gautiVidurkiVidutini();
    s.gautiVidurkiMediana();
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
  double vidurkisVidutinis = (pazymiuSuma * 1.0) / (namuDarbai_ * 1.0);

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