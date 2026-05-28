#pragma once
#include "Zmogus.h"
#include <iostream>
#include <list>
#include <string>
#include <vector>

class Studentas : public Zmogus {
private:
  std::vector<int> pazymiai_ = {};
  int namuDarbai_ = 0;
  int egzaminoBalas_ = 0;
  double galutinisVidurkis_ = 0.0;
  double galutinisMediana_ = 0.0;

public:
  Studentas()
      : Zmogus(), namuDarbai_(0), egzaminoBalas_(0), galutinisMediana_(0.0),
        galutinisVidurkis_(0.0) {}

  Studentas(std::string vardas, std::string pavarde, int namuDarbai,
            std::vector<int> pazymiai, int egzaminoBalas)
      : Zmogus(vardas, pavarde), namuDarbai_(namuDarbai),
        pazymiai_(std::move(pazymiai)), egzaminoBalas_(egzaminoBalas) {}

  ~Studentas() {
    pazymiai_.clear();
    pazymiai_.shrink_to_fit();
    namuDarbai_ = 0;
    egzaminoBalas_ = 0;
    galutinisVidurkis_ = 0.0;
    galutinisMediana_ = 0.0;
  }

  // Kopijavimo konstruktorius
  Studentas(const Studentas &other)
      : Zmogus(other.vardas_, other.pavarde_), namuDarbai_(other.namuDarbai_),
        pazymiai_(other.pazymiai_), egzaminoBalas_(other.egzaminoBalas_),
        galutinisVidurkis_(other.galutinisVidurkis_),
        galutinisMediana_(other.galutinisMediana_) {}

  // Kopijavimo priskyrimo operatorius
  Studentas &operator=(const Studentas &other) {
    if (this == &other) {
      return *this;
    }

    vardas_ = other.vardas_;
    pavarde_ = other.pavarde_;
    namuDarbai_ = other.namuDarbai_;
    pazymiai_ = other.pazymiai_;
    egzaminoBalas_ = other.egzaminoBalas_;
    galutinisVidurkis_ = other.galutinisVidurkis_;
    galutinisMediana_ = other.galutinisMediana_;

    return *this;
  }

  // Perkelimo konstruktorius
  Studentas(Studentas &&other)
      : Zmogus(std::move(other.vardas_), std::move(other.pavarde_)),
        namuDarbai_(other.namuDarbai_), pazymiai_(std::move(other.pazymiai_)),
        egzaminoBalas_(other.egzaminoBalas_),
        galutinisVidurkis_(other.galutinisVidurkis_),
        galutinisMediana_(other.galutinisMediana_) {

    other.vardas_.clear();
    other.pavarde_.clear();
    other.namuDarbai_ = 0;
    other.egzaminoBalas_ = 0;
    other.galutinisVidurkis_ = 0.0;
    other.galutinisMediana_ = 0.0;
  }

  // Perkelimo priskyrimo operatorius
  Studentas &operator=(Studentas &&other) {
    if (this == &other) {
      return *this;
    }

    vardas_ = std::move(other.vardas_);
    pavarde_ = std::move(other.pavarde_);
    namuDarbai_ = other.namuDarbai_;
    pazymiai_ = std::move(other.pazymiai_);
    egzaminoBalas_ = other.egzaminoBalas_;
    galutinisVidurkis_ = other.galutinisVidurkis_;
    galutinisMediana_ = other.galutinisMediana_;

    other.vardas_.clear();
    other.pavarde_.clear();
    other.namuDarbai_ = 0;
    other.egzaminoBalas_ = 0;
    other.galutinisVidurkis_ = 0.0;
    other.galutinisMediana_ = 0.0;

    return *this;
  }

  void WhoamI() const override {
    std::cout << vardas_ << " " << pavarde_ << std::endl;
  }

  // Perdengtas išvedimo operatorius
  friend std::ostream &operator<<(std::ostream &out, const Studentas &s);
  // Perdengtas įvedimo operatorius
  friend std::istream &operator>>(std::istream &in, Studentas &s);

  std::string getVardas() const { return vardas_; }
  std::string getPavarde() const { return pavarde_; }
  int getNamuDarbai() const { return namuDarbai_; }
  int getEgzaminoBalas() const { return egzaminoBalas_; }
  double getGalutinisVidurkis() const { return galutinisVidurkis_; }
  double getGalutinisMediana() const { return galutinisMediana_; }
  const std::vector<int> &getPazymiai() const { return pazymiai_; }

  void setVardas(const std::string &vardas) { vardas_ = vardas; }
  void setPavarde(const std::string &pavarde) { pavarde_ = pavarde; }
  void setEgzaminoBalas(const int balas) { egzaminoBalas_ = balas; }
  void setNamuDarbai(const int nd) { namuDarbai_ = nd; }
  void setGalutinisVidurkis(const double vidurkis) {
    galutinisVidurkis_ = vidurkis;
  }
  void setGalutinisMediana(const double mediana) {
    galutinisMediana_ = mediana;
  }
  void setPazymiai(std::vector<int> pazymiai) {
    pazymiai_ = std::move(pazymiai);
  }
  void addPazymys(int pazymys) { pazymiai_.push_back(pazymys); }

  void surusiuotiPazymius();
  double gautiVidurkiVidutini() const;
  double gautiVidurkiMediana() const;
};

using StudentuKonteineris = std::vector<Studentas>;
// using StudentuKonteineris = std::list<Studentas>;
// using StudentuKonteineris = std::deque<Studentas>;

// Rodykle i bet kokia funkcija, kuri priima du Studentas objektus ir grazina
// bool reiksme
using Comparator = bool (*)(const Studentas &, const Studentas &);

template <typename Konteineris>
inline void surusiuotiStudentus(Konteineris &studentai, Comparator comparator) {
  sort(studentai.begin(), studentai.end(), comparator);
}

template <>
inline void surusiuotiStudentus(std::list<Studentas> &studentai,
                                Comparator comparator) {
  studentai.sort(comparator);
}