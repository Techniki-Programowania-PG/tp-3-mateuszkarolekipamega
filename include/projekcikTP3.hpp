#pragma once
#include <vector>
#include <initializer_list>

// Deklaracje funkcji sygnałów
void Sinus(double frequency, double start_time, double end_time, int sample_count);
void Cosinus(double frequency, double start_time, double end_time, int sample_count);
void Rectangular(double frequency, double start_time, double end_time, int sample_count);
void Sawtooth(double frequency, double start_time, double end_time, int sample_count);
void DFT(const std::vector<double>& input);
