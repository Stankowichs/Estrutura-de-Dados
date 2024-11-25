#include "tad.h"

int main() {
    VetorLivros *vec = createVector(3);
    print(vec);

    append(vec, 3.1);
    append(vec, 2.5);
    append(vec, 4.7);

    print(vec);
    return 0;
}