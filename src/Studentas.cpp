#include "Studentas.h"
#include <algorithm>
#include <numeric>
using std::istream;
using std::runtime_error;
using std::sort;

Studentas::Studentas() {}

istream &Studentas::readStudent(istream &is, int namuDarbai) {
  if (!(is >> vardas_ >> pavarde_))
    return is;

  pazymiai_.clear();
  bool skaitymasPavyko = true;

  for (int i = 0; i < namuDarbai; i++) {
    int pazymys;
    if (!(is >> pazymys)) {
      skaitymasPavyko = false;
      break;
    }
    pazymiai_.push_back(pazymys);
  }

  if (!skaitymasPavyko || !(is >> egzaminoBalas_))
    throw runtime_error("Sugadintas failas");

  return is;
};

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