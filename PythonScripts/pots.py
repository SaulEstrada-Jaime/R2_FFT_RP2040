import math

N = 256
filename = "wn_neg_table.txt"

with open(filename, "w") as f:
    f.write("// Tabla de potencias de -Wn para FFT de 256 puntos\n")
    f.write("// Formato: { Re, Im }\n\n")
    f.write("const complex Wn_neg_table[{}] = {{\n".format(N // 2))
    for k in range(N):
        angle = 2 * math.pi * k / N  # nota: signo positivo para -Wn
        re = 10*math.cos(100*angle)
        im = 0
        f.write("    {{ {:.3f}f, {:.3f}f }},\n".format(re, im))
    f.write("};\n")

print(f"Archivo generado: {filename}")
