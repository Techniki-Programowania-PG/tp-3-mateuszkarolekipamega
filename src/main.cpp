#include "../matplotplusplus/source/matplot/matplot.h"
#include <cmath>
#include <vector>
#include <iostream>
#include <complex>
#include <initializer_list>

using namespace std;

using Complex = complex<double>;
const double PI = 3.141592653589793;

// Funkcja obliczająca i wyświetlająca DFT oraz IDFT
void DFT(const std::vector<double>& input) {
    vector<double> signal(input);
    int N = signal.size();
    vector<Complex> spectrum(N);

    // Obliczanie DFT
    for (int k = 0; k < N; ++k) {
        Complex sum(0.0, 0.0);
        for (int n = 0; n < N; ++n) {
            double angle = -2 * PI * k * n / N;
            sum += signal[n] * exp(Complex(0, angle));
        }
        spectrum[k] = sum;
    }

    // Wyświetlanie widma
    cout << "Widmo (DFT):" << endl;
    for (const auto& c : spectrum) {
        cout << c << endl;
    }

    // Odwrotna transformata
    vector<double> back2normal_signal(N);
    for (int n = 0; n < N; ++n) {
        Complex sum(0.0, 0.0);
        for (int k = 0; k < N; ++k) {
            double angle = 2 * PI * k * n / N;
            sum += spectrum[k] * exp(Complex(0, angle));
        }
        back2normal_signal[n] = sum.real() / N;
    }

    // Wyświetlanie odzyskanego sygnału
    cout << "\nOdzyskany sygnał (IDFT):" << endl;
    for (const auto& val : back2normal_signal) {
        cout << val << " ";
    }
    cout << endl << endl;
}

void Sinus(double frequency, double start_time, double end_time, int num_samples) {
    using namespace matplot;

    if (num_samples <= 1 || end_time <= start_time) {
        cerr << "Nieprawidłowe dane wejściowe.\n";
        return;
    }

    vector<double> t(num_samples);
    double dt = (end_time - start_time) / (num_samples - 1);
    for (int i = 0; i < num_samples; ++i)
        t[i] = start_time + i * dt;

    vector<double> y(num_samples);
    for (int i = 0; i < num_samples; ++i)
        y[i] = sin(2 * pi * frequency * t[i]);

    plot(t, y);
    title("Sygnał sinusoidalny");
    xlabel("Czas [s]");
    ylabel("Amplituda");
    grid(on);
    show();
}

void Cosinus(double frequency, double start_time, double end_time, int num_samples) {
    using namespace matplot;

    if (num_samples <= 1 || end_time <= start_time) {
        cerr << "Nieprawidłowe dane wejściowe.\n";
        return;
    }

    vector<double> t(num_samples);
    double dt = (end_time - start_time) / (num_samples - 1);
    for (int i = 0; i < num_samples; ++i)
        t[i] = start_time + i * dt;

    vector<double> y(num_samples);
    for (int i = 0; i < num_samples; ++i)
        y[i] = cos(2 * pi * frequency * t[i]);

    plot(t, y);
    title("Sygnał cosinusoidalny");
    xlabel("Czas [s]");
    ylabel("Amplituda");
    grid(on);
    show();
}

void Rectangular(double frequency, double start_time, double end_time, int num_samples) {
    using namespace matplot;

    if (num_samples <= 1 || end_time <= start_time) {
        cerr << "Nieprawidłowe dane wejściowe.\n";
        return;
    }

    vector<double> t(num_samples);
    double dt = (end_time - start_time) / (num_samples - 1);
    for (int i = 0; i < num_samples; ++i)
        t[i] = start_time + i * dt;

    vector<double> y(num_samples);
    for (int i = 0; i < num_samples; ++i) {
        double val = sin(2 * pi * frequency * t[i]);
        y[i] = (val >= 0 ? 1.0 : -1.0);
    }

    plot(t, y);
    title("Sygnał prostokątny");
    xlabel("Czas [s]");
    ylabel("Amplituda");
    grid(on);
    show();
}

void Sawtooth(double frequency, double start_time, double end_time, int num_samples) {
    using namespace matplot;

    if (num_samples <= 1 || end_time <= start_time) {
        cerr << "Nieprawidłowe dane wejściowe.\n";
        return;
    }

    vector<double> t(num_samples);
    double dt = (end_time - start_time) / (num_samples - 1);
    for (int i = 0; i < num_samples; ++i)
        t[i] = start_time + i * dt;

    vector<double> y(num_samples);
    for (int i = 0; i < num_samples; ++i) {
        double val = 2.0 * (frequency * t[i] - floor(frequency * t[i] + 0.5));
        y[i] = val;
    }

    plot(t, y);
    title("Sygnał piłokształtny");
    xlabel("Czas [s]");
    ylabel("Amplituda");
    grid(on);
    show();
}

// Przykład testowy w main:
int main() {
    DFT({1,2,5,9,2,3});
    Sinus(1.0, 0.0, 2.0, 100);
    Cosinus(2.0, 0.0, 1.0, 200);
    Rectangular(5.0, 0.0, 1.0, 500);
    Sawtooth(3.0, 0.0, 1.0, 300);
    return 0;
}
