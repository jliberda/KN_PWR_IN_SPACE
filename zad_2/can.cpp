#include "can.h"

// adds messages to queue based on their frequency and time we're currently at.
void generate_messages(int current_time, can_message messages[], size_t size, vector<can_message> &queue) {
for (size_t i = 0; i < size; i++) {
    if (current_time % messages[i].freq == 0) {
        can_message message = messages[i];
        message.generation_time = current_time;
        queue.push_back(message);
        }
    }
}

// chooses message with the most priority and erases it from queue.
can_message arbitrate(vector<can_message> &queue) {
    size_t min_idx = 0;
    for (size_t i = 1; i < queue.size(); i++) {
        if (queue[i].id < queue[min_idx].id) {min_idx = i;}
    }
    can_message ans = queue[min_idx];
    queue.erase(queue.begin() + min_idx);
    return ans;
}

double transmission_time_ms(int total_bits) {
    int frame_bits = total_bits;
    // return frame_bits/bitrate; s
    return frame_bits/bitrate; // ms
}

int cnt_stuff_bits(const string bits) {
    int consecutive = 1;
    char prev = '\0';
    int stuff_bits = 0;
    
    for (char bit : bits) {
        if (bit == prev) {
            consecutive++;
        } else {
            prev = bit;
            consecutive = 1;
        }
        if (consecutive == 5) {
            stuff_bits++;
            prev = (bit == '0')? '1' : '0';
            consecutive = 1;
        }
    }
    return stuff_bits;
}

// działa na hex w formacie 0x. 0x... zamienia się na dec.
string hex_to_bin(int num, int goal_len) {
    string bits = "";
    while (num > 0) {
        bits = to_string(num%2) + bits;
        num /= 2;
    }
    return string(goal_len - bits.size(), '0') + bits;
}

string bytes_to_bin(int bytes, int goal_len) {
    string bin = "";
    while (bytes > 0) {
        bin = to_string(bytes%2) + bin;
        bytes /= 2;
    }
    return string(goal_len - bin.size(), '0') + bin;
}

// SOF – początek ramki, bit dominujący. 1 bit
// ID – identyfikator i priorytet wiadomości. 11 bitów
// RTR – rodzaj ramki. 0 ramka danych, 1 prośba o dane. 1 bit
// Control – IDE, r0, DLC - format ramki (0 - 2.0A lub 1 - 2.0B), reserved dom. bit, data len in bytes 0-9. 1+1+4 = 6 bitów.
// Data – właściwe dane. 0–64 bity
// CRC – suma kontrolna poprzednich pól += ogranicznik. 15+1 = 16 bitów.
// ACK – potwierdzenie CRC i sumy pól przed CRC. jeśli się zgadza, ramka nie została zakłucona, ogranicznik. 0 - zgadza się, 1 - nie zgadza się. 1+1 = 2 bity.
// EOF – koniec ramki. 7 bitów recesywnych.
// IFS 3 bity recesywne - przerwa między ramkami, nie jest częścią ramki. 3 bity.
// 1 + 11 + 1 + 6 + 16 + 2 + 7 + dane = 44 narzut + dane
can_frame build_frame(const can_message message) {
    can_frame frame;
    // narzut+dane = 44+64
    string bits = "0"; // SOF
    bits += hex_to_bin(message.id, 11); // ID
    bits += "0"; // RTR

    bits += "0"; // IDE -> CAN 2.0 A
    bits += "0"; // r0 -> zarezerwowany bit
    bits += bytes_to_bin(message.size, 4); // DLC

    bits += string(message.size*8, '0'); // Dane, przykładowe dane - "0"
    bits += string(15, '0'); // CRC, przykładowe CRC = "0", bez ogranicznika = nie podlega stuffingowi.

    size_t stuff_bits = cnt_stuff_bits(bits);

    // Reszta ramki - bez stuffingu
    size_t rest_bits = 1 + 2 + 7 + 3;

    frame = {bits, stuff_bits, bits.size() + stuff_bits + rest_bits};

    return frame;
}
