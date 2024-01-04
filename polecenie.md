# Faza 1: Generator labiryntu
Utworzyć generator labiryntów (od 5x5 do 10x10), który generuje labirynt który ma: <br/>
* jedno wejście (na górze) jedno wyjście (na dole)
* nie ma zamkniętych przestrzeni w środku
* przejścia znajdują się tylko w pionie i poziomie (nie po przekątnej)

# Faza 2: Implementacja grafu
Zastosować implementację grafu zgodną z opisem zadania
* generator wag wierzchołków
* macierz sąsiedztwa

# Faza 3: Wyszukiwanie min. ścieżki
Implementować algorytm wyszukiwania minimalnej ścieżki w grafie (wg. sumy wag od startu do końca), pokazać przebytą ścieżkę
* dijkstra
* wyświetlanie najkrótszej ścieżki (wagi)