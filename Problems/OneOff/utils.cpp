
#include "utils.h"

template <typename T>
void Swap(T &n1, T &n2)
{
	T temp;
	temp = n1;
	n1 = n2;
	n2 = temp;
}

const unsigned char BinUtils::sCharToHex[256] =
{
    /* 00 */ 255,255,255,255,255,255,255,255, 255,255,255,255,255,255,255,255,
    /* 10 */ 255,255,255,255,255,255,255,255, 255,255,255,255,255,255,255,255,
    /* 20 */ 255,255,255,255,255,255,255,255, 255,255,255,255,255,255,255,255,
    /* 30 */  0, 1, 2, 3, 4, 5, 6, 7,  8, 9,255,255,255,255,255,255, //0-9
    /* 40 */ 255,10,11,12,13,14,15,255, 255,255,255,255,255,255,255,255, //A-F
    /* 50 */ 255,255,255,255,255,255,255,255, 255,255,255,255,255,255,255,255,
    /* 60 */ 255,10,11,12,13,14,15,255, 255,255,255,255,255,255,255,255, //a-f
    /* 70 */ 255,255,255,255,255,255,255,255, 255,255,255,255,255,255,255,255,
    /* 80 */ 255,255,255,255,255,255,255,255, 255,255,255,255,255,255,255,255,
    /* 90 */ 255,255,255,255,255,255,255,255, 255,255,255,255,255,255,255,255,
    /* A0 */ 255,255,255,255,255,255,255,255, 255,255,255,255,255,255,255,255,
    /* B0 */ 255,255,255,255,255,255,255,255, 255,255,255,255,255,255,255,255,
    /* C0 */ 255,255,255,255,255,255,255,255, 255,255,255,255,255,255,255,255,
    /* D0 */ 255,255,255,255,255,255,255,255, 255,255,255,255,255,255,255,255,
    /* E0 */ 255,255,255,255,255,255,255,255, 255,255,255,255,255,255,255,255,
    /* F0 */ 255,255,255,255,255,255,255,255, 255,255,255,255,255,255,255,255
};

const char BinUtils::sHexToChar[] =
"000102030405060708090A0B0C0D0E0F"
"101112131415161718191A1B1C1D1E1F"
"202122232425262728292A2B2C2D2E2F"
"303132333435363738393A3B3C3D3E3F"
"404142434445464748494A4B4C4D4E4F"
"505152535455565758595A5B5C5D5E5F"
"606162636465666768696A6B6C6D6E6F"
"707172737475767778797A7B7C7D7E7F"
"808182838485868788898A8B8C8D8E8F"
"909192939495969798999A9B9C9D9E9F"
"A0A1A2A3A4A5A6A7A8A9AAABACADAEAF"
"B0B1B2B3B4B5B6B7B8B9BABBBCBDBEBF"
"C0C1C2C3C4C5C6C7C8C9CACBCCCDCECF"
"D0D1D2D3D4D5D6D7D8D9DADBDCDDDEDF"
"E0E1E2E3E4E5E6E7E8E9EAEBECEDEEEF"
"F0F1F2F3F4F5F6F7F8F9FAFBFCFDFEFF";


void
BinUtils::toHEX(const unsigned char * inBytes, size_t len, std::ostream& outChars)
{
	while(len-- > 0)
	{
		outChars.write(sHexToChar + (((int)(*inBytes++)) * 2), 2);
	}
}

size_t
BinUtils::toHEX(const unsigned char * inBytes, size_t len, char *outChars)
{
	while(len-- > 0)
	{
		const char * ptr = sHexToChar + (((int)(*inBytes++)) * 2);
		*outChars++ = *ptr++;
		*outChars++ = *ptr;
	}
	return 2 * len; 
}

void
BinUtils::fromHEX(const char * inChars, size_t len, std::ostream & outBytes)
{
	for(;len > 0; len -= 2)
	{
		unsigned char val = sCharToHex[static_cast< uint8_t >(*inChars++)] << 4;
		val += sCharToHex[static_cast< uint8_t >(*inChars++)];
		outBytes.write((const char*)&val, 1);
	}
}

size_t
BinUtils::fromHEX(const char * inChars, size_t len, unsigned char *outBytes)
{
	unsigned char* pout = outBytes;
	for(;len > 0; len -= 2)
    {
		unsigned char val = sCharToHex[static_cast< uint8_t >(*inChars++)] << 4;
		val += sCharToHex[static_cast< uint8_t >(*inChars++)];
        *pout++ = val;
    }
	return pout - outBytes;
}

/*
* base64.cpp and base64.h
*
* Copyright (C) 2004-2008 Ren� Nyffenegger
*
* This source code is provided 'as-is', without any express or implied
* warranty. In no event will the author be held liable for any damages
* arising from the use of this software.
*
* Permission is granted to anyone to use this software for any purpose,
* including commercial applications, and to alter it and redistribute it
* freely, subject to the following restrictions:
*
* 1. The origin of this source code must not be misrepresented; you must not
* claim that you wrote the original source code. If you use this source code
* in a product, an acknowledgment in the product documentation would be
* appreciated but is not required.
*
* 2. Altered source versions must be plainly marked as such, and must not be
* misrepresented as being the original source code.
*
* 3. This notice may not be removed or altered from any source distribution.
*
* Ren� Nyffenegger rene.nyffenegger@adp-gmbh.ch
*
* !!!!!!!!
* This source code has been altered to match the API and types
**/

static const std::string base64_chars =
"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
"abcdefghijklmnopqrstuvwxyz"
"0123456789+/";

static inline bool is_base64(unsigned char c) {
	return (isalnum(c) || (c == '+') || (c == '/'));
}


size_t BinUtils::toBase64(const unsigned char* inBytes, size_t len, char* outChars)
{
	int i = 0;
	int j = 0;
	unsigned char char_array_3[3];
	unsigned char char_array_4[4];
	char* pout = outChars;

	while (len--) {
		char_array_3[i++] = *(inBytes++);
		if (i == 3) {
			char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
			char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
			char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
			char_array_4[3] = char_array_3[2] & 0x3f;

			for (i = 0; (i <4); i++)
			{
				//if (len == nMaxLen) return(0); // about to overflow
				*pout++ = base64_chars[char_array_4[i]];
			}
			i = 0;
		}
	}

	if (i)
	{
		for (j = i; j < 3; j++)
			char_array_3[j] = '\0';

		char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
		char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
		char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
		char_array_4[3] = char_array_3[2] & 0x3f;

		for (j = 0; (j < i + 1); j++)
		{
			//if (len == nMaxLen) return(0); // about to overflow
			*pout++ = base64_chars[char_array_4[j]];
		}

		while ((i++ < 3))
		{
			//if (len == nMaxLen) return(0); // about to overflow
			*pout++ = '=';
		}
	}
	return pout - outChars;
}

size_t BinUtils::fromBase64(const char* inChars, size_t len, unsigned char* outBytes)
{
	int i = 0;
	int j = 0;
	int in_ = 0;
	unsigned char char_array_4[4], char_array_3[3];
	unsigned char* pout = outBytes;

	while (len-- && (inChars[in_] != '=') && is_base64(inChars[in_])) {
		char_array_4[i++] = inChars[in_]; in_++;
		if (i == 4) {
			for (i = 0; i <4; i++)
				char_array_4[i] = (uint8_t)base64_chars.find(char_array_4[i]);

			char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
			char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
			char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];

			for (i = 0; (i < 3); i++)
			{
				//if (len == nMaxLen) return(0); // about to overflow
				*pout++ = char_array_3[i];
			}
			i = 0;
		}
	}

	if (i) {
		for (j = i; j <4; j++)
			char_array_4[j] = 0;

		for (j = 0; j <4; j++)
			char_array_4[j] = (unsigned char)base64_chars.find(char_array_4[j]);

		char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
		char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
		char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];

		for (j = 0; (j < i - 1); j++)
		{
			//if (len == nMaxLen) return(0); // about to overflow
			*pout++ = char_array_3[j];
		}
	}

	return pout - outBytes;
}



/**
 * Function that returns size of the file in no.of bytes
 */

int getFileSizeInBytes(std::string filename)
{
  std::streampos begin,end;
  std::ifstream myfile (filename, std::ios::binary);
  begin = myfile.tellg();
  myfile.seekg (0, std::ios::end);
  end = myfile.tellg();
  myfile.close();
//   std::cout << "size is: " << end-begin << " bytes.\n";
  return end-begin;
}