#pragma once
#include <iostream>
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

  Studentas(std::string vardas, std::string pavarde, int namuDarbai,
            std::vector<int> pazymiai, int egzaminoBalas)
      : vardas_(std::move(vardas)), pavarde_(std::move(pavarde)),
        namuDarbai_(namuDarbai), pazymiai_(std::move(pazymiai)),
        egzaminoBalas_(egzaminoBalas) {};

  Studentas(std::string vardas, std::string pavarde, int namuDarbai,
            std::vector<int> pazymiai, int egzaminoBalas,
            double galutinisVidurkis, double galutinisMediana)
      : vardas_(std::move(vardas)), pavarde_(std::move(pavarde)),
        namuDarbai_(namuDarbai), pazymiai_(std::move(pazymiai)),
        egzaminoBalas_(egzaminoBalas), galutinisVidurkis_(galutinisVidurkis),
        galutinisMediana_(galutinisMediana) {};

  std::string getVardas() const { return vardas_; }
  std::string getPavarde() const { return pavarde_; }
  int getNamuDarbai() const { return namuDarbai_; }
  int getEgzaminoBalas() const { return egzaminoBalas_; }
  double getGalutinisVidurkis() const { return galutinisVidurkis_; }
  double getGalutinisMediana() const { return galutinisMediana_; }
  const std::vector<int> &getPazymiai() const { return pazymiai_; }

  // double galutinisBalas(double (*)(std::vector<double>) = mediana) const;
  std::istream &readStudent(std::istream &is, int namuDarbai);

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