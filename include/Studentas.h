#pragma once
#include <list>
#include <string>
#include <vector>

class Studentas {
private:
  std::string vardas_ = "";
  std::string pavarde_ = "";
  int namuDarbai_ = 0;
  std::vector<int> pazymiai_ = {};
  int egzaminoBalas_ = 0;
  double galutinisVidurkis_ = 0.0;
  double galutinisMediana_ = 0.0;

public:
  Studentas();

  ~Studentas() {}

  Studentas(std::string vardas, std::string pavarde, int namuDarbai,
            std::vector<int> pazymiai, int egzaminoBalas)
      : vardas_(std::move(vardas)), pavarde_(std::move(pavarde)),
        namuDarbai_(namuDarbai), pazymiai_(std::move(pazymiai)),
        egzaminoBalas_(egzaminoBalas) {};

  Studentas(const Studentas &other)
      : vardas_(other.vardas_), pavarde_(other.pavarde_),
        namuDarbai_(other.namuDarbai_), pazymiai_(other.pazymiai_),
        egzaminoBalas_(other.egzaminoBalas_),
        galutinisVidurkis_(other.galutinisVidurkis_),
        galutinisMediana_(other.galutinisMediana_) {}

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

  Studentas(Studentas &&other)
      : vardas_(std::move(other.vardas_)), pavarde_(std::move(other.pavarde_)),
        namuDarbai_(other.namuDarbai_), pazymiai_(std::move(other.pazymiai_)),
        egzaminoBalas_(other.egzaminoBalas_),
        galutinisVidurkis_(other.galutinisVidurkis_),
        galutinisMediana_(other.galutinisMediana_) {}

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

    return *this;
  }

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