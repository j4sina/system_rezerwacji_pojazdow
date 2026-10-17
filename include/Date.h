#pragma once

#include <string>

struct Date {
    int dzien;
    int miesiac;
    int rok;

    Date(int d = 1, int m = 1, int r = 2026)
        : dzien(d), miesiac(m), rok(r) {}
};
