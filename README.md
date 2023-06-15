# Programowanie imperatywne
Repozytorium zawiera moje rozwiązania zadań z przedmiotu Programowanie Imperatywne z semestru letniego 2023 z platformy UPEL.
# Budowanie rozwiązań
Aby zbudować rozwiązanie wystarczy posiadać program CMake - wbudowany w IDE Clion. Istnieje też wersja standalone.</br>
Na systemie Linux jest szansa na błąd linkowania w rozwiązaniach korzystających z biblioteki math.h. Wtedy w pliku
CMakeLists.txt znajdującym się w danym folderze z rozwiązaniem należy dopisać następującą linijkę: </br>
`target_link_libraries(P_12_listy_dwukierunkowe m)`
