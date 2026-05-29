#include "Studentas.h"
#include "functions.h"
#include "timer.h"

using std::cout;

/**
 * @brief Pagrindinė programos funkcija, kuri leidžia vartotojui pasirinkti
 * įvairias operacijas su studentų duomenimis, įskaitant įvedimą, generavimą,
 * failų skaitymą ir rašymą, bei greičio testavimą.
 *
 * Vartotojas gali pasirinkti:
 * 1 - įvesti studento duomenis ranka,
 * 2 - generuoti tik pažymius,
 * 3 - generuoti studento vardus, pavardes ir pažymius,
 * 4 - nuskaityti studentų duomenis iš failo,
 * 5 - generuoti failą su studentų duomenimis,
 * 6 - testuoti programos greitį,
 * 7 - baigti darbą.
 *
 * Programa naudoja Studentas klasę, kuri paveldi iš abstrakčios Zmogus klasės,
 * ir įvairias funkcijas duomenų apdorojimui bei failų operacijoms.
 *
 * @return int Programos pabaigos kodas (0 reiškia sėkmingą pabaigą).
 */
int main() {

  // Klaida: negalima sukurti Zmogus objekto, nes tai yra abstrakti klasė
  // Zmogus zmogus;
  // Zmogus *z = new Zmogus();

  StudentuKonteineris studentai;
  int input;

  do {
    input = skaitytiSkaiciu(
        "Pasirinkite (1 - ranka, 2 - generuoti tik pažymius, 3 - generuoti "
        "studentų vardus, pavardės ir pažymius, 4 - nuskaityti failą, 5 - "
        "generuoti faila, 6 - testuoti greiti, 7 - baigti darbą):\n",
        1, 7);

    switch (input) {
    case 1:
      studentai.push_back(ivestisRanka());
      studentuDuomenuApdorojimas(studentai);
      break;
    case 2:
      studentai.push_back(generuotiPazymius());
      studentuDuomenuApdorojimas(studentai);
      break;
    case 3:
      studentai.push_back(generuotiStudenta());
      studentuDuomenuApdorojimas(studentai);
      break;
    case 4: {
      failoNuskaitymas(studentai);
      failoDuomenuApdorojimas(studentai);
      break;
    }
    case 5:
      failuGeneravimas();
      break;
    case 6:
      testuotiGreiti();
      break;
    case 7:
      break;
    default:
      cout << "Neteisingas pasirinkimas!\n";
    }

  } while (input != 7);
}