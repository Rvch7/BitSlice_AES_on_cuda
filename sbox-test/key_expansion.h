#pragma once

typedef unsigned char BYTE;

const char Nk = 4;	// Number of keys
const char Nb = 4;	// Number of words in a block
const char Nr = 10; // Number of rounds

struct word {
    BYTE byte[4];
    word operator^(word x) {
        word z;
        z.byte[0] = x.byte[0] ^ this->byte[0];
        z.byte[1] = x.byte[1] ^ this->byte[1];
        z.byte[2] = x.byte[2] ^ this->byte[2];
        z.byte[3] = x.byte[3] ^ this->byte[3];
        return z;
    }
};

struct key_t {
    word state[4] = {};
    key_t operator^(key_t x) {
        key_t z;
        z.state[0] = x.state[0] ^ this->state[0];
        z.state[1] = x.state[1] ^ this->state[1];
        z.state[2] = x.state[2] ^ this->state[2];
        z.state[3] = x.state[3] ^ this->state[3];
        return z;
    }
};



void key_expansionCore(word* in, unsigned i);
void key_expansion(key_t* key, key_t* expandedkeys);