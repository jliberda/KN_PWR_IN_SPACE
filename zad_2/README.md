# (English ver)
# CAN Bus Simulation: Rocket Communication System.
## Description:
The project simulates communication between four rocket modules. Messagess are being sent with set frequency. Arbitration is based on message IDs.

The simulated modules are:
- Engine
- Navigation
- Diagnostics
- Power

The project contains:
- main.cpp - runs the simulation and displays statistics
- can.cpp - handy functions such as message generation, arbitration, frame building or bit stuffing.
- can.h - declares can.cpp's functions, implements structures.

## Requirements:
- C++ compiler e. g. GCC

## How to use?
compile:
`g++ main.cpp can.cpp -Wall -o main`
run:
`./main`

## CAN Configuration:
- CAN 2.0A
- Bitrate 500 kbit/s
- Simulation duration: 10 000 ms.

## Message ID Variants
(RESULTS.md file contains the statistics for Variants A, B and C)
Three different assignment strategies were tested:
- Variant A: Original
- Variant B: Longest deadline first
- Variant C: Shortest deadline first.

The purpose of this comparison is to examine whether the id's are optimal.

## Conclusions
In all three variants, the number of messages delivered after their deadlines was 0. No starvation was observed in the conducted simulations.

Latency is the time from message generation to the completion of its transmission. It includes waiting time in the queue and transmission time.

## Contact
jliberda.kontakt@gmail.com



# (Polska wer)
# ESP32: Konfiguracja rakiety w pamięci NVS.
# Symulacja magistrali CAN: System komunikacji rakiety

## Opis:
Projekt symuluje komunikację pomiędzy czterema modułami rakiety. Wiadomości są wysyłane z określoną częstotliwością. Arbitraż opiera się na ID wiadomości.

Symulowane moduły:
- Silnik
- Nawigacja
- Zasilanie
- Diagnostyka

Projekt zawiera:
- `main.cpp` – uruchamia symulację i wyświetla statystyki.
- `can.cpp` – funkcje pomocnicze, takie jak generowanie wiadomości, arbitraż, budowanie ramek czy bit stuffing.
- `can.h` – deklaruje funkcje z `can.cpp` i definiuje struktury.

## Wymagania:
- Kompilator C++ np. GCC.

## Jak używać?
Kompilacja:
`
g++ main.cpp can.cpp -Wall -o main
`

Uruchomienie:
`
./main
`

## Konfiguracja CAN:
- CAN 2.0A
- Prędkość transmisji: 500 kbit/s
- Czas trwania symulacji: 10 000 ms.

## Warianty identyfikatorów wiadomości
(Plik `RESULTS.md` zawiera statystyki dla wariantów A, B i C).

Przetestowano trzy różne strategie przydzielania identyfikatorów:
- Wariant A: Oryginalny.
- Wariant B: Najdłuższy deadline jako pierwszy.
- Wariant C: Najkrótszy deadline jako pierwszy.

Celem tego porównania jest sprawdzenie, czy identyfikatory są optymalne.

## Wnioski
We wszystkich trzech wariantach liczba wiadomości dostarczonych po deadline wyniosła 0. W przeprowadzonych symulacjach nie zaobserwowano zagłodzenia.

Latency oznacza czas od wygenerowania wiadomości do zakończenia jej transmisji.
can_free - generation_time. Obejmuje oczekiwanie w kolejce i transmisję.

## Kontakt
jliberda.kontakt@gmail.com