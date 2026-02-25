# Hill Cipher — Encryption & Decryption in C

A clean, from-scratch implementation of the **Hill Cipher** — one of the earliest polygraphic substitution ciphers in classical cryptography — written entirely in C.

---

## What Is the Hill Cipher?

The Hill Cipher was invented by mathematician Lester S. Hill in 1929. Instead of encrypting letters one by one like Caesar or Vigenère, it works on **blocks of letters at a time** using linear algebra. The key is a matrix, and encryption is simply multiplying that matrix by a vector of letter values, modulo 26.

This makes it significantly harder to crack through simple frequency analysis, since each encrypted letter depends on multiple plaintext letters simultaneously.

---

## How It Works

### Encryption

1. Convert each letter to a number — `A/a = 0`, `B/b = 1`, …, `Z/z = 25`.
2. Arrange the plaintext into column vectors of size **n** (where **n** is the key matrix dimension).
3. If the plaintext length isn't divisible by **n**, pad it with `A` (or `a` for lowercase).
4. Multiply each vector by the **n × n key matrix** and take the result **mod 26**.
5. Convert numbers back to letters — that's your ciphertext.

### Decryption

Decryption is the reverse: multiply the ciphertext vectors by the **inverse of the key matrix** (mod 26). Computing this inverse involves:

- Finding the **determinant** of the key matrix.
- Building the **cofactor matrix**.
- **Transposing** it to get the adjugate.
- Multiplying by the **modular inverse** of the determinant mod 26.

> ⚠️ The key matrix must have a **non-zero determinant**, and that determinant must be **coprime with 26** — otherwise the cipher can't be decrypted and the program will ask you to enter a different key.

---

## Project Structure

```
Hill-Encryption-Algorithm/
├── hill_Encryption.c   # Encrypts a plaintext word using the Hill Cipher
└── Decryption.c        # Decrypts a ciphertext word back to plaintext
```

---

## Prerequisites

All you need is a C compiler. [GCC](https://gcc.gnu.org/) works perfectly:

```bash
# Check if GCC is installed
gcc --version
```

---

## Compilation

```bash
# Compile the encryption program
gcc hill_Encryption.c -o encrypt

# Compile the decryption program
gcc Decryption.c -o decrypt
```

---

## Usage

### Encrypting a Message

```bash
./encrypt
```

The program will prompt you step by step:

```
sifrelemek isteiginiz kelimeyi giriniz  : HELLO
anahatarin (satir ve sutun) sayisini giriniz = 2
1-1 = 3
1-2 = 3
2-1 = 2
2-2 = 5

sifrelenen kelime : GNLLE
```

- Enter the **word** you want to encrypt.
- Enter the **matrix size** (e.g., `2` for a 2×2 key).
- Fill in the **key matrix** values row by row.
- The encrypted word is printed at the end.

---

### Decrypting a Message

```bash
./decrypt
```

```
anahtarin (satir ve sutun) sayisini giriniz = 2
1_1 = 3
1_2 = 3
2_1 = 2
2_2 = 5
asli istenen kelimeyi giriniz : GNLLE

asil kelime: HELLO
```

- Enter the **same key matrix** that was used during encryption.
- Enter the **ciphertext** to decrypt.
- The original word is recovered and printed.

---

## Supported Input

| Feature | Details |
|---|---|
| Letter case | Uppercase (`A–Z`) and lowercase (`a–z`) both supported |
| Matrix size | Any square matrix (2×2, 3×3, etc.) |
| Padding | Short inputs are automatically padded with `A`/`a` |
| Invalid keys | The decryption program rejects keys with a zero or non-invertible determinant |

---

## Example Walkthrough

Let's encrypt the word **"ACT"** using the key matrix:

```
Key =  | 6  24  1 |
       | 13 16 10 |
       | 20 17 15 |
```

**Step 1 — Convert letters to numbers:**
```
A=0, C=2, T=19  →  vector [0, 2, 19]
```

**Step 2 — Multiply key × vector (mod 26):**
```
(6×0 + 24×2 + 1×19)  mod 26 = 67  mod 26 = 15  →  P
(13×0 + 16×2 + 10×19) mod 26 = 222 mod 26 = 14  →  O
(20×0 + 17×2 + 15×19) mod 26 = 319 mod 26 = 7   →  H
```

**Result:** `ACT` → `POH`

To get `ACT` back, run the decryption program with the same key and input `POH`.

---

## Notes & Limitations

- The programs use `gets()` and `scanf()` for input — these are straightforward for learning purposes but not suitable for production use.
- Only **alphabetic characters** (A–Z, a–z) are handled. Numbers, spaces, and special characters are not supported.
- Uppercase and lowercase are treated separately — mixing them in a single word may produce unexpected results.
- The key matrix size is capped at 100×100 internally, but realistic use cases will be 2×2 or 3×3.

---

## Background

This project was written as an educational exercise to demonstrate how classical cryptographic algorithms are implemented at a low level. It's a great starting point if you want to understand the math behind symmetric-key ciphers before jumping into modern algorithms like AES.

---

## License

This project is open source and free to use for learning and academic purposes.
