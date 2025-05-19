#include "../matplotplusplus/source/matplot/matplot.h"
#include <cmath>
#include <vector>
#include <iostream>
#include <complex>
#include <initializer_list>

using namespace std;

using Complex = complex<double>;
const double PI = 3.141592653589793;

// Funkcja obliczająca i wyświetlająca DFT
void DFT(const vector<double>& input) {
    int N = input.size();
    vector<Complex> out(N);

    for (int k = 0; k < N; ++k) {
        Complex sum(0.0, 0.0);
        for (int n = 0; n < N; ++n) {
            double angle = -2 * PI * k * n / N;
            sum += input[n] * exp(Complex(0, angle));
        }
        if (abs(sum.imag()) < 1e-4)
            sum = Complex(sum.real(), 0.0);
        out[k] = sum;
    }

    cout << "Widmo DFT: ";
    for (const auto& val : out)
        cout << val << " ";
    cout << endl;
}

// Funkcja I_DFT
void I_DFT(const vector<Complex>& spectrum) {
    int N = spectrum.size();
    vector<double> signal(N);

    for (int n = 0; n < N; ++n) {
        Complex sum(0.0, 0.0);
        for (int k = 0; k < N; ++k) {
            double angle = 2 * PI * k * n / N;
            sum += spectrum[k] * exp(Complex(0, angle));
        }
        signal[n] = sum.real() / N;
    }

    cout << "Sygnał po I_DFT: ";
    for (const auto& val : signal)
        cout << val << " ";
    cout << endl;
}

// Filtrowanie niskich częstotliwości
void FiltreLowFrequencies(vector<Complex>& out, double threshold) {
    int N = out.size();
    int g = 1;
    int cutoff = static_cast<int>(threshold * N);

    for (int k = 1; k <= cutoff; ++k) {
        out[0] = 0;
        out[k - 1] = 0;
        if (g == 1) {
            out[N - k] = 0;
            g = 0;
        }
        out[N - k - 1] = 0;
    }

    cout << "Sygnał po filtracji: ";
    for (const auto& val : out)
        cout << val << " ";
    cout << endl;
}

// I_DFT z filtrem
void I_DFTFiltre(const vector<Complex>& spectrum) {
    int N = spectrum.size();
    vector<double> signal(N);

    for (int n = 0; n < N; ++n) {
        Complex sum(0.0, 0.0);
        for (int k = 0; k < N; ++k) {
            double angle = 2 * PI * k * n / N;
            sum += spectrum[k] * exp(Complex(0, angle));
        }
        signal[n] = sum.real() / N;
    }

    cout << "Sygnał po I_DFT (po filtracji): ";
    for (const auto& val : signal)
        cout << val << " ";
    cout << endl;
}

// Funkcja pełnego przetwarzania: DFT + filtracja + odwrotność
void DFTFiltre_Reversed(const vector<double>& signal) {
    int N = signal.size();
    vector<Complex> out(N);

    for (int k = 0; k < N; ++k) {
        Complex sum(0.0, 0.0);
        for (int n = 0; n < N; ++n) {
            double angle = -2 * PI * k * n / N;
            sum += signal[n] * exp(Complex(0, angle));
        }
        if (abs(sum.imag()) < 1e-4)
            sum = Complex(sum.real(), 0.0);
        out[k] = sum;
    }

    FiltreLowFrequencies(out, 0.2);
    I_DFTFiltre(out);
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
    DFT({1, 2, 5, 9, 2, 3});
    I_DFT({{1, 0}, {6, 3}, {9, 2}, {-8, 2}, {22, 3}, {0, 0}});
    DFTFiltre_Reversed({1, 2, 5, 9, 2, 3});
    Sinus(1.0, 0.0, 2.0, 100);
    Cosinus(2.0, 0.0, 1.0, 200);
    Rectangular(5.0, 0.0, 1.0, 500);
    Sawtooth(3.0, 0.0, 1.0, 300);
    return 0;
}
