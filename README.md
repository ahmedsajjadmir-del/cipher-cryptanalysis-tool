# cipher-cryptanalysis-tool
A program resposible for cryptoanalysis , and usage of different ciphers .

# CipherLens: Interactive Text Cipher & Cryptanalysis Tool

A C++ command-line tool that encrypts and decrypts text using classical ciphers
and performs cryptanalysis (frequency analysis and automatic cipher cracking).

**Course:** Computer Programming (1st Semester, BSE)
**University:** Bahria University, Islamabad
**Submission Deadline:** December 11, 2026

## Team Members

| Name | Registration No. | Section | GitHub Username | Role |
|------|------------------|---------|-----------------|------|
| Ahmed Sajjad | 09-131262-011 | BSE-1A | `ahmedsajjadmir-del` | Group leader: ciphers, menu, file handling |
| Maryam Rizwan | 09-131262-043 | BSE-1A | `maryamrizwangul-star` | Cryptanalysis, utilities, testing |

## Features

- Caesar, Vigenère, and keyed substitution ciphers (encrypt and decrypt)
- Letter-frequency analysis with a text histogram
- Automatic Caesar cipher cracker using chi-squared scoring
- Vigenère key-length estimation using Index of Coincidence
- Save and load messages and a session log (file handling)

## C++ Concepts Used

- **Loops and conditionals:** menu system, cipher processing, brute-force shifts
- **Functions:** modular design across multiple `.cpp`/`.h` files
- **Arrays:** character buffers, frequency arrays (`int counts[26]`)
- **Pointers:** pointer arithmetic for string traversal, passing structs by pointer
- **Structures:** `Message`, `FreqProfile`, `CrackResult`
- **File handling:** saving and loading session data

## Project Structure

```
├── src/        Source code (.cpp / .h)
├── docs/       Project report
├── tests/      Sample test cases
└── README.md
```

## How to Compile and Run

**Requirements:** a C++ compiler (g++ 7 or later).

```bash
# Clone the repository
git clone https://github.com/<ahmedsajjadmir-del>/cipher-cryptanalysis-tool.git
cd cipher-cryptanalysis-tool

# Compile
g++ src/*.cpp -o cipherlens

# Run (Linux / macOS)
./cipherlens

# Run (Windows)
cipherlens.exe
```

## Sample Usage

```
=========== CipherLens ===========
1. Encrypt text
2. Decrypt text
3. Frequency analysis
4. Crack Caesar cipher
...
Choice: 4
Enter ciphertext: WKLV LV D VHFUHW
Best shift: 3
Recovered text: THIS IS A SECRET
```

## Report

The full project report is available in the [`docs/`](docs/) folder.
