#pragma once

void MD5(char *dst, const char *src);
void MD5(char *dst, const char *src, const unsigned int length);
int  MD5_file(char *dst, const char *filename);

void SHA1(char *dst, const char *src);
void SHA1(char *dst, const char *src, const unsigned int length);
int  SHA1_file(char *dst, const char *filename);

void SHA224(char *dst, const char *src);
void SHA224(char *dst, const char *src, const unsigned int length);
int  SHA224_file(char *dst, const char *filename);

void SHA256(char *dst, const char *src);
void SHA256(char *dst, const char *src, const unsigned int length);
int  SHA256_file(char *dst, const char *filename);

void SHA384(char *dst, const char *src);
void SHA384(char *dst, const char *src, const unsigned int length);
int  SHA384_file(char *dst, const char *filename);

void SHA512(char *dst, const char *src);
void SHA512(char *dst, const char *src, const unsigned int length);
int  SHA512_file(char *dst, const char *filename);
