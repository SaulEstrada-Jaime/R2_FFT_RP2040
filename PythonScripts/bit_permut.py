def reverse_bits(n, bits):
    result = 0
    for i in range(bits):
        result = (result << 1) | (n & 1)
        n >>= 1
    return result

N = 256
bits = N.bit_length() - 1  # log2(N)

filename = "bit_reverse_table.txt"

with open(filename, "w") as f:
    f.write("// Tabla de bit reversal para FFT de 256 puntos\n")
    f.write("const uint8_t bit_reverse_table[{}] = {{\n".format(N))
    
    for i in range(N):
        reversed_i = reverse_bits(i, bits)
        f.write("{:3d},".format(reversed_i))
    
    f.write("};\n")

print(f"Archivo generado: {filename}")
