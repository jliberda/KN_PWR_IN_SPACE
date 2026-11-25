# (English ver)
# ESP32: Rocket Configuration in NVS Memory.
## Description:
The project allows saving, reading, modifying and deleting data (int, float, bool, str) in the NVS memory of the ESP32 board.

The project contains three modules:
- module "storage" for storing and modifying data.
- module "cli" for modifying data using the terminal.
- module "validate" for validation of data entered by the user.

Taking into account Flash limitations: a limited number of write cycles and the necessity of
erasing entire sectors
is implemented in storage_set_default

## Requirements:
- ESP-IDF v6.1.
- (I used the Wokwi simulator for testing. (in the browser. build/uf2.bin file))

## How to use?
### save (int/float/bool/str) (key) (value)
Saves a variable of the selected type with the name (key) and value (value) in the ESP32 memory.
### default
Restores the board memory to example default values.
### read (key)
Reads a variable with the name (key). Prints its value and type in the format:
`
key (type)
`
### delete (key)
Deletes a variable with the name (key) from the NVS of the ESP32 board.
### list
Prints the entire contents of the board memory.
### exit
Interrupts the CLI.

## Notes
Key: max. 15 characters. An incorrect command, missing arguments, a non-existing key and an incorrect value (e.g. "save int x abc") give an error message.

## Flash Limitations
Flash can only be erased in entire sectors (4 KB), erasing uses up flash memory. Therefore, NVS does not overwrite values, but adds new entries and erases a sector only when it becomes full, distributing wear evenly (wear leveling).

Therefore, "storage_set_default" erases only its own namespace ("nvs_erase_all"), not the entire partition. The entire partition is erased only by "storage_init", when NVS reports no free pages or a newer data format.

## Unit Tests
The validate_* functions are tested using the "assert" command in main.c. I also tested the CLI manually in the Wokwi simulator.

## Contact
jliberda.kontakt@gmail.com


# (Polska wer)
# ESP32: Konfiguracja rakiety w pamięci NVS.
## Opis:
Projekt pozwala zapisywać, odczytywać, modyfikować i usuwać dane (int, float, bool, str) w pamięci NVS płytki ESP32.

Projekt zawiera trzy moduły:
- moduł "storage" do przechowywania i modyfikacji danych.
- moduł "cli" do modyfikowania danych za pomocą terminala.
- moduł "validate" do walidacji wprowadzanych przez użytkownika danych.

 Uwzględnienie ograniczeń Flash: ograniczona liczba cykli zapisu i konieczność 
kasowania całych sektorów
w storage_set_default jest uwzględnione

## Wymagania:
- ESP-IDF v6.1.
- (Użyłam symulatora Wokwi do testowania. (w przeglądarce. plik build/uf2.bin))

## Jak używać?
### save (int/float/bool/str) (klucz) (wartość)
Zapisuje zmienną wybranego typu o nazwie (klucz) mającą wartość (wartość) w pamięci ESP32.
### default
Przywraca pamięć płytki do przykładowych wartości domyślnych.
### read (klucz)
Odczytuje zmienną o nazwie (klucz). Wypisuje jej wartość i typ w formacie:
`
klucz (typ)
`
### delete (klucz)
Usuwa zmienną o nazwie (klucz) z NVS płytki ESP32.
### list
Wypisuje całą zawartość pamięci płytki ESP32.
### exit
Przerywa CLI.

## Notatki
Klucz: maks. 15 znaków. Błędna komenda, brak argumentów, nieistniejący klucz i błędna wartość (np. "save int x abc") dają komunikat błędu.

## Ograniczenia Flash
Flash kasuje tylko całymi sektorami (po 4 KB), kasowanie zużywa pamięć flash. Dlatego NVS nie nadpisuje wartości, a dopisuje nowe wpisy i kasuje sektor dopiero po zapełnieniu, rozkładając zużycie równomiernie (wear leveling).

Dlatego "storage_set_default" kasuje tylko własny namespace ("nvs_erase_all"), a nie całą partycję. Całą partycję kasuje wyłącznie "storage_init"", gdy NVS zgłosi brak wolnych stron lub nowszy format danych.

## Testy jednostkowe
Funkcje validate_* są testowane za pomocą komendy "assert" w main.c. Testowałam również CLI ręcznie w symulatorze Wokwi.

## Kontakt
jliberda.kontakt@gmail.com
