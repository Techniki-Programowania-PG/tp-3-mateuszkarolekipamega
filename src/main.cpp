#include "../matplotplusplus/source/matplot/matplot.h"
#include <cmath>
#include <vector>
#include <iostream>

using namespace std;

int Sinus(double freq) {
    using namespace matplot;

    // Zakres czasu (np. 0 do 1 sekundy)
    std::vector<double> x;
    std::vector<double> y;

    double sampling_rate = 1000; // 1000 próbek na sekundę
    double duration = 1.0;       // czas trwania sygnału w sekundach

    for (int i = 0; i < duration * sampling_rate; ++i) {
        double t = i / sampling_rate;
        x.push_back(t);
        y.push_back(std::sin(2 * pi * freq * t));
    }

    // Rysowanie wykresu
    plot(x, y);
    title("Wykres funkcji sinusoidalnej");
    xlabel("Czas [s]");
    ylabel("Amplituda");
    grid(on);

    show();

    return 0;
}

int Cosinus(double freq) {
    using namespace matplot;

    // Zakres czasu (np. 0 do 1 sekundy)
    std::vector<double> x;
    std::vector<double> y;

    double sampling_rate = 1000; // 1000 próbek na sekundę
    double duration = 1.0;       // czas trwania sygnału w sekundach

    for (int i = 0; i < duration * sampling_rate; ++i) {
        double t = i / sampling_rate;
        x.push_back(t);
        y.push_back(std::cos(2 * pi * freq * t));
    }

    // Rysowanie wykresu
    plot(x, y);
    title("Wykres funkcji cosinusoidalnej");
    xlabel("Czas [s]");
    ylabel("Amplituda");
    grid(on);

    show();

    return 0;
}

//narazie dalem int main aby testowac funkcje
int main() {

    double freq_choice;

    std::cout << "Podaj częstotliwość (Hz): ";
    std::cin >> freq_choice;
    
    //Cosinus(freq_choice);
    //Sinus(freq_choice);

    return 0;
}