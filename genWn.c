#include <math.h>
#include <stdint.h>
#include <stdio.h>

#define PI 3.14159265358979323846  // Más preciso que 3.15
#define N 256
#define FFT_SCALE 8

typedef struct {
    int32_t Re;
    int32_t Im;
} complex;

complex Wn[N];

int main() {
    FILE *file = fopen("twiddle_table.txt", "w");
    if (file == NULL) {
        perror("Error al abrir el archivo");
        return 1;
    }

    for (int k = 0; k < N/2; k++) {
        Wn[k].Re = (int32_t)round(cos(-2.0 * PI * k / N) * (1 << FFT_SCALE));
        Wn[k].Im = (int32_t)round(sin(-2.0 * PI * k / N) * (1 << FFT_SCALE));

        fprintf(file, "{ %d, %d },\n", Wn[k].Re, Wn[k].Im);
    }

    fclose(file);
    return 0;
}

