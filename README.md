Sorki, masz rację – wklejam to tutaj w formie czystego kodu do bezpośredniego skopiowania (okienko `markdown`), żebyś nie musiał nic poprawiać.

```markdown
### Organizacja plików projektu (tak na wypadek)

Jeśli pliki `.cpp` i `.hpp` mają znajdować się w oddzielnych folderach:

* `src/` – tu trafiają pliki źródłowe `.cpp`.
* `include/` – tu lądują pliki nagłówkowe `.hpp`.

Wtedy w pliku `.cpp` dołączasz nagłówek w ten sposób:
```cpp
#include "../include/mini_vector.hpp"

```

```cpp
template<typename T>
class vector {
  std::unique_ptr<T[]> data;
  void push_back(const T& val);
};

```

### Szablony i Zarządzanie Pamięcią

#### Inteligentne wskaźniki (`std::unique_ptr`)

Kiedy tworzysz obiekt przez `new`, musisz pamiętać o `delete`. Jeśli zapomnisz – masz wyciek pamięci.
`unique_ptr` robi to automatycznie. Gdy obiekt `vector` przestaje istnieć (kończy się jego zasięg), `unique_ptr` sam "sprząta" pamięć, której używał.

* **Słowo `unique**`: Oznacza, że tylko jeden wskaźnik na raz może posiadać dany zasób.
* **Nawiasy kwadratowe `[]**`: Informują kompilator, że ten wskaźnik nie zarządza jednym pojedynczym obiektem, ale całą tablicą obiektów.
* **Typ `T**`: Jeśli stworzyłeś `vector<int>`, to tutaj `T` staje się `int`.

#### Przenoszenie zasobów (`std::move`)

```cpp
pair(T t, U u) : t(std::move(t)), u(std::move(u)) {}

```

* **Bez `std::move**`: Kompilator musiałby zrobić drugą kopię. To tak, jakbyś miał dokument w ręku, podszedł do kserokopiarki, zrobił kopię i włożył ją do segregatora, a oryginał wyrzucił do kosza sekundę później (bo funkcja się kończy). To strata czasu i papieru.
* **Z `std::move**`: Mówisz kompilatorowi: „Ej, te lokalne zmienne `t` i `u` i tak za chwilę znikną, bo kończy się konstruktor. Nie kopiuj ich. Po prostu zabierz im zawartość i daj moim polom w klasie”.

#### Przykład użycia w funkcji `swap`

```cpp
template<typename T>
void swap(T& a, T& b) {
    T tmp = std::move(a);
    a = std::move(b);
    b = std::move(tmp);
}

```

#### Typy zwracane i Referencje (`&`)

* **T / U**: To typy danych, które zdefiniowałeś w szablonie. Jeśli Twoja para to `pair<int, string>`, to `first()` zwróci `int`, a `second()` zwróci `string`.
* **& (Referencja)**: To jest tu najważniejsze. Funkcja nie zwraca kopii tego, co jest w środku, ale oryginał.
* **Dlaczego to ważne?**: Gdyby nie było `&`, funkcja robiłaby kserokopię danych. Jeśli Twoim danym byłoby np. zdjęcie o rozmiarze 10MB, każde wywołanie `first()` zajmowałoby nową pamięć i czas procesora. Dzięki `&` dostajesz "bezpośredni wgląd" do zmiennej wewnątrz obiektu.

```

```
