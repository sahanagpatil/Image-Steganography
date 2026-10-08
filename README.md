# Image Steganography using C

A C-based application for securely hiding and extracting secret information from BMP images using the Least Significant Bit (LSB) technique.

## Overview

**Image Steganography** is a C-based application that demonstrates how secret information can be hidden inside a BMP image without noticeable changes to its visual appearance.

The project uses the **Least Significant Bit (LSB)** technique to embed secret data into image pixel information and later extract the hidden data through the decoding process.

## Key Features

- 🔐 **Secret Data Hiding** – Embed text data inside a BMP image.
- 🔎 **Data Extraction** – Retrieve hidden information from an encoded image.
- 🖼️ **BMP Image Processing** – Supports BMP image files for encoding and decoding.
- ⚙️ **LSB Technique** – Uses Least Significant Bit manipulation for data hiding.
- 💻 **Command-Line Application** – Simple terminal-based execution.
- 🧩 **Modular Design** – Separate modules for encoding, decoding, and common operations.

## Technologies & Concepts

```text
┌─────────────────────────┬──────────────────────────────────┐
│ Programming Language    │ C                                │
├─────────────────────────┼──────────────────────────────────┤
│ Compiler                │ GCC                              │
├─────────────────────────┼──────────────────────────────────┤
│ File Handling           │ Binary & Text File Operations    │
├─────────────────────────┼──────────────────────────────────┤
│ Core Concepts           │ Pointers, Structures, Functions  │
├─────────────────────────┼──────────────────────────────────┤
│ Bit Manipulation        │ Bitwise Operations & LSB         │
├─────────────────────────┼──────────────────────────────────┤
│ Image Processing        │ BMP Image Handling               │
├─────────────────────────┼──────────────────────────────────┤
│ Design                  │ Modular Programming              │
└─────────────────────────┴──────────────────────────────────┘

Project Structure
┌── Image-Steganography/
│
├── 📄 encode.c
├── 📄 encode.h
├── 📄 decode.c
├── 📄 decode.h
├── 📄 common.h
├── 📄 types.h
├── 📄 test_encode.c
│
├── 🖼️ beautiful.bmp
├── 🔒 secret.txt
├── 🖼️ stego.bmp
└── 📄 output.txt

File Description

| File            | Description                            |
| --------------- | -------------------------------------- |
| `encode.c`      | Implements the data encoding process   |
| `encode.h`      | Function declarations for encoding     |
| `decode.c`      | Implements the data decoding process   |
| `decode.h`      | Function declarations for decoding     |
| `common.h`      | Common definitions and declarations    |
| `types.h`       | User-defined data types                |
| `test_encode.c` | Main program and command-line handling |

How It Works:
The project consists of two main operations: Encoding and Decoding
1. Encoding
The secret information is converted into binary data and embedded into the Least Significant Bits (LSBs) of the BMP image pixels.
┌─────────────────────┐
│    Source Image     │
│     BMP Image       │
└──────────┬──────────┘
           │
           │  + Secret Data
           ▼
┌─────────────────────┐
│      Encoding       │
│    LSB Technique    │
└──────────┬──────────┘
           │
           ▼
┌─────────────────────┐
│     Stego Image     │
│    Hidden Data      │
└─────────────────────┘
2. Decoding
The hidden information is extracted from the Least Significant Bits (LSBs) of the stego image and reconstructed as the original secret data.
┌─────────────────────┐
│     Stego Image     │
│    Encoded BMP      │
└──────────┬──────────┘
           │
           ▼
┌─────────────────────┐
│      Decoding       │
│    LSB Technique    │
└──────────┬──────────┘
           │
           ▼
┌─────────────────────┐
│     Secret Data     │
│   Extracted Text    │
└─────────────────────┘
Overall Workflow
                 IMAGE STEGANOGRAPHY
                         │
              ┌──────────┴──────────┐
              │                     │
           ENCODING              DECODING
              │                     │
              ▼                     ▼
       Source BMP Image       Stego BMP Image
              │                     │
              +                     │
         Secret Data                │
              │                     │
              ▼                     ▼
       LSB Embedding          LSB Extraction
              │                     │
              ▼                     ▼
         Stego Image          Secret Data

Compilation:
Compile the project using GCC:
gcc encode.c decode.c test_encode.c -o stego

Execution:
Encoding
./stego -e <source_image.bmp> <secret_file> <output_image.bmp>
Ex: ./stego -e beautiful.bmp secret.txt stego.bmp
Decoding:
./stego -d <stego_image.bmp>
Ex: ./stego -d stego.bmp

**Key Learning Outcomes**

Through this project, I gained practical experience in:
C programming and modular code development
File handling and binary file operations
Pointers and structures
Bitwise operations and data manipulation
BMP image file processing
Encoding and decoding techniques
Command-line argument handling
Debugging and problem solving

##Project Outcome##
Successfully developed a C-based Image Steganography application capable of hiding secret information inside BMP images using the LSB technique and extracting the hidden information through the decoding process.

Author
Sahana Patil
B.E. Electrical & Electronics Engineering | Embedded Systems Enthusiast
