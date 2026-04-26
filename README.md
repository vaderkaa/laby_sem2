### Organizacja plików projektu (tak na wypadek)

Jeśli pliki `.cpp` i `.hpp` mają znajdować się w oddzielnych folderach:

* `src/` – tu trafiają pliki źródłowe `.cpp`.
* `include/` – tu lądują pliki nagłówkowe `.hpp`.

Wtedy w pliku `.cpp` dołączasz nagłówek w ten sposób:
```cpp
#include "../include/mini_vector.hpp"
