#pragma once
#include <vector>
#include <complex>

using namespace std;

// Deklaracje funkcji sygnałów
void Sinus(double frequency, double start_time, double end_time, int sample_count);
void Cosinus(double frequency, double start_time, double end_time, int sample_count);
void Rectangular(double frequency, double start_time, double end_time, int sample_count);
void Sawtooth(double frequency, double start_time, double end_time, int sample_count);
void DFT(const std::vector<double>& input);
void I_DFT(const std::vector<std::complex<double>>& spectrum);
void DFTFiltre_Reversed(const std::vector<double>& input);
void FiltreLowFrequencies(std::vector<std::complex<double>>& out, double threshold);
void I_DFTFiltre(const std::vector<std::complex<double>>& spectrum);
void Filter1D(const vector<double>& signal, int window_size);
