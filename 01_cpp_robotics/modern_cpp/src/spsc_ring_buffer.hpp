#pragma once
#include <array>
#include <atomic>
#include <cstddef>
#include <new>  // per hardware_destructive_interference_size (C++17/20)
#include <optional>

// Capacità deve essere potenza di 2 per ottimizzare il modulo con la maschera bitwise
template <typename T, size_t Capacity>
class SpscRingBuffer {
    static_assert((Capacity != 0) && ((Capacity & (Capacity - 1)) == 0),
                  "Capacity must be a power of 2");

public:
    SpscRingBuffer() : head_(0), tail_(0) {}

    // TODO: Implementare il push lock-free
    // Ritorna true se inserito, false se la coda è piena
    bool push(const T& item) {
        // 1. Leggi head_ (che memory order?)
        size_t current_head = head_.load(std::memory_order_relaxed);
        // 2. Leggi tail_ (che memory order?)
        size_t current_tail = tail_.load(std::memory_order_acquire);
        // 3. Calcola next_head
        size_t next_head = (current_head + 1) & (Capacity - 1);
        // 4. Verifica se c'è spazio
        if (next_head == current_tail) {
            return false;
        }
        // 5. Scrivi il dato nel buffer
        buffer_[current_head] = item;
        // 6. Aggiorna head_ (che memory order?)
        head_.store(next_head, std::memory_order_release);

        return false;
    }

    // TODO: Implementare il pop lock-free
    // Ritorna il dato se presente, std::nullopt se vuota
    std::optional<T> pop() {
        // 1. Leggi tail_
        size_t current_tail = tail_.load(std::memory_order_relaxed);
        // 2. Leggi head_
        size_t current_head = head_.load(std::memory_order_acquire);
        // 3. Verifica se la coda è vuota (head == tail)
        if (current_head == current_tail) {
            return std::nullopt;
        }
        // 4. Leggi il dato dal buffer
        T item = buffer_[current_tail];
        // 5. Aggiorna tail_
        size_t next_tail = (current_tail + 1) & (Capacity - 1);
        tail_.store(next_tail, std::memory_order_release);
        return item;
    }

private:
    // Suggerimento: usa alignas(64) per separare head_ e tail_ su cache line diverse
    // ed evitare il "False Sharing" tra il core del producer e quello del consumer.

    alignas(64) std::atomic<size_t> head_;
    alignas(64) std::atomic<size_t> tail_;

    // Il buffer pre-allocato. Nessuna allocazione deve avvenire dopo la costruzione.
    std::array<T, Capacity> buffer_;
};