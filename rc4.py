def ksa(khoa: str) -> list:
    khoa_dai = len(khoa)
    S = list(range(256))
    j = 0
    for i in range(256):
        j = (j + S[i] + ord(khoa[i % khoa_dai])) % 256
        S[i], S[j] = S[j], S[i]
    return S

def prga(S: list, do_dai_text: int) -> list:
    i = 0
    j = 0
    dongkhoa = []
    for _ in range(do_dai_text):
        i = (i + 1) % 256
        j = (j + S[i]) % 256
        S[i], S[j] = S[j], S[i]
        dongkhoa.append(S[(S[i] + S[j]) % 256])
    return dongkhoa

def rc4_ma_hoa(khoa: str, text: str) -> str:
    S = ksa(khoa)
    dongkhoa = prga(S, len(text))
    banma = []
    for i in range(len(text)):
        banma.append(chr(ord(text[i]) ^ dongkhoa[i]))
    return ''.join(banma), dongkhoa

khoa = "nqphu"
text = "Hanoi University of Science and Technology"
banma, dongkhoa = rc4_ma_hoa(khoa, text)

print("Dongkhoa:", dongkhoa)
print("Banma:", ''.join([hex(ord(c))[2:].zfill(2) for c in banma]))
