#include <algorithm>
#include <chrono>
#include <cstdio>
#include <iostream>
#include <numeric>
#include <thread>
#include <vector>

// Configurazione dei loop
constexpr int RATE_100_HZ = 100;
constexpr int RATE_400_HZ = 400;
constexpr int NUM_CYCLES = 1000;

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

        // TODO: 2. Metti a dormire il thread fino a 'next_wakeup' usando
        // std::this_thread::sleep_until
        std::this_thread::sleep_until(next_wakeup);

        // TODO: 3. Appena sveglio, registra il tempo reale ('actual_wakeup')
        auto actual_wakeup = std::chrono::steady_clock::now();

        // TODO: 4. Calcola il jitter come (actual_wakeup - next_wakeup) in nanosecondi
        auto jitter =
            std::chrono::duration_cast<std::chrono::nanoseconds>(actual_wakeup - next_wakeup)
                .count();

        // TODO: 5. Inserisci il jitter nel vettore 'jitters_ns'
        jitters_ns.push_back(jitter);
    }

    int64_t sum = 0;
    int64_t overrun = 0;

    for (int i = 0; i < NUM_CYCLES; ++i) {
        sum += std::abs(jitters_ns[i]);
        if (std::abs(jitters_ns[i]) > overrun) {
            overrun = std::abs(jitters_ns[i]);
        }
    }

    std::cout << " Avg : " << (sum / NUM_CYCLES) / 1'000'000.0 << "\n";
    std::cout << " Overrun : " << overrun / 1'000'000.0 << "\n";

    // TODO: Itera sul vettore per calcolare la media (usa std::abs per sommare il jitter
    // assoluto, visto che a volte il SO potrebbe svegliare il thread in anticipo) e trova
    // il picco massimo assoluto (Max Overrun).

    // TODO: Stampa l'Average Jitter e il Max Overrun in millisecondi
}

int main() {
    printf("--- JITTER TEST (Standard OS Scheduler) ---\n\n");

    // TODO: Lancia la funzione per il rate a 100 Hz
    run_jitter_test(RATE_100_HZ, "Test 100Hz");
    // TODO: Lancia la funzione per il rate a 400 Hz
    run_jitter_test(RATE_400_HZ, "Test 400Hz");
    return 0;
}