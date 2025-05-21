#include "../matplotplusplus/source/matplot/matplot.h"
#include "projekcikTP3.hpp"
#include <cmath>
#include <vector>
#include <iostream>
#include <complex>

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

void Filter1D(const vector<double>& signal, int window_size) {
    using namespace matplot;

    if (window_size < 1 || window_size % 2 == 0 || signal.size() < window_size) {
        cerr << "Nieprawidłowy rozmiar okna filtracji lub sygnał zbyt krótki.\n";
        return;
    }

    vector<double> filtered;
    int offset = window_size / 2;

    for (size_t i = 0; i < signal.size(); ++i) {
        double sum = 0.0;
        int count = 0;
        for (int j = -offset; j <= offset; ++j) {
            if (i + j >= 0 && i + j < signal.size()) {
                sum += signal[i + j];
                ++count;
            }
        }
        filtered.push_back(sum / count);
    }

    // wykres oryginału i przefiltrowanego sygnału
    auto t = linspace(0, signal.size() - 1, signal.size());
    plot(t, signal)->line_width(2).display_name("Oryginalny");
    plot(t, filtered)->line_width(2).display_name("Filtrowany");
    title("Filtracja 1D (średnia ruchoma)");
    xlabel("Index");
    ylabel("Amplituda");
    legend();
    grid(on);
    show();
}

// teraz filtered jest przekazywany przez referencję i modyfikowany wewnątrz
void Filter2D(const vector<vector<double>>& image, int window_size, vector<vector<double>>& filtered) {
    // using namespace matplot;
    if (window_size < 1 || window_size % 2 == 0) {
        cerr << "Nieprawidłowy rozmiar okna filtracji (musi być nieparzysty i >=1).\n";
        return;
    }
    if (image.empty() || image[0].empty()) {
        cerr << "Pusta macierz obrazu.\n";
        return;
    }
    int rows = (int)image.size();
    int cols = (int)image[0].size();
    if (rows < window_size || cols < window_size) {
        cerr << "Obraz zbyt mały w stosunku do rozmiaru okna filtracji.\n";
        return;
    }

    filtered.assign(rows, vector<double>(cols, 0.0));
    int offset = window_size / 2;

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            double sum = 0.0;
            int count = 0;
            for (int wi = -offset; wi <= offset; ++wi) {
                for (int wj = -offset; wj <= offset; ++wj) {
                    int ni = i + wi;
                    int nj = j + wj;
                    if (ni >= 0 && ni < rows && nj >= 0 && nj < cols) {
                        sum += image[ni][nj];
                        ++count;
                    }
                }
            }
            filtered[i][j] = sum / count;
        }
    }
}

void TestFilter2D(const vector<vector<double>>& image) {
   
    vector<vector<double>> filtered;

    int window_size = 3;
    Filter2D(image, window_size, filtered);

    cout << "Oryginalny obraz:\n";
    for (const auto& row : image) {
        for (double val : row) cout << val << "\t";
        cout << "\n";
    }

    cout << "\nObraz po filtracji 2D:\n";
    for (const auto& row : filtered) {
        for (double val : row) cout << val << "\t";
        cout << "\n";
    }
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

int main(){
    return 0;
}
