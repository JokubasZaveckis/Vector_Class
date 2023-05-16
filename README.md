# Vector_Class

Šis projektas padarytas isitikini, kas mano Vector konteineris veikia lygiai taip pat kaip ir std::vector. 
Buvo sukurta template klasė us reikalingais metodais, modifikacijomis iteratoriais ir tt. ir apkeista su normaliai naudojamu std::vektoriumi.

# Analizė:

Paprasų sveikųjų skaičių užpildymas:

Number of Elements    std::vector Time (ms)    myVector Time (ms)
-------------------   ---------------------   ------------------
10,000                0                        0
100,000               0                        0
100,000               3                        4
1,000,000             48                       39
10,000,000            484                      456

Kiek kartų įvyko atminties perskirstymai 10000000 elementų užpildyme:

Container        Number of Reallocations
--------------   ---------------------
std::vector      19
myVector         24

Skirtingų kodo vietų laiko užtrukimo layginimas naudojant įvairaus tipo kintamuosius:

Container        Operation      Time (s)
--------------   -------------  ---------
myVector         Nuskaitymas    0.32
myVector         Rikiavimas     0.02
myVector         Rusiavimas     0.01
myVector         Isvedimas      0.37
myVector         Programos trukme: 0.71
std::vector      Nuskaitymas    0.32
std::vector      Rikiavimas     0.03
std::vector      Rusiavimas     0.01
std::vector      Isvedimas      0.41
std::vector      Programos trukme: 0.76

Išvada: mano parašytas vektorius veikia pakankamai panašiai kaip ir std::vector konteineris.
