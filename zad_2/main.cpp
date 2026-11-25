#include <iostream>
#include "can.h"
using namespace std;

int main() {
    can_message messages[] = {
        {"Silnik", "Temperatura", 0x010, 4, 10, 50, 0},
        {"Silnik", "Ciśnienie", 0x020, 4, 20, 10, 0},
        {"Zasilanie", "Napięcie akumulatora", 0x100, 2, 100, -1, 0},
        {"Nawigacja", "Pozycja GPS", 0x200, 8, 200, 100, 0},
        {"Diagnostyka", "Status systemu", 0x300, 4, 500, -1, 0},

        {"Zasilanie", "Prąd", 0x110, 2, 100, 300, 0},
        {"Nawigacja", "Sygnał", 0x230, 1, 100, 200, 0},
        {"Silnik", "Prędkość", 0x030, 2, 50, 200, 0}
    };

    size_t n = sizeof(messages)/sizeof(messages[0]); // liczba wiadomości w tablicy messages.

    vector<can_message> queue;
    can_message cur;
    bool transmitting = false;
    vector<stats> statistics(n);
    int simulation_time = 10000; // ms 
    double can_free = 0; // ms 
    
    // krok: z dokładnością co do 0.01 ms.
    // t = 1 oznacza 0.01 ms.
    for (int t = 0; t <= simulation_time*100 || transmitting || !queue.empty(); t++) {
        // generuj tylko na pęłnej milisekundzie t%100 == 0.
        if (t <= simulation_time*100 && t%100 == 0) {generate_messages(t/100, messages, n, queue);}

            if (transmitting && t/100.0 >= can_free) {
                double latency = can_free - cur.generation_time;

                size_t i = 0;
                while (messages[i].id != cur.id) {i++;}

                statistics[i].total_latency += latency;
                statistics[i].total_count++;
                if (latency > statistics[i].max_latency) {statistics[i].max_latency = latency;}

                if (cur.deadline != -1 && latency > cur.deadline) {statistics[i].late_count++;}

                transmitting = false;
            }

            if (!transmitting && !queue.empty()) {
                cur = arbitrate(queue);
                can_frame frame = build_frame(cur);
                can_free = t/100.0 + transmission_time_ms(frame.total_bits);
                transmitting = true;
                }
            }

    
    cout << "\n--------- Statistics ---------\n";
    for (size_t i = 0; i < sizeof(messages)/sizeof(messages[0]); i++) {
        if (statistics[i].total_count > 0) {statistics[i].avg_latency = statistics[i].total_latency / statistics[i].total_count;}

        cout << "\n" << messages[i].title << "\n";
        cout << "Average latency: " << statistics[i].avg_latency << " ms\n";
        cout << "Max latency: " << statistics[i].max_latency << " ms\n";
        cout << "Late messages: " << statistics[i].late_count << "\n";
    }
}