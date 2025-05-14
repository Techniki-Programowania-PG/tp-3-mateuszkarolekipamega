#include "../matplotplusplus/source/matplot/matplot.h"

int dodawanko(int a, int b){
    return a + b;
}

int main() {
    using namespace matplot;

    // przykład wykresu
    plot({1, 3, 2, 4, 5});
    title("Mój pierwszy wykres z matplot++");
    xlabel("oś X");
    ylabel("oś Y");
    show();

    return 0;
}