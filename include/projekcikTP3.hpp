#pragma once
#include <vector>
#include <complex>

// Deklaracje funkcji sygnałów
void Sinus(double frequency, double start_time, double end_time, int sample_count);
void Cosinus(double frequency, double start_time, double end_time, int sample_count);
void Rectangular(double frequency, double start_time, double end_time, int sample_count);
void Sawtooth(double frequency, double start_time, double end_time, int sample_count);
void DFT(const std::vector<double>& input);
void I_DFT(const std::vector<std::complex<double>>& spectrum);
