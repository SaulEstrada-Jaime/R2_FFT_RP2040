//Funciones para la permutacion de bits y datos dentro del arreglo
void swap(float* a, float* b) {
    float temp = *a;
    *a = *b;
    *b = temp;}
// Invierte los bits de 'x' con una cantidad de bits 'bits'
unsigned int reverse_bits(unsigned int x, unsigned int bits) {
    unsigned int result = 0;
    for (unsigned int i = 0; i < bits; i++) {
        result = (result << 1) | (x & 1);
        x >>= 1;
    }
    return result;
}
// Reordena un arreglo de tamaño N en orden de bits invertidos
// Ya esta el reorden de los datos para las operaciones mariposa
void bit_reversal_permutation(float* x, unsigned int N) {
    unsigned int bits = (int)log2(N); //<---- log2 de N
    for (unsigned int i = 0; i < N; i++) {
        unsigned int j = reverse_bits(i, bits);
        if (j > i) {
            swap(&x[i], &x[j]);
        }
    }
}