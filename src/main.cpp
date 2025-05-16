#include "../matplotplusplus/source/matplot/matplot.h"
#include <cmath>
#include <vector>
#include <iostream>

using namespace std;

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
    Sinus(1.0, 0.0, 2.0, 100);
    Cosinus(2.0, 0.0, 1.0, 200);
    Rectangular(5.0, 0.0, 1.0, 500);
    Sawtooth(3.0, 0.0, 1.0, 300);
    return 0;
}
