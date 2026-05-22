#pragma once
#include "Studentas.h"
#include <algorithm>
#include <cmath>
#include <deque>
#include <filesystem>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <list>
#include <random>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

Studentas ivestisRanka();
Studentas generuotiPazymius();
Studentas generuotiStudenta();
void isvestis(const StudentuKonteineris &studentai, bool arMediana);
void isvestisKonsole(const StudentuKonteineris &studentai);
void isvestisFailas(const StudentuKonteineris &studentai,
                    std::string failoPavadinimas);
std::string skaitytiZodi(const std::string &pranesimas);
std::string nuskaitytiVarda();
std::string nuskaitytiPavarde();
bool suskaiciuotiGalutini(StudentuKonteineris &studentai);
void suskaiciuotiStudentoGalutinius(Studentas &studentas);
void suskaiciuotiGalutinius(StudentuKonteineris &studentai);
std::vector<int> nuskaitytiPazymius(std::istream &is, int namuDarbai);
void nuskaitytiFaila(StudentuKonteineris &studentai,
                     const std::string &failoPavadinimas);
bool rusiuotiPagalVarda(const Studentas &a, const Studentas &b);
bool rusiuotiPagalPavarde(const Studentas &a, const Studentas &b);
bool rusiuotiPagalVidurki(const Studentas &a, const Studentas &b);
bool rusiuotiPagalMediana(const Studentas &a, const Studentas &b);
void rusiuotiStudentus(StudentuKonteineris &studentai, int input);
void surusiuotiPagalPasirinkima(StudentuKonteineris &studentai);
int skaitytiSkaiciu(const std::string &pranesimas, int min, int max);
std::string generuotiFaila(int studentuSkaicius, int namuDarbuSkaicius);
void skaidytiStudentus1(StudentuKonteineris &studentai,
                        StudentuKonteineris &vargsiukai,
                        StudentuKonteineris &kietiakai);
void skaidytiStudentus2(StudentuKonteineris &studentai,
                        StudentuKonteineris &kietiakai);
void skaidytiStudentus3(StudentuKonteineris &studentai,
                        StudentuKonteineris &vargsiukai,
                        StudentuKonteineris &kietiakai);
void failuGeneravimas();
void failoKurimoTestavimas();
void duomenuApdorojimoTestavimas();
void tikrinti(bool condition);
void ruleOfFiveTestas();
void testuotiGreiti();
void failoNuskaitymas(StudentuKonteineris &studentai);
void failoDuomenuApdorojimas(StudentuKonteineris &studentai);
void studentuDuomenuApdorojimas(StudentuKonteineris &studentai);