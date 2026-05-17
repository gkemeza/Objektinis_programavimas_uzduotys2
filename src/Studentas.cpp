#include "Studentas.h"
#include <algorithm>
#include <numeric>
using std::istream;
using std::sort;

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