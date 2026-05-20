#include "functions.h"
#include "Studentas.h"
#include "timer.h"
#include <array>
#include <iostream>
#include <utility>

using std::array;
using std::cerr;
using std::cin;
using std::cout;
using std::endl;
using std::fixed;
using std::ifstream;
using std::istream;
using std::istringstream;
using std::left;
using std::move;
using std::mt19937;
using std::ofstream;
using std::random_device;
using std::right;
using std::runtime_error;
using std::setprecision;
using std::setw;
using std::string;
using std::to_string;
using std::uniform_int_distribution;
using std::vector;
using std::filesystem::create_directories;

void isvestis(const StudentuKonteineris &studentai, bool arMediana) {
  cout << left << fixed << setprecision(2);
  if (arMediana) {
    cout << setw(20) << "Pavarde" << setw(20) << "Vardas" << setw(20)
         << "Galutinis (Med.)" << "\n";
    cout << string(100, '-') << "\n";
    for (const Studentas &studentas : studentai) {
      cout << setw(20) << studentas.getPavarde() << setw(20)
           << studentas.getVardas() << setw(20)
           << studentas.getGalutinisMediana() << "\n";
    }
  } else {
    cout << setw(20) << "Pavarde" << setw(20) << "Vardas" << setw(20)
         << "Galutinis (Vid.)" << "\n";
    cout << string(100, '-') << "\n";
    for (const Studentas &studentas : studentai) {
      cout << setw(20) << studentas.getPavarde() << setw(20)
           << studentas.getVardas() << setw(20)
           << studentas.getGalutinisVidurkis() << "\n";
    }
  }
}

void isvestisKonsole(const StudentuKonteineris &studentai) {
  cout << left << setw(20) << "Vardas" << left << setw(20) << "Pavarde" << left
       << setw(20) << "Galutinis (Vid.)" << left << setw(20)
       << "Galutinis (Med.)" << "\n";
  cout << string(100, '-') << "\n";

  cout << left << fixed << setprecision(2);
  for (const Studentas &studentas : studentai) {
    cout << setw(20) << studentas.getVardas() << setw(20)
         << studentas.getPavarde() << setw(20)
         << studentas.getGalutinisVidurkis() << setw(20)
         << studentas.getGalutinisMediana() << "\n";
  }
}

void isvestisFailas(const StudentuKonteineris &studentai,
                    string failoPavadinimas) {
  try {
    const string dirPath = "../outputData/";
    create_directories(dirPath);

    ofstream failas("../outputData/" + failoPavadinimas);

    if (!failas.is_open())
      throw runtime_error("Klaida: nepavyko atidaryti failo irasymui.");

    failas << left << setw(20) << "Vardas" << left << setw(20) << "Pavarde"
           << left << setw(20) << "Galutinis (Vid.)" << left << setw(20)
           << "Galutinis (Med.)" << "\n";
    failas << string(100, '-') << "\n";

    failas << left << fixed << setprecision(2);
    for (const Studentas &studentas : studentai) {
      failas << setw(20) << studentas.getVardas() << setw(20)
             << studentas.getPavarde() << setw(20)
             << studentas.getGalutinisVidurkis() << setw(20)
             << studentas.getGalutinisMediana() << "\n";
    }
  } catch (const runtime_error &ex) {
    cerr << ex.what() << "\n";
  }

  cout << ">Isvesta i " + failoPavadinimas << endl;
}

string skaitytiZodi(const string &pranesimas) {
  while (true) {
    try {
      cout << pranesimas;
      string eilute;
      cin >> eilute;

      for (char c : eilute) {
        if (!isalpha(c)) {
          throw runtime_error("Klaida: ivestas zodis turi turėti tik raides.");
        }
      }

      return eilute;
    } catch (const runtime_error &ex) {
      cerr << "Klaida: " << ex.what() << "\n";
    }
  }
}

string nuskaitytiVarda() { return (skaitytiZodi("Iveskite varda: ")); }

string nuskaitytiPavarde() { return (skaitytiZodi("Iveskite pavarde: ")); }

Studentas ivestisRanka() {
  try {
    string vardas = nuskaitytiVarda();
    string pavarde = nuskaitytiPavarde();

    int namuDarbai =
        skaitytiSkaiciu("Iveskite semestro pazymiu skaiciu: ", 1, 10);

    vector<int> pazymiai;
    for (int i = 0; i < namuDarbai; i++) {
      cout << "Iveskite " << i + 1 << " pazymi is " << namuDarbai << ": ";
      int pazymys = skaitytiSkaiciu("", 1, 10);

      pazymiai.push_back(pazymys);
    }

    int randBalas = skaitytiSkaiciu("Iveskite egzamino pazymi: ", 1, 10);

    return Studentas(vardas, pavarde, namuDarbai, pazymiai, randBalas);

  } catch (const runtime_error &ex) {
    cerr << ex.what() << endl;
    throw;
  }
}

bool suskaiciuotiGalutini(StudentuKonteineris &studentai) {
  try {
    int input = skaitytiSkaiciu(
        "Galutinio balo skaiciavimo budas (1 - vidurkis, 2 - mediana):\n", 1,
        2);

    switch (input) {
    case 1:
      for (Studentas &studentas : studentai) {
        double vidurkis = studentas.gautiVidurkiVidutini();
        studentas.setGalutinisVidurkis(vidurkis * 0.4 +
                                       studentas.getEgzaminoBalas() * 0.6);
      }
      return false;
    case 2:
      for (Studentas &studentas : studentai) {
        studentas.surusiuotiPazymius();
        double vidurkis = studentas.gautiVidurkiMediana();
        studentas.setGalutinisMediana(vidurkis * 0.4 +
                                      studentas.getEgzaminoBalas() * 0.6);
      }
      return true;
    default:
      cout << "Neteisingas pasirinkimas!\n";
    }
  } catch (const runtime_error &ex) {
    cerr << ex.what() << endl;
  }

  return false;
}

void suskaiciuotiGalutinius(StudentuKonteineris &studentai) {
  for (Studentas &studentas : studentai) {

    double vidurkis = studentas.gautiVidurkiVidutini();
    studentas.setGalutinisVidurkis(vidurkis * 0.4 +
                                   studentas.getEgzaminoBalas() * 0.6);

    studentas.surusiuotiPazymius();
    double mediana = studentas.gautiVidurkiMediana();
    studentas.setGalutinisMediana(mediana * 0.4 +
                                  studentas.getEgzaminoBalas() * 0.6);
  }
}

int randomInt(int min, int max) {
  random_device rd;
  mt19937 mt(rd());
  uniform_int_distribution<int> dist(min, max);

  return dist(mt);
}

Studentas generuotiStudenta() {
  static const array<string, 10> vardai = {
      "Irma",   "Alma",  "Irena", "Egle",   "Jolanta",
      "Petras", "Jonas", "Ignas", "Darius", "Simas"};

  static const array<string, 5> vyruPavardes = {"Pavardenis1", "Pavardenis2",
                                                "Pavardenis3", "Pavardenis4",
                                                "Pavardenis5"};

  static const array<string, 5> moteruPavardes = {"Pavardaite1", "Pavardaite2",
                                                  "Pavardaite3", "Pavardaite4",
                                                  "Pavardaite5"};

  string vardas = vardai[randomInt(0, vardai.size() - 1)];

  string pavarde;
  if (!vardas.empty() && vardas.back() == 's') {
    pavarde = vyruPavardes[randomInt(0, vyruPavardes.size() - 1)];
  } else {
    pavarde = moteruPavardes[randomInt(0, moteruPavardes.size() - 1)];
  }

  int namuDarbai = 5;
  vector<int> pazymiai;
  pazymiai.reserve(namuDarbai);

  for (int i = 0; i < namuDarbai; i++) {
    pazymiai.push_back(randomInt(1, 10));
  }

  int randBalas = randomInt(1, 10);

  return Studentas(vardas, pavarde, namuDarbai, pazymiai, randBalas);
}

Studentas generuotiPazymius() {
  try {
    string vardas = nuskaitytiVarda();
    string pavarde = nuskaitytiPavarde();

    int namuDarbai = 5;
    vector<int> pazymiai;
    for (int i = 0; i < namuDarbai; i++) {
      int randPazymys = randomInt(1, 10);
      pazymiai.push_back(randPazymys);
    }

    int egzaminoPazymys = randomInt(1, 10);

    return Studentas(vardas, pavarde, namuDarbai, pazymiai, egzaminoPazymys);

  } catch (const runtime_error &ex) {
    cerr << ex.what() << endl;
    throw;
  }
}

vector<int> nuskaitytiPazymius(istream &is, int namuDarbai) {
  vector<int> pazymiai;

  for (int i = 0; i < namuDarbai; i++) {

    int pazymys;
    if (!(is >> pazymys)) {
      throw runtime_error("Sugadintas failas (pazymiai)");
      break;
    }

    pazymiai.push_back(pazymys);
  }

  return pazymiai;
}

void nuskaitytiFaila(StudentuKonteineris &studentai,
                     const string &failoPavadinimas) {
  ifstream failas(failoPavadinimas);
  if (!failas.is_open())
    throw runtime_error("Nepavyko atidaryti failo: " + failoPavadinimas);

  string antraste;
  if (!getline(failas, antraste))
    throw runtime_error("Failas tuscias: " + failoPavadinimas);

  istringstream ss(antraste);
  string zodis;
  int zodziuSkaicius = 0;
  while (ss >> zodis) {
    zodziuSkaicius++;
  }

  if (zodziuSkaicius < 4)
    throw runtime_error("Neteisinga antraste: " + failoPavadinimas);

  int namuDarbai = zodziuSkaicius - 3;
  string vardas, pavarde;
  vector<int> pazymiai;
  int egzaminoBalas;

  while (failas >> vardas >> pavarde) {
    pazymiai = (nuskaitytiPazymius(failas, namuDarbai));

    if (!(failas >> egzaminoBalas))
      throw runtime_error("Sugadintas failas (egzaminoBalas)");

    studentai.push_back(
        Studentas(vardas, pavarde, namuDarbai, pazymiai, egzaminoBalas));
  }

  suskaiciuotiGalutinius(studentai);
}

bool rusiuotiPagalVarda(const Studentas &a, const Studentas &b) {
  return a.getVardas() < b.getVardas();
}

bool rusiuotiPagalPavarde(const Studentas &a, const Studentas &b) {
  return a.getPavarde() < b.getPavarde();
}

bool rusiuotiPagalVidurki(const Studentas &a, const Studentas &b) {
  return a.getGalutinisVidurkis() < b.getGalutinisVidurkis();
}

bool rusiuotiPagalMediana(const Studentas &a, const Studentas &b) {
  return a.getGalutinisMediana() < b.getGalutinisMediana();
}

void rusiuotiStudentus(StudentuKonteineris &studentai, int input) {
  switch (input) {
  case 1:
    surusiuotiStudentus(studentai, rusiuotiPagalVarda);
    break;
  case 2:
    surusiuotiStudentus(studentai, rusiuotiPagalPavarde);
    break;
  case 3:
    surusiuotiStudentus(studentai, rusiuotiPagalVidurki);
    break;
  case 4:
    surusiuotiStudentus(studentai, rusiuotiPagalMediana);
    break;
  default:
    cout << "Neteisingas pasirinkimas!\n";
    break;
  }
}

void surusiuotiPagalPasirinkima(StudentuKonteineris &studentai) {
  int input =
      skaitytiSkaiciu("Rusiuoti pagal (1 - vardas, 2 - pavarde, 3 - galutinis "
                      "(vidurkis), 4 - galutinis (mediana):\n",
                      1, 4);

  rusiuotiStudentus(studentai, input);
}

int skaitytiSkaiciu(const string &pranesimas, int min, int max) {
  while (true) {
    try {
      cout << pranesimas;
      string eilute;
      cin >> eilute;

      for (int i = 0; i < eilute.size(); i++) {
        if (i == 0 && eilute[i] == '-') {
          continue;
        }
        if (!isdigit(eilute[i])) {
          throw runtime_error("Klaida: ivestas ne sveikas skaicius.");
        }
      }

      int reiksme = stoi(eilute);

      if (reiksme < min || reiksme > max)
        throw runtime_error("Klaida: skaicius turi buti nuo " + to_string(min) +
                            " iki " + to_string(max) + ".");

      return reiksme;
    } catch (const runtime_error &ex) {
      cerr << "Klaida: " << ex.what() << "\n";
    }
  }
}

string generuotiFaila(int studentuSkaicius, int namuDarbuSkaicius) {
  const string dirPath = "../generatedData/";
  create_directories(dirPath);

  const string failoPavadinimas = "studentai" + to_string(studentuSkaicius);
  ofstream failas("../generatedData/" + failoPavadinimas + ".txt");

  if (!failas.is_open())
    throw runtime_error("Klaida: nepavyko atidaryti failo irasymui.");

  failas << left << setw(20) << "Vardas" << setw(20) << "Pavarde";

  for (int i = 1; i <= namuDarbuSkaicius; i++) {
    failas << right << setw(10) << "ND" + to_string(i);
  }
  failas << right << setw(10) << " Egz." << "\n";

  for (int i = 0; i < studentuSkaicius; i++) {
    failas << left << setw(20) << "VardasNR" + to_string(i + 1) << setw(20)
           << "PavardeNR" + to_string(i + 1);

    failas << right;
    for (int j = 0; j < namuDarbuSkaicius; j++) {
      failas << setw(10) << randomInt(1, 10);
    }
    failas << setw(10) << randomInt(1, 10) << "\n";
  }

  cout << ">Isvesta i " + failoPavadinimas << endl;
  return failoPavadinimas;
}

// 1 Strategija
void skaidytiStudentus1(StudentuKonteineris &studentai,
                        StudentuKonteineris &vargsiukai,
                        StudentuKonteineris &kietiakai) {
  for (const Studentas &studentas : studentai) {
    if (studentas.getGalutinisVidurkis() < 5) {
      vargsiukai.push_back(studentas);
    } else {
      kietiakai.push_back(studentas);
    }
  }
}

// 2 Strategija
void skaidytiStudentus2(StudentuKonteineris &studentai,
                        StudentuKonteineris &kietiakai) {
  while (studentai.back().getGalutinisVidurkis() >= 5 && !studentai.empty()) {
    kietiakai.push_back(studentai.back());
    studentai.pop_back();
  }
}

// 3 Strategija
void skaidytiStudentus3(StudentuKonteineris &studentai,
                        StudentuKonteineris &vargsiukai,
                        StudentuKonteineris &kietiakai) {
  auto riba = stable_partition(
      studentai.begin(), studentai.end(),
      [](const Studentas &s) { return s.getGalutinisVidurkis() < 5; });

  copy(studentai.begin(), riba, back_inserter(vargsiukai));
  copy(riba, studentai.end(), back_inserter(kietiakai));
}

void failuGeneravimas() {
  int studentuSkaicius = skaitytiSkaiciu(
      "Iveskite studentu skaiciu (1 - 10 000 000):\n", 1, 10000000);
  int namuDarbuSkaicius =
      skaitytiSkaiciu("Iveskite namu darbu skaiciu (1 - 100):\n", 1, 100);

  string failoPavadinimas;
  try {
    failoPavadinimas = generuotiFaila(studentuSkaicius, namuDarbuSkaicius);
  } catch (const runtime_error &ex) {
    cerr << "KLAIDA: " << ex.what() << "\n";
  }

  bool arPadalinti = skaitytiSkaiciu("Ar norite padalinti studentus (pagal "
                                     "vidurki)? (1 - Taip, 2 - Ne):\n",
                                     1, 2) == 1;

  if (arPadalinti) {
    StudentuKonteineris studentai;

    try {
      nuskaitytiFaila(studentai,
                      "../generatedData/" + failoPavadinimas + ".txt");
    } catch (const runtime_error &ex) {
      cerr << "KLAIDA: " << ex.what() << "\n";
    }
    suskaiciuotiGalutinius(studentai);

    StudentuKonteineris vargsiukai;
    StudentuKonteineris kietiakai;
    skaidytiStudentus1(studentai, vargsiukai, kietiakai);

    int input =
        skaitytiSkaiciu("Rusiuoti pagal (1 - vardas, 2 - pavarde, 3 - "
                        "galutinis (vidurkis), 4 - galutinis (mediana):\n",
                        1, 4);
    rusiuotiStudentus(vargsiukai, input);
    rusiuotiStudentus(kietiakai, input);

    isvestisFailas(vargsiukai, failoPavadinimas + "_vargsiukai.txt");
    isvestisFailas(kietiakai, failoPavadinimas + "_kietiakai.txt");
  }
}

void failoKurimoTestavimas() {
  int studentuSkaicius = skaitytiSkaiciu(
      "Iveskite studentu skaiciu (1 - 10 000 000):\n", 1, 10000000);
  int namuDarbuSkaicius =
      skaitytiSkaiciu("Iveskite namu darbu skaiciu (1 - 100):\n", 1, 100);

  Timer timer;
  try {
    generuotiFaila(studentuSkaicius, namuDarbuSkaicius);
  } catch (const runtime_error &ex) {
    cerr << "KLAIDA: " << ex.what() << "\n";
    return;
  }
  cout << fixed << setprecision(2);
  cout << "Failo sukurimo laikas: " << timer.elapsed() << " s" << endl;
}

void duomenuApdorojimoTestavimas() {
  const vector<string> failai = {
      "../archive/studentai1000.txt", "../archive/studentai10000.txt",
      "../archive/studentai100000.txt", "../archive/studentai1000000.txt",
      "../archive/studentai10000000.txt"};

  int input =
      skaitytiSkaiciu("Pasirinkite 1 - studentai1000.txt, 2 - "
                      "studentai10000.txt, 3 - studentai100000.txt, 4 - "
                      "studentai1000000.txt, 5 - studentai10000000.txt):\n",
                      1, 5);

  const string &pasirinktasFailas = failai[input - 1];
  cout << "Pasirinktas failas: " << pasirinktasFailas << "\n";

  StudentuKonteineris studentai;
  Timer totalTimer;
  Timer taskTimer;

  try {
    nuskaitytiFaila(studentai, pasirinktasFailas);
    cout << fixed << setprecision(3)
         << "Duomenu nuskaitymo is failo laikas: " << taskTimer.elapsed()
         << " s\n";
  } catch (const runtime_error &ex) {
    cerr << "Klaida skaitant faila: " << ex.what() << "\n";
    return;
  }

  taskTimer.reset();
  rusiuotiStudentus(studentai, 3);
  cout << "Studentu rusiavimo pagal vidurki laikas (sort): "
       << taskTimer.elapsed() << " s\n";

  StudentuKonteineris vargsiukai;
  StudentuKonteineris kietiakai;

  taskTimer.reset();
  // skaidytiStudentus1(studentai, vargsiukai, kietiakai);
  skaidytiStudentus2(studentai, kietiakai);
  // skaidytiStudentus3(studentai, vargsiukai, kietiakai);
  cout << "Studentu rusiavimo i dvi grupes laikas: " << taskTimer.elapsed()
       << " s\n";

  cout << "Pilnas veikimo laikas: " << totalTimer.elapsed() << " s\n";

  // studentai.clear();
  // isvestisFailas(vargsiukai, "../outputData/testas_vargsiukai.txt");
  // isvestisFailas(kietiakai, "../outputData/testas_kietiakai.txt");
}
void tikrinti(bool condition) {
  std::cout << (condition ? "[PASS] " : "[FAIL] ") << "\n";
}

void ruleOfFiveTestas() {

  // Default konstruktorius
  Studentas s1;
  tikrinti(s1.getVardas() == "");
  tikrinti(s1.getPavarde() == "");
  tikrinti(s1.getNamuDarbai() == 0);
  tikrinti(s1.getPazymiai().empty());
  tikrinti(s1.getEgzaminoBalas() == 0);
  tikrinti(s1.getGalutinisVidurkis() == 0.0);
  tikrinti(s1.getGalutinisMediana() == 0.0);

  // Parameterizuotas konstruktorius
  Studentas s2("Jonas", "Jonaitis", 3, {8, 9, 7}, 10);
  tikrinti(s2.getVardas() == "Jonas");
  tikrinti(s2.getPavarde() == "Jonaitis");
  tikrinti(s2.getNamuDarbai() == 3);
  tikrinti(s2.getPazymiai()[0] == 8);
  tikrinti(s2.getPazymiai()[1] == 9);
  tikrinti(s2.getPazymiai()[2] == 7);
  tikrinti(s2.getEgzaminoBalas() == 10);

  // Kopijavimo konstruktorius
  Studentas s3(s2);
  tikrinti(s3.getVardas() == "Jonas");
  tikrinti(s3.getPavarde() == "Jonaitis");
  tikrinti(s3.getNamuDarbai() == 3);
  tikrinti(s3.getPazymiai()[0] == 8);
  tikrinti(s3.getPazymiai()[1] == 9);
  tikrinti(s3.getPazymiai()[2] == 7);
  tikrinti(s3.getEgzaminoBalas() == 10);
  s3.setVardas("Petras");
  tikrinti(s3.getVardas() == "Petras");

  // Kopijavimo priskyrimo operatorius
  Studentas s4;
  s4 = s2;
  tikrinti(s4.getVardas() == "Jonas");
  tikrinti(s4.getPavarde() == "Jonaitis");
  tikrinti(s4.getNamuDarbai() == 3);
  tikrinti(s4.getPazymiai()[0] == 8);
  tikrinti(s4.getPazymiai()[1] == 9);
  tikrinti(s4.getPazymiai()[2] == 7);
  tikrinti(s4.getEgzaminoBalas() == 10);
  s4 = s4;
  tikrinti(s4.getVardas() == "Jonas");

  // Perkelimo konstruktorius
  Studentas s5(move(s2));
  tikrinti(s5.getVardas() == "Jonas");
  tikrinti(s5.getPavarde() == "Jonaitis");
  tikrinti(s5.getNamuDarbai() == 3);
  tikrinti(s5.getPazymiai()[0] == 8);
  tikrinti(s5.getPazymiai()[1] == 9);
  tikrinti(s5.getPazymiai()[2] == 7);
  tikrinti(s5.getEgzaminoBalas() == 10);

  // Perkelimo priskyrimo operatorius
  Studentas s6("Tomas", "Tomaitis", 2, {6, 7}, 8);
  Studentas s7;
  s7 = move(s6);
  tikrinti(s7.getVardas() == "Tomas");
  tikrinti(s7.getPavarde() == "Tomaitis");
  tikrinti(s7.getNamuDarbai() == 2);
  tikrinti(s7.getPazymiai()[0] == 6);
  tikrinti(s7.getPazymiai()[1] == 7);
  tikrinti(s7.getEgzaminoBalas() == 8);

  tikrinti(s6.getVardas() == "");
  tikrinti(s6.getPavarde() == "");
  tikrinti(s6.getNamuDarbai() == 0);
  tikrinti(s6.getPazymiai().empty());
  tikrinti(s6.getEgzaminoBalas() == 0);
}

void testuotiGreiti() {
  int input = skaitytiSkaiciu(
      "Pasirinkite (1 - failo kurimo testas, 2 - "
      "duomenu apdorojimo testas, 3 - \"Rule of five\" testas):\n",
      1, 2);

  switch (input) {
  case 1:
    failoKurimoTestavimas();
    break;
  case 2:
    duomenuApdorojimoTestavimas();
    break;
  case 3:
    ruleOfFiveTestas();
    break;
  default:
    cout << "Neteisingas pasirinkimas!\n";
  }
}

void failoNuskaitymas(StudentuKonteineris &studentai) {
  Timer timer;
  try {
    // nuskaitytiFaila(studentai, "../data/kursiokai.txt");
    // nuskaitytiFaila(studentai, "../data/studentai10000.txt");
    nuskaitytiFaila(studentai, "../data/studentai100000.txt");
    // nuskaitytiFaila(studentai, "../data/studentai1000000.txt");
  } catch (const runtime_error &ex) {
    cerr << "KLAIDA: " << ex.what() << "\n";
  }

  cout << fixed << setprecision(2);
  cout << "Nuskaitymo laikas: " << timer.elapsed() << " s\n";
}

void failoDuomenuApdorojimas(StudentuKonteineris &studentai) {
  suskaiciuotiGalutinius(studentai);
  surusiuotiPagalPasirinkima(studentai);

  int input = skaitytiSkaiciu(
      "Pasirinkite isvedima (1 - Failas, 2 - Konsole):\n", 1, 2);

  switch (input) {
  case 1:
    isvestisFailas(studentai, "output.txt");
    break;
  case 2:
    isvestisKonsole(studentai);
    break;
  default:
    cout << "Neteisingas pasirinkimas!\n";
    break;
  }
}

void studentuDuomenuApdorojimas(StudentuKonteineris &studentai) {
  bool arMediana = suskaiciuotiGalutini(studentai);
  isvestis(studentai, arMediana);
}