#include "Studentas.h"
#include "functions.h"
#include "timer.h"

using std::cerr;
using std::cout;
using std::endl;
using std::fixed;
using std::runtime_error;
using std::setprecision;
using std::vector;

int main()
{
    Studentas studentas;
    StudentuKonteineris studentai;
    int input;

    do
    {
        input = skaitytiSkaiciu("Pasirinkite (1 - ranka, 2 - generuoti tik pažymius, 3 - generuoti studentų vardus, pavardės ir pažymius, 4 - nuskaityti failą, 5 - generuoti faila, 6 - testuoti greiti, 7 - baigti darbą):\n", 1, 7);

        switch (input)
        {
        case 1:
            ivestisRanka(studentas);
            studentai.push_back(studentas);
            studentas = {};
            studentuDuomenuApdorojimas(studentai);
            break;
        case 2:
            generuotiPazymius(studentas);
            studentai.push_back(studentas);
            studentas = {};
            studentuDuomenuApdorojimas(studentai);
            break;
        case 3:
            generuotiStudenta(studentas);
            studentai.push_back(studentas);
            studentas = {};
            studentuDuomenuApdorojimas(studentai);
            break;
        case 4:
        {
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