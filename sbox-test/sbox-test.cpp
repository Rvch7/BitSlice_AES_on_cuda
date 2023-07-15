// sbox-test.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "aes.h"
#include "internal-aes.h"


typedef struct block {
    uint64_t high;
    uint64_t low;
}block_t;

//uint64_t out[7];

block_t out[8];


uint8_t aes_input0[128] = {
    0x32, 0x88, 0x31, 0xE0,
    0x43, 0x5A, 0x31, 0x37,
    0xF6, 0x30, 0x98, 0x07,
    0xA8, 0x8D, 0xA2, 0x34,
    0x32, 0x88, 0x31, 0xE0,
    0x43, 0x5A, 0x31, 0x37,
    0xF6, 0x30, 0x98, 0x07,
    0xA8, 0x8D, 0xA2, 0x34,
    0x32, 0x88, 0x31, 0xE0,
    0x43, 0x5A, 0x31, 0x37,
    0xF6, 0x30, 0x98, 0x07,
    0xA8, 0x8D, 0xA2, 0x34,
    0x32, 0x88, 0x31, 0xE0,
    0x43, 0x5A, 0x31, 0x37,
    0xF6, 0x30, 0x98, 0x07,
    0xA8, 0x8D, 0xA2, 0x34,
    0x32, 0x88, 0x31, 0xE0,
    0x43, 0x5A, 0x31, 0x37,
    0xF6, 0x30, 0x98, 0x07,
    0xA8, 0x8D, 0xA2, 0x34,
    0x32, 0x88, 0x31, 0xE0,
    0x43, 0x5A, 0x31, 0x37,
    0xF6, 0x30, 0x98, 0x07,
    0xA8, 0x8D, 0xA2, 0x34,
    0x32, 0x88, 0x31, 0xE0,
    0x43, 0x5A, 0x31, 0x37,
    0xF6, 0x30, 0x98, 0x07,
    0xA8, 0x8D, 0xA2, 0x34,
    0x32, 0x88, 0x31, 0xE0,
    0x43, 0x5A, 0x31, 0x37,
    0xF6, 0x30, 0x98, 0x07,
    0xA8, 0x8D, 0xA2, 0x34,
};
uint8_t aes_input1[16] = {
    0x32, 0x88, 0x31, 0xE0,
    0x43, 0x5A, 0x31, 0x37,
    0xF6, 0x30, 0x98, 0x07,
    0xA8, 0x8D, 0xA2, 0x34
};
uint8_t aes_input2[16] = {
    0x32, 0x88, 0x31, 0xE0,
    0x43, 0x5A, 0x31, 0x37,
    0xF6, 0x30, 0x98, 0x07,
    0xA8, 0x8D, 0xA2, 0x34
};
//uint8_t aes_input3[16] = {
//    0x32, 0x88, 0x31, 0xE0,
//    0x43, 0x5A, 0x31, 0x37,
//    0xF6, 0x30, 0x98, 0x07,
//    0xA8, 0x8D, 0xA2, 0x34
//};
//uint8_t aes_input4[16] = {
//    0x32, 0x88, 0x31, 0xE0,
//    0x43, 0x5A, 0x31, 0x37,
//    0xF6, 0x30, 0x98, 0x07,
//    0xA8, 0x8D, 0xA2, 0x34
//};
//uint8_t aes_input5[16] = {
//    0x32, 0x88, 0x31, 0xE0,
//    0x43, 0x5A, 0x31, 0x37,
//    0xF6, 0x30, 0x98, 0x07,
//    0xA8, 0x8D, 0xA2, 0x34
//};
//uint8_t aes_input6[16] = {
//    0x32, 0x88, 0x31, 0xE0,
//    0x43, 0x5A, 0x31, 0x37,
//    0xF6, 0x30, 0x98, 0x07,
//    0xA8, 0x8D, 0xA2, 0x34
//};
//uint8_t aes_input7[16] = {
//    0x32, 0x88, 0x31, 0xE0,
//    0x43, 0x5A, 0x31, 0x37,
//    0xF6, 0x30, 0x98, 0x07,
//    0xA8, 0x8D, 0xA2, 0x34
//};

uint8_t aes_key[16] = {
    0x2B, 0x7E, 0x15, 0x16,
    0x28, 0xAE, 0xD2, 0xA6,
    0xAB, 0xF7, 0x15, 0x88,
    0x09, 0xCF, 0x4F, 0x3C
};

uint8_t aes_key0[16] = { 0 };

#define HI32(X) ((X & 0xFFFF0000) >> 32)
#define LO32(X) (X & 0x0000FFFF)



__inline void load_64(const uint8_t* in, block_t* out) {
    for (int i = 0; i < 8; i++) {
        out->high  |= ((uint64_t)in[i]) << (i * 8);
        out->low |= ((uint64_t)in[i + 8]) << (i * 8);
    }
}

//template <typename T>
//__inline void swapmove_(T& a, T& b, T n, T mask) {
//    T tmp = ((T)b ^ (T)(a >> n)) & (T)mask;
//    b ^= tmp;
//    a ^= (tmp << n);
//}

template <typename T>
__inline void swapmove_(T& a, T& b, int n, T mask) {
    T tmp = b >> n;
    tmp ^= a;
    tmp &= mask;
    a ^= tmp;
    b ^= (tmp << n);
}

void bit_tranformation(block_t* block) {
    swapmove_(block[0].high, block[1].high, 1, (uint64_t)0x5555555555555555); 
    swapmove_(block[0].low, block[1].low, 1, (uint64_t)0x5555555555555555);
    swapmove_(block[2].high, block[3].high, 1, (uint64_t)0x5555555555555555);
    swapmove_(block[2].low, block[3].low, 1, (uint64_t)0x5555555555555555);
    swapmove_(block[4].high, block[5].high, 1, (uint64_t)0x5555555555555555);
    swapmove_(block[4].low, block[5].low, 1, (uint64_t)0x5555555555555555);
    swapmove_(block[6].high, block[7].high, 1, (uint64_t)0x5555555555555555);
    swapmove_(block[6].low, block[7].low, 1, (uint64_t)0x5555555555555555);
    swapmove_(block[0].high, block[2].high, 2, (uint64_t)0x3333333333333333);
    swapmove_(block[0].low, block[2].low, 2, (uint64_t)0x3333333333333333);
    swapmove_(block[1].high, block[3].high, 2, (uint64_t)0x3333333333333333);
    swapmove_(block[1].low, block[3].low, 2, (uint64_t)0x3333333333333333);
    swapmove_(block[4].high, block[6].high, 2, (uint64_t)0x3333333333333333);
    swapmove_(block[4].low, block[6].low, 2, (uint64_t)0x3333333333333333);
    swapmove_(block[5].high, block[7].high, 2, (uint64_t)0x3333333333333333);
    swapmove_(block[5].low, block[7].low, 2, (uint64_t)0x3333333333333333);
    swapmove_(block[0].high, block[4].high, 4, (uint64_t)0x0f0f0f0f0f0f0f0f);
    swapmove_(block[0].low, block[4].low, 4, (uint64_t)0x0f0f0f0f0f0f0f0f);
    swapmove_(block[1].high, block[5].high, 4, (uint64_t)0x0f0f0f0f0f0f0f0f);
    swapmove_(block[1].low, block[5].low, 4, (uint64_t)0x0f0f0f0f0f0f0f0f);
    swapmove_(block[2].high, block[6].high, 4, (uint64_t)0x0f0f0f0f0f0f0f0f);
    swapmove_(block[2].low, block[6].low, 4, (uint64_t)0x0f0f0f0f0f0f0f0f);
    swapmove_(block[3].high, block[7].high, 4, (uint64_t)0x0f0f0f0f0f0f0f0f);
    swapmove_(block[3].low, block[7].low, 4, (uint64_t)0x0f0f0f0f0f0f0f0f);
}


//void packing_(uint8_t* aes_input, uint64_t* out) {
//    load_64(aes_input0, out);
//
//
//}

uint32_t rkeys;

typedef unsigned short word;

#define XOR(c,a,b) (c = (a)^(b))
#define AND(c,a,b) (c = (a)&(b))

void sbox_bitsliced(block_t in[8]) {
    uint64_t U0, U1, U2, U3, U4, U5, U6, U7;
    uint64_t T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27;
    uint64_t M1, M2, M3, M4, M5, M6, M7, M8, M9, M10, M11, M12, M13, M14, M15, M16, M17, M18, M19, M20, M21, M22, M23, M24, M25, M26, M27, M28, M29, M30, M31, M32, M33, M34, M35, M36, M37, M38, M39, M40, M41, M42, M43, M44, M45, M46, M47, M48, M49, M50, M51, M52, M53, M54, M55, M56, M57, M58, M59, M60, M61, M62, M63;
    uint64_t L0, L1, L2, L3, L4, L5, L6, L7, L8, L9, L10, L11, L12, L13, L14, L15, L16, L17, L18, L19, L20, L21, L22, L23, L24, L25, L26, L27, L28, L29;
    uint64_t S0, S1, S2, S3, S4, S5, S6, S7;

    U0 = in[0].high;
    U1 = in[1].high;
    U2 = in[2].high;
    U3 = in[3].high;
    U4 = in[4].high;
    U5 = in[5].high;
    U6 = in[6].high;
    U7 = in[7].high;

    XOR(T1, U0, U3);
    XOR(T2, U0, U5);
    XOR(T3, U0, U6);
    XOR(T4, U3, U5);
    XOR(T5, U4, U6);
    XOR(T6, T1, T5);
    XOR(T7, U1, U2);
    XOR(T8, U7, T6);
    XOR(T9, U7, T7);
    XOR(T10, T6, T7);
    XOR(T11, U1, U5);
    XOR(T12, U2, U5);
    XOR(T13, T3, T4);
    XOR(T14, T6, T11);
    XOR(T15, T5, T11);
    XOR(T16, T5, T12);
    XOR(T17, T9, T16);
    XOR(T18, U3, U7);
    XOR(T19, T7, T18);
    XOR(T20, T1, T19);
    XOR(T21, U6, U7);
    XOR(T22, T7, T21);
    XOR(T23, T2, T22);
    XOR(T24, T2, T10);
    XOR(T25, T20, T17);
    XOR(T26, T3, T16);
    XOR(T27, T1, T12);

    AND(M1, T13, T6);
    AND(M2, T23, T8);
    XOR(M3, T14, M1);
    AND(M4, T19, U7);
    XOR(M5, M4, M1);
    AND(M6, T3, T16);
    AND(M7, T22, T9);
    XOR(M8, T26, M6);
    AND(M9, T20, T17);
    XOR(M10, M9, M6);
    AND(M11, T1, T15);
    AND(M12, T4, T27);
    XOR(M13, M12, M11);
    AND(M14, T2, T10);
    XOR(M15, M14, M11);
    XOR(M16, M3, M2);
    XOR(M17, M5, T24);
    XOR(M18, M8, M7);
    XOR(M19, M10, M15);
    XOR(M20, M16, M13);
    XOR(M21, M17, M15);
    XOR(M22, M18, M13);
    XOR(M23, M19, T25);
    XOR(M24, M22, M23);
    AND(M25, M22, M20);
    XOR(M26, M21, M25);
    XOR(M27, M20, M21);
    XOR(M28, M23, M25);
    AND(M29, M28, M27);
    AND(M30, M26, M24);
    AND(M31, M20, M23);
    AND(M32, M27, M31);
    XOR(M33, M27, M25);
    AND(M34, M21, M22);
    AND(M35, M24, M34);
    XOR(M36, M24, M25);
    XOR(M37, M21, M29);
    XOR(M38, M32, M33);
    XOR(M39, M23, M30);
    XOR(M40, M35, M36);
    XOR(M41, M38, M40);
    XOR(M42, M37, M39);
    XOR(M43, M37, M38);
    XOR(M44, M39, M40);
    XOR(M45, M42, M41);
    AND(M46, M44, T6);
    AND(M47, M40, T8);
    AND(M48, M39, U7);
    AND(M49, M43, T16);
    AND(M50, M38, T9);
    AND(M51, M37, T17);
    AND(M52, M42, T15);
    AND(M53, M45, T27);
    AND(M54, M41, T10);
    AND(M55, M44, T13);
    AND(M56, M40, T23);
    AND(M57, M39, T19);
    AND(M58, M43, T3);
    AND(M59, M38, T22);
    AND(M60, M37, T20);
    AND(M61, M42, T1);
    AND(M62, M45, T4);
    AND(M63, M41, T2);

    XOR(L0, M61, M62);
    XOR(L1, M50, M56);
    XOR(L2, M46, M48);
    XOR(L3, M47, M55);
    XOR(L4, M54, M58);
    XOR(L5, M49, M61);
    XOR(L6, M62, L5);
    XOR(L7, M46, L3);
    XOR(L8, M51, M59);
    XOR(L9, M52, M53);
    XOR(L10, M53, L4);
    XOR(L11, M60, L2);
    XOR(L12, M48, M51);
    XOR(L13, M50, L0);
    XOR(L14, M52, M61);
    XOR(L15, M55, L1);
    XOR(L16, M56, L0);
    XOR(L17, M57, L1);
    XOR(L18, M58, L8);
    XOR(L19, M63, L4);
    XOR(L20, L0, L1);
    XOR(L21, L1, L7);
    XOR(L22, L3, L12);
    XOR(L23, L18, L2);
    XOR(L24, L15, L9);
    XOR(L25, L6, L10);
    XOR(L26, L7, L9);
    XOR(L27, L8, L10);
    XOR(L28, L11, L14);
    XOR(L29, L11, L17);

    XOR(S0, L6, L24);
    XOR(S1, L16, L26);
    XOR(S2, L19, L28);
    XOR(S3, L6, L21);
    XOR(S4, L20, L22);
    XOR(S5, L25, L29);
    XOR(S6, L13, L27);
    XOR(S7, L6, L23);

    in[0].high = S0;
    in[1].high = ~S1;
    in[2].high = ~S2;
    in[3].high = S3;
    in[4].high = S4;
    in[5].high = S5;
    in[6].high = ~S6;
    in[7].high = ~S7;
}



int main()
{
    
    
    //swapmove_(out->high, aes_input1+1,0x11,2);
    //printf("%i",sizeof(unsigned short));
    //std::cout << "Hello World!\n";

    //packing(out, aes_input0, aes_input1);
    for (int i = 0; i < 8; i++) {
        load_64(aes_input0+(16*i), out+i);
    }

    bit_tranformation(out);
    sbox_bitsliced(out);





    //uint32_t ret = HI32(*out);
    //printf("%08x", ret);

    //unsigned short a = 0x3D3D;
    //unsigned short b = 0x4F4F;
    //unsigned short c = 0xA1A1;
    //unsigned short d = 0x7575;
    //
    //
    //unsigned short mask = 0x5555;
    //unsigned short n = 0x0001;
    //swapmove_(a, b, n, mask);
    //swapmove_(c, d, n, mask);

    //mask = 0x3333;
    //n = 0x0002;
    //swapmove_(a, c, n, mask);
    //swapmove_(b, d, n, mask);
    //
    //mask = 0x0F0F;
    //n = 0x0004;
    //swapmove_(a, b, n, mask);
    //swapmove_(c, d, n, mask);











    //swapmove_(out[0].high, out[1].high, 1, 0x5555555555555555);
    //swapmove_(out[0].low, out[1].low, 1, 0x5555555555555555);
    //swapmove_(out[2].high, out[3].high, 1, 0x5555555555555555);
    //swapmove_(out[2].low, out[3].low, 1, 0x5555555555555555);

    //swapmove_(out[0].high, out[2].high, 2, 0x3333333333333333);
    //swapmove_(out[1].high, out[3].high, 2, 0x3333333333333333);
    //swapmove_(out[0].low, out[2].low, 2, 0x3333333333333333);
    //swapmove_(out[1].low, out[3].low, 2, 0x3333333333333333);

    //swapmove_(out[0].low, out[0].high, 4, 0x0f0f0f0f0f0f0f0f);
    //swapmove_(out[1].low, out[1].high, 4, 0x0f0f0f0f0f0f0f0f);
    //swapmove_(out[2].low, out[2].high, 4, 0x0f0f0f0f0f0f0f0f);
    //swapmove_(out[3].low, out[3].high, 4, 0x0f0f0f0f0f0f0f0f);


    //swapmove_(out[3].high, out[3].low ,  8, 0x00ff00ff00ff00ff); 
    //swapmove_(out[3].low , out[3].high, 16, 0x0000ffff0000ffff);
    //swapmove_(out[3].high, out[3].low , 32, 0x00000000ffffffff); 
    //swapmove_(out[2].high, out[2].low ,  8, 0x00ff00ff00ff00ff);
    //swapmove_(out[2].low , out[2].high, 16, 0x0000ffff0000ffff); 
    //swapmove_(out[2].high, out[2].low , 32, 0x00000000ffffffff);
    //swapmove_(out[1].high, out[1].low ,  8, 0x00ff00ff00ff00ff); 
    //swapmove_(out[1].low , out[1].high, 16, 0x0000ffff0000ffff);
    //swapmove_(out[1].high, out[1].low , 32, 0x00000000ffffffff); 
    //swapmove_(out[0].high, out[0].low ,  8, 0x00ff00ff00ff00ff); 
    //swapmove_(out[0].low , out[0].high, 16, 0x0000ffff0000ffff); 
    //swapmove_(out[0].high, out[0].low , 32, 0x00000000ffffffff);
    //swapmove_(out[0].high, out[1].high, 1, 0x5555555555555555);
    //swapmove_(out[0].low, out[1].low, 1, 0x5555555555555555);
    //swapmove_(out[2].high, out[3].high, 1, 0x5555555555555555);
    //swapmove_(out[2].low, out[3].low, 1, 0x5555555555555555);
    //swapmove_(out[0].high, out[2].high, 2, 0x3333333333333333);
    //swapmove_(out[1].high, out[3].high, 2, 0x3333333333333333);
    //swapmove_(out[0].low, out[2].low, 2, 0x3333333333333333);
    //swapmove_(out[1].low, out[3].low, 2, 0x3333333333333333);
    //swapmove_(out[0].low , out[0].high,  4, 0x0f0f0f0f0f0f0f0f); 
    //swapmove_(out[1].low , out[1].high,  4, 0x0f0f0f0f0f0f0f0f);
    //swapmove_(out[2].low , out[2].high,  4, 0x0f0f0f0f0f0f0f0f); 
    //swapmove_(out[3].low , out[3].high,  4, 0x0f0f0f0f0f0f0f0f);


  /*1; R8 = low 64 bytes of block 3 R9 = low 64 bytes of block 2
    2; R10 = low 64 bytes of block 1 R11 = low 64 bytes of block 0
    3; R12 = high 64 bytes of block 3 R13 = high 64 bytes of block 2
    4; R14 = high 64 bytes of block 1 R15 = high 64 bytes of block 0
    5 swapmove R12, R8, 8, 00ff00ff00ff00ffh swapmove R8, R12, 16, 0000ffff0000ffffh
    6 swapmove R12, R8, 32, 00000000ffffffffh swapmove R13, R9, 8, 00ff00ff00ff00ffh
    7 swapmove R9, R13, 16, 0000ffff0000ffffh swapmove R13, R9, 32, 00000000ffffffffh
    8 swapmove R14, R10, 8, 00ff00ff00ff00ffh swapmove R10, R14, 16, 0000ffff0000ffffh
    9 swapmove R14, R10, 32, 00000000ffffffffh swapmove R15, R11, 8, 00ff00ff00ff00ffh
    10 swapmove R11, R15, 16, 0000ffff0000ffffh swapmove R15, R11, 32, 00000000ffffffffh
    11 swapmove R14, R15, 1, 5555555555555555h swapmove R12, R13, 1, 5555555555555555h
    12 swapmove R10, R11, 1, 5555555555555555h swapmove R8, R9, 1, 5555555555555555h
    13 swapmove R13, R15, 2, 3333333333333333h swapmove R12, R14, 2, 3333333333333333h
    14 swapmove R9, R11, 2, 3333333333333333h swapmove R8, R10, 2, 3333333333333333h
    15 swapmove R11, R15, 4, 0f0f0f0f0f0f0f0fh swapmove R10, R14, 4, 0f0f0f0f0f0f0f0fh
    16 swapmove R9, R13, 4, 0f0f0f0f0f0f0f0fh swapmove R8, R12, 4, 0f0f0f0f0f0f0f0fh*/
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
