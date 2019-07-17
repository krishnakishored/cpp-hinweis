#include <iostream>
#include <fstream>
#include <string>

class BinUtils
{
public:
    /**
			* Converts binary bytes to a hexadecimal character equivalent.  For
			* example, if inBytes was ASCII chars "xy", then invoking this methods
			* would put the ASCII chars "7879" into the outChars . <p>
			* If the non-stream variant is used, you must have twice as many byte in
			* outChars than are in inBytes.
			*
			* This method does NOT null terminate the chars.
			*/
    static void toHEX(const unsigned char *inBytes, size_t len, std::ostream &outChars);
    static size_t toHEX(const unsigned char *inBytes, size_t len, char *outChars);

    /**
			* Interprets the inChars as a ASCII hex representation of
			* binary data.  Returns the binary equivalent in the outBytes.
			* For example, if inChars was "7879", then the outBytes would contain 2
			* bytes with ASCII chars "xy".<p>
			*
			* The len must be a multiple of 2.  Behavior is undetermined otherwise.
			*/
    static void fromHEX(const char *inChars, size_t len, std::ostream &outBytes);
    static size_t fromHEX(const char *inChars, size_t len, unsigned char *outBytes);

    /**
			* @brief Converts binary data to Base64 representation.
			* Note that you cannnot covert to Base64 inplace without overwriting the data,
			* Base64 requires more bytes than Byte representation.
			*
			* This method does NOT null terminate the chars.
			*/
    static size_t toBase64(const unsigned char *inBytes, size_t len, char *outChars);

    /**
			 * toBase64Size() accurately calculates the size required to encode toBase64().
			 */
    static size_t toBase64Size(size_t bytes) { return (((bytes + 2) / 3) * 4); } // include pad

    /**
			* Converts binary data from Base64 representation.  Provides the
			* size calculation helper functions.   Note that you can convert from Base64 in place.
			*
			* Note the size methods will always return a size greater than equal to the actual output from the
			* conversion routines.  Use the actual size returned from the conversion routines when setting buffer and string
			* lengths.
			*
			* This method does NOT null terminate the chars.
			*/
    static size_t fromBase64(const char *inChars, size_t len, unsigned char *outBytes);

    /**
			 * fromBase64Size() does not accurately determine number of bytes.
			 * It may be 1,2 or 3 bytes larger than the actual size.
			 * For an accurate size use the return result of fromBase64()
			 */
    static size_t fromBase64Size(size_t bytes) { return ((bytes / 4) * 3); } // may have pad

    /**
			* sCharToHex returns an unsigned char value of the nibble
			* of the char used to index int the array.
			* The digits it supports are (0-9,A-F,a-F)
			* Other char digits, return 255
			* For instance 'A' will return 10
			* Likewise 'a' will return 10
			* Non-hex digits (0-9,A-F,a-F)
			*/
    static const unsigned char sCharToHex[256];

    /**
			* sHexToChar is a long "string" of length 512,
			* that contains every character sequence from "00" to "FF".
			* You use it by taking an unsigned char value, multiplying it by 2,
			* and using the result as an index into the array.
			* The string is not NUL terminated, so you will have to only
			* grab two byte from it.
			*/
    static const char sHexToChar[];

private:
    // these are unimplemented
    BinUtils();
    BinUtils(const BinUtils &);
    ~BinUtils();
    BinUtils &operator=(const BinUtils &);
};

//Util functions
int getFileSizeInBytes(std::string filename);