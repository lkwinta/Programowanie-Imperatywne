# Programowanie imperatywne
Repozytorium zawiera moje rozwiązania zadań z przedmiotu Programowanie Imperatywne z semestru letniego 2023 z platformy UPEL.
# Budowanie rozwiązań
Aby zbudować rozwiązanie wystarczy posiadać program CMake - wbudowany w IDE Clion. Istnieje też wersja standalone.</br>
Na systemie Linux jest szansa na błąd linkowania w rozwiązaniach korzystających z biblioteki math.h. Wtedy w pliku
CMakeLists.txt znajdującym się w danym folderze z rozwiązaniem należy dopisać następującą linijkę: </br>
`target_link_libraries(<nazwa_podprojektu> m)` </br>
Przykładowo plik z taką modyfikacją powinien wyglądać następująco:
```cmake
#CMakeLists.txt

cmake_minimum_required(VERSION 3.24)
project(<nazwa_podprojektu> C)

set(CMAKE_C_STANDARD 99)

add_executable(<nazwa_podprojektu> main.c)
target_link_libraries(<nazwa_podprojektu> m)
install(TARGETS <nazwa_podprojektu> RUNTIME DESTINATION bin)
```
