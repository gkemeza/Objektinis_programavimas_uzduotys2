# Naudojimosi instrukcija

1 - pilnas studento ivedimas (vardas, pavarde, pazymiai)\
2 - pusiau automatinis studento ivedimas (pazymiai susigeneruoja)\
3 - pilnai automatinis studento generavimas\
4 - failo nuskaitymas, duomenu rusiavimas ir isvedimas\
5 - sugeneruoti pasirinkto dydzio faila\
6 - testuoti failo sparta\
7 - isjungti programa

# Įdiegimo instrukcija

git clone --branch v1.1 https://github.com/gkemeza/Objektinis_programavimas_uzduotys2.git
cd Objektinis_programavimas_uzduotys2
mkdir build && cd build
cmake ..
cmake --build .

**Windows paleidimas:**\
Debug\Darbas_su_studentais.exe

**Linux/Mac paleidimas:**\
./Darbas_su_studentais

# V1.1

**CPU:** AMD Ryzen™ 5 PRO 7540U
**SSD:** Micron_2400_MTFDKBA1T0QFM
**RAM:** 16GB

### Palyginimas struct ir class naudojant vector ir 2 strategija

### struct

| Operacija      | 100 000 | 1 000 000 |
| :------------- | ------: | --------: |
| Veikimo laikas | 1.181 s |  15.721 s |

### class

| Operacija      | 100 000 | 1 000 000 |
| :------------- | ------: | --------: |
| Veikimo laikas | 1.181 s |  15.721 s |

### O1 flag

| Operacija      | 100 000 | 1 000 000 |
| :------------- | ------: | --------: |
| Veikimo laikas | 1.181 s |  15.721 s |

### O2 flag

| Operacija      | 100 000 | 1 000 000 |
| :------------- | ------: | --------: |
| Veikimo laikas | 1.181 s |  15.721 s |

### O3 flag

| Operacija      | 100 000 | 1 000 000 |
| :------------- | ------: | --------: |
| Veikimo laikas | 1.181 s |  15.721 s |

# V1.0

Pridetas spartos testavimas su skirtingais konteineriais, 3 strategijos, README.md aprasymai prie kiekvieno release, naudojimosi instrukcija.

### Testavimo sistemos parametrai

**CPU:** Intel core i5-10210U
**SSD:** WDC PC SN520
**RAM:** 8GB

### Spartos testavimas su skirtingais konteineriais

### 1 strategija (studentai konteinerio skaidymas į du naujus to paties tipo konteinerius)

### std::vector

| Operacija               |   1 000 |  10 000 | 100 000 | 1 000 000 | 10 000 000 |
| :---------------------- | ------: | ------: | ------: | --------: | ---------: |
| Nuskaitymas is failo    | 0.004 s | 0.027 s | 0.148 s |   1.181 s |   15.721 s |
| Rusiavimas (sort asc)   | 0.005 s | 0.025 s | 0.345 s |   4.096 s |   55.102 s |
| Skirstymas i dvi grupes | 0.002 s | 0.008 s | 0.064 s |   0.616 s |    9.542 s |

### std::list

| Operacija               |   1 000 |  10 000 | 100 000 | 1 000 000 | 10 000 000 |
| :---------------------- | ------: | ------: | ------: | --------: | ---------: |
| Nuskaitymas is failo    | 0.007 s | 0.030 s | 0.161 s |   1.168 s |   12.997 s |
| Rusiavimas (sort asc)   | 0.001 s | 0.005 s | 0.096 s |   1.256 s |   17.955 s |
| Skirstymas i dvi grupes | 0.001 s | 0.005 s | 0.068 s |   0.702 s |    9.144 s |

### std::deque

| Operacija               |   1 000 |  10 000 | 100 000 | 1 000 000 | 10 000 000 |
| :---------------------- | ------: | ------: | ------: | --------: | ---------: |
| Nuskaitymas is failo    | 0.002 s | 0.014 s | 0.120 s |   0.993 s |   14.062 s |
| Rusiavimas (sort asc)   | 0.003 s | 0.032 s | 0.340 s |   4.529 s |   61.390 s |
| Skirstymas i dvi grupes | 0.001 s | 0.003 s | 0.036 s |   0.373 s |    6.825 s |

1 strategijos skaidymas i du konteinerius greiciausiai veikia su deque konteineriu.

### 2 strategija (studentai konteinerio skirstymas panaudojant tik vieną naują konteinerį)

### std::vector

| Operacija               |   1 000 |  10 000 |   100 000 |  1 000 000 | 10 000 000 |
| :---------------------- | ------: | ------: | --------: | ---------: | ---------: |
| Skirstymas i dvi grupes | 0.072 s | 6.371 s | 725.941 s | netestuota | netestuota |

### std::list

| Operacija               |   1 000 |  10 000 | 100 000 | 1 000 000 | 10 000 000 |
| :---------------------- | ------: | ------: | ------: | --------: | ---------: |
| Skirstymas i dvi grupes | 0.001 s | 0.006 s | 0.037 s |   0.354 s |    4.514 s |

### std::deque

| Operacija               |   1 000 |  10 000 | 100 000 | 1 000 000 | 10 000 000 |
| :---------------------- | ------: | ------: | ------: | --------: | ---------: |
| Skirstymas i dvi grupes | 0.000 s | 0.003 s | 0.027 s |   0.307 s |    5.019 s |

2 strategijoje pagreiteja sparta su list ir deque, bet stipriai suleteja vector.

### 3 strategija (skaidymas į du konteinerius, panaudojant stable_partition(), copy() ir back_inserter())

### std::vector

| Operacija               |   1 000 |  10 000 | 100 000 | 1 000 000 | 10 000 000 |
| :---------------------- | ------: | ------: | ------: | --------: | ---------: |
| Skirstymas i dvi grupes | 0.002 s | 0.010 s | 0.116 s |   1.060 s |   12.980 s |

### std::list

| Operacija               |   1 000 |  10 000 | 100 000 | 1 000 000 | 10 000 000 |
| :---------------------- | ------: | ------: | ------: | --------: | ---------: |
| Skirstymas i dvi grupes | 0.002 s | 0.011 s | 0.128 s |   1.305 s |   15.276 s |

### std::deque

| Operacija               |   1 000 |  10 000 | 100 000 | 1 000 000 | 10 000 000 |
| :---------------------- | ------: | ------: | ------: | --------: | ---------: |
| Skirstymas i dvi grupes | 0.002 s | 0.007 s | 0.076 s |   0.849 s |   11.546 s |

3 strategijos visu konteineriu sparta yra mazesne uz pirmos strategijos.

## V0.4

Pridetas failu generavimas, studentu skirstymas i dvi kategorijas, spartos tyrimai ir CMake failas

[1 TYRIMAS] Failo sukurimo vidurkiai (3 bandymai, 3 ND):

1000 studentu - 0.07 s

![alt text](images/image-6.png)

10000 studentu - 0.44 s

![alt text](images/image-5.png)

100000 studentu - 4.5 s

![alt text](images/image-4.png)

1000000 studentu - 46 s

![alt text](images/image-3.png)

10000000 studentu - 463 s

![alt text](images/image-2.png)

[2 TYRIMAS] Duomenu apdorojimo vidurkiai (3 bandymai, 3 ND):

1000 studentu:
duomenu nuskaitymas is failo - 0.01 s
studentu rusiavimas i dvi grupes - 0.00 s
studentu isvedimas i du naujus failus - 0.01 s
viso testavimo veikimas - 0.02 s

![alt text](images/image-12.png)

10000 studentu:
duomenu nuskaitymas is failo - 0.03 s
studentu rusiavimas i dvi grupes - 0.01 s
studentu isvedimas i du naujus failus - 0.03 s
viso testavimo veikimas - 0.07 s

![alt text](images/image-10.png)

100000 studentu:
duomenu nuskaitymas is failo - 0.13 s
studentu rusiavimas i dvi grupes - 0.05 s
studentu isvedimas i du naujus failus - 0.16 s
viso testavimo veikimas - 0.36 s

![alt text](images/image-9.png)

1000000 studentu:
duomenu nuskaitymas is failo - 1.12 s
studentu rusiavimas i dvi grupes - 0.49 s
studentu isvedimas i du naujus failus - 1.60 s
viso testavimo veikimas - 3.34 s

![alt text](images/image-8.png)

10000000 studentu:
duomenu nuskaitymas is failo - 14.5 s
studentu rusiavimas i dvi grupes - 5.8 s
studentu isvedimas i du naujus failus - 19.15 s
viso testavimo veikimas - 39.45 s

![alt text](images/image-7.png)

## V0.3

Atliktas programos refactoring'as: prideti header failai ir isimciu gaudymas

## V0.2

Sioje versijoje atnaujinta tik vector versija ir pridetas failo nuskaitymas, duomenu rusiavimas

Failu nuskaitymo vidurkiai (5 bandymai):

1. 'studentai.txt' - 0.00 s

2. 'studentai10000.txt' - 0.44 s

3. 'studentai100000.txt' - 1.99 s

4. 'studentai1000000.txt' - 16.52 s

## V0.1

Pradine programa su dviem versijom (C kalbos masyvu ir vector).
