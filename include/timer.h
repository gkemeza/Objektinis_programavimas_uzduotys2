#include <chrono>
using std::chrono::duration;
using std::chrono::high_resolution_clock;
using std::chrono::time_point;

/**
 * @brief Timer klasė, skirta matuoti laiką tarp operacijų.
 *
 * Ši klasė naudoja C++11 chrono biblioteką, kad galėtų tiksliai matuoti
 * laiką. Ji turi metodus laikui pradėti, iš naujo nustatyti ir gauti praėjusį
 * laiką sekundėmis.
 *
 * Timer klasė yra naudinga greičio testavimui ir optimizavimui, leidžiant
 * lengvai matuoti, kiek laiko užtrunka tam tikros operacijos ar funkcijos
 * vykdymas.
 *
 */
class Timer {
  using hrClock = high_resolution_clock;

private:
  time_point<hrClock> start;

public:
  Timer() : start{hrClock::now()} {}
  void reset() { start = hrClock::now(); }
  double elapsed() const {
    return duration<double>(hrClock::now() - start).count();
  }
};
