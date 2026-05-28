// Zmogus.h
#pragma once
#include <string>

class Zmogus {
protected:
  std::string vardas_;
  std::string pavarde_;

public:
  Zmogus() : vardas_(""), pavarde_("") {};

  Zmogus(const std::string &vardas, const std::string &pavarde)
      : vardas_(vardas), pavarde_(pavarde) {};

  virtual ~Zmogus() = default;

  virtual void WhoamI() const = 0;

  std::string getVardas() const { return vardas_; }
  std::string getPavarde() const { return pavarde_; }

  void setVardas(const std::string &v) { vardas_ = v; }
  void setPavarde(const std::string &p) { pavarde_ = p; }
};