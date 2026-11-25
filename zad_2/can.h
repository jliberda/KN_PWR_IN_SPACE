#include <vector>
#include <string>
using namespace std;

const double bitrate = 500; // kbit/s

struct can_message {
    const char *modul;
    const char *title;
    int id;
    int size; // rozmiar danych w bajtach
    int freq; // częstotliwość generowania wiadomości
    int deadline; // czas od wygenerowania do dostarczenia
    int generation_time; // czas wygenerowania wiadomości
};

struct stats {
    double avg_latency; // srednie opóźnienie
    double max_latency; // maksymalne opóźnienie
    int late_count; // liczba wiadomości po terminie
    double total_latency;
    int total_count;
};

void generate_messages(int current_time, can_message messages[], size_t size, vector<can_message> &queue);
can_message arbitrate(vector<can_message> &queue);
double transmission_time_ms(int total_bits);
int cnt_stuff_bits(const string bits);

// w uproszczeniu
struct can_frame {
    string bits;
    size_t stuff_bits;
    size_t total_bits;
};

string hex_to_bin(int num, int goal_len);
can_frame build_frame(const can_message message);