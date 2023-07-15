#ifndef AES_H_
#define AES_H_

#include <stdint.h>


/* Fully-fixsliced encryption functions */
void aes128_encrypt_ffs(unsigned char* ctext0, unsigned char* ctext1,
	const unsigned char* ptext0, const unsigned char* ptext1,
	const uint32_t* rkeys_ffs);
void aes256_encrypt_ffs(unsigned char* ctext0, unsigned char* ctext1,
	const unsigned char* ptext0, const unsigned char* ptext1,
	const uint32_t* rkeys_ffs);

/* Semi-fixsliced encryption functions */
void aes128_encrypt_sfs(unsigned char* ctext0, unsigned char* ctext1,
	const unsigned char* ptext0, const unsigned char* ptext1,
	const uint32_t* rkeys_sfs);
void aes256_encrypt_sfs(unsigned char* ctext0, unsigned char* ctext1,
	const unsigned char* ptext0, const unsigned char* ptext1,
	const uint32_t* rkeys_sfs);

/* Fully-fixsliced key schedule functions */
void aes128_keyschedule_ffs(uint32_t* rkeys, const unsigned char* key0,
	const unsigned char* key1);
void aes256_keyschedule_ffs(uint32_t* rkeys, const unsigned char* key0,
	const unsigned char* key1);

/* Semi-fixsliced key schedule functions */
void aes128_keyschedule_sfs(uint32_t* rkeys, const unsigned char* key0,
	const unsigned char* key1);
void aes256_keyschedule_sfs(uint32_t* rkeys, const unsigned char* key0,
	const unsigned char* key1);

/* Fully-fixsliced key schedule functions (LUT-based) */
void aes128_keyschedule_ffs_lut(uint32_t* rkeys_ffs, const unsigned char* key);
void aes256_keyschedule_ffs_lut(uint32_t* rkeys_ffs, const unsigned char* key);

/* Semi-fixsliced key schedule functions (LUT-based) */
void aes128_keyschedule_sfs_lut(uint32_t* rkeys_sfs, const unsigned char* key);
void aes256_keyschedule_sfs_lut(uint32_t* rkeys_sfs, const unsigned char* key);

#endif 	// AES_H_
