#include "functions.h"
#include "Studentas.h"
#include "timer.h"
#include <iostream>

using std::cerr;
using std::cin;
using std::cout;
using std::endl;
using std::fixed;
using std::ifstream;
using std::istringstream;
using std::left;
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
  string vardas;
  switch (randomInt(0, 9)) {
  case 0:
    vardas = "Irma";
    break;
  case 1:
    vardas = "Alma";
    break;
  case 2:
    vardas = "Irena";
    break;
  case 3:
    vardas = "Egle";
    break;
  case 4:
    vardas = "Jolanta";
    break;
  case 5:
    vardas = "Petras";
    break;
  case 6:
    vardas = "Jonas";
    break;
  case 7:
    vardas = "Ignas";
    break;
  case 8:
    vardas = "Darius";
    break;
  case 9:
    vardas = "Simas";
    break;
  }

  string pavarde;
  switch (*vardas.rbegin()) {
  case 's':
    switch (randomInt(0, 4)) {
    case 0:
      pavarde = "Pavardenis1";
      break;
    case 1:
      pavarde = "Pavardenis2";
      break;
    case 2:
      pavarde = "Pavardenis3";
      break;
    case 3:
      pavarde = "Pavardenis4";
      break;
    case 4:
      pavarde = "Pavardenis5";
      break;
    }
    break;
  default:
    switch (randomInt(0, 4)) {
    case 0:
      pavarde = "Pavardaite1";
      break;
    case 1:
      pavarde = "Pavardaite2";
      break;
    case 2:
      pavarde = "Pavardaite3";
      break;
    case 3:
      pavarde = "Pavardaite4";
      break;
    case 4:
      pavarde = "Pavardaite5";
      break;
    }
    break;
  };

  int namuDarbai = 5;
  vector<int> pazymiai;
  for (int i = 0; i < namuDarbai; i++) {
    int randPazymys = randomInt(1, 10);
    pazymiai.push_back(randPazymys);
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

  Studentas studentas;
  studentas.setNamuDarbai(namuDarbai);
  while (studentas.readStudent(failas, namuDarbai)) {
    studentai.push_back(studentas);
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

  // studentai.clear();
  // isvestisFailas(vargsiukai, "../outputData/testas_vargsiukai.txt");
  // isvestisFailas(kietiakai, "../outputData/testas_kietiakai.txt");
}

void testuotiGreiti() {
  int input = skaitytiSkaiciu(
      "Pasirinkite (1 - failo kurimo testas, 2 - duomenu apdorojimo testas):\n",
      1, 2);

  switch (input) {
  case 1:
    failoKurimoTestavimas();
    break;
  case 2:
    duomenuApdorojimoTestavimas();
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