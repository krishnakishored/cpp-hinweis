#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <numeric>
#include <sstream>
#include <ctime>
#include <cmath>

#include <iomanip> // std::setprecision
#include <fstream>

using std::cout;

using std::string; 
using std::ifstream;
using std::ofstream;
using std::streampos; 

#include "utils.h"



int main_convertBinToHex()
{
    
 
    ifstream in("input.xmf");
    ofstream out("output.txt");

    int fileSize = getFileSizeInBytes("latlon.bin");
    char inputBytes[fileSize];

    in.read(inputBytes,fileSize);
    BinUtils::toHEX((unsigned char*)inputBytes, fileSize, out);

    

    // size_t base64Size = BinUtils::toBase64Size(fileSize);
    // char outputBase64Bytes[base64Size];
    // BinUtils::toBase64((unsigned char*)inputBytes,fileSize,outputBase64Bytes);

    // out.write(outputBase64Bytes,base64Size);


    return 0;
}

// int main(){

//     return 0;
// }

int main(int argc, char const *argv[])
{
    main_convertBinToHex();
    return 0;
}
