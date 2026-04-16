Jeśli pliki cpp i hpp mają znajdować się w oddzielnych folderach:
src/ – tu trafiają pliki .cpp.
include/ – tu lądują pliki .hpp.
Wtedy w pliku cpp robisz:
#include "../include/mini_vector.hpp"
