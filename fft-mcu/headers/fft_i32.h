#define FFT_N         256
#define FFT_ORDER     8
#define FFT_SCALE     8

typedef struct {
    int32_t Re;
    int32_t Im;
} complex;

typedef struct {
    uint16_t N;
    uint16_t order;
    uint8_t scale;
    const complex* twiddle_table; 
} fft_i32;

//---------------------------- OPERACIONES COMPLEJAS ----------------------------
complex dot_complex(complex z, complex w) {
    complex result;
    result.Re = (z.Re * w.Re - z.Im * w.Im) >> FFT_SCALE;
    result.Im = (z.Re * w.Im + z.Im * w.Re) >> FFT_SCALE;
    return result;
}

complex sum_complex(complex z, complex w) {
    return (complex){ z.Re + w.Re, z.Im + w.Im };
}

complex sub_complex(complex z, complex w) {
    return (complex){ z.Re - w.Re, z.Im - w.Im };
}
//---------------------------- PERMUTACIÓN BIT-REVERSAL POR USO DE TABLA----------------------------
void bit_reversal_permutation(const complex* input, complex* output, const uint16_t* bitrev_table, uint16_t N) {
    for(uint16_t i = 0; i < N; i++) {
        uint16_t j = bitrev_table[i];
        output[j] = input[i];
    }
}
//---------------------------- RADIX2 FFT ----------------------------
void fft_i32_radix_2(const fft_i32* ctx, complex* output, const complex* input, const uint16_t* bitrev_table) {
    complex bridge[FFT_N];
    bit_reversal_permutation(input, output, bitrev_table, ctx->N);

    for (uint16_t stage = 0; stage < ctx -> order; stage++) {
        uint16_t num_groups = 1 << (ctx -> order - stage - 1);
        uint16_t num_btfy   = 1 << stage;

        for (uint16_t group = 0; group < num_groups; group++) {
            for (uint16_t btfy = 0; btfy < num_btfy; btfy++) {
                uint16_t index1 = group * (num_btfy << 1) + btfy;
                uint16_t index2 = index1 + num_btfy;
                uint16_t twiddle_index = btfy * num_groups;

                complex Wn = ctx->twiddle_table[twiddle_index];
                complex wndot  = dot_complex(output[index2], Wn);

                bridge[index1] = sum_complex(output[index1], wndot);
                bridge[index2] = sub_complex(output[index1], wndot);
            }
        }
        for (uint16_t i = 0; i < ctx -> N; i++) { output[i] = bridge[i]; }
    }
}

