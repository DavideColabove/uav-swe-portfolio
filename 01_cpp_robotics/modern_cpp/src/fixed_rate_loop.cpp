#include <iostream>
#include <thread>
#include <chrono>
#include <vector>
#include <numeric>
#include <algorithm>
#include <cstdio>

// Configurazione dei loop
constexpr int RATE_100_HZ = 100;
constexpr int RATE_400_HZ = 400;
constexpr int NUM_CYCLES = 10000;

void run_jitter_test(int target_hz, const std::string& name) {
    // TODO: Calcola l'intervallo ideale in nanosecondi in base a target_hz
    // Usa std::chrono::nanoseconds
    const auto ideal_interval = std::chrono::nanoseconds(1'000'000'000) / target_hz;

    
    std::vector<int64_t> jitters_ns;
    jitters_ns.reserve(NUM_CYCLES);

    printf("[%s] Executing loop at %d Hz...\n", name.c_str(), target_hz);

    // TODO: Prendi il tempo corrente usando std::chrono::steady_clock come 'next_wakeup'
    auto next_wakeup = std::chrono::steady_clock::now();

    for (int i = 0; i < NUM_CYCLES; ++i) {
        // TODO: 1. Incrementa 'next_wakeup' sommandogli l'intervallo ideale 
        // (Nota: incrementiamo il tempo target invece di prendere il tempo corrente
        // per evitare che i micro-ritardi si accumulino in un "drift" a lungo termine)
        next_wakeup += ideal_interval;
        
        // TODO: 2. Metti a dormire il thread fino a 'next_wakeup' usando std::this_thread::sleep_until
        
        // TODO: 3. Appena sveglio, registra il tempo reale ('actual_wakeup')
        
        // TODO: 4. Calcola il jitter come (actual_wakeup - next_wakeup) in nanosecondi
        
        // TODO: 5. Inserisci il jitter nel vettore 'jitters_ns'
    }

    // TODO: Itera sul vettore per calcolare la media (usa std::abs per sommare il jitter 
    // assoluto, visto che a volte il SO potrebbe svegliare il thread in anticipo) e trova
    // il picco massimo assoluto (Max Overrun).

    // TODO: Stampa l'Average Jitter e il Max Overrun in millisecondi
}

int main() {
    printf("--- JITTER TEST (Standard OS Scheduler) ---\n\n");
    
    // TODO: Lancia la funzione per il rate a 100 Hz
    
    // TODO: Lancia la funzione per il rate a 400 Hz

    return 0;
}