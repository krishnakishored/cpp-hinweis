
// C++ programs have a concept known as a string table and all string literals in your program are included in the program’s executable.
#ifndef IOSTREAM
#define IOSTREAM
#include <iostream>
#endif

#ifndef CINTTYPES
#define CINTTYPES
#include <cinttypes>
#endif

using std::cout;
using std::endl;
using std::string;

int main_int_cintTypes()
{
    int wholeNumber1{64};
    cout << "wholeNumber1 equals " << wholeNumber1 << endl;
    int wholeNumber2{wholeNumber1 + 32};
    cout << "wholeNumber2 equals " << wholeNumber2 << endl;
    int wholeNumber3{wholeNumber2 - wholeNumber1};
    cout << "wholeNumber3 equals " << wholeNumber3 << endl;
    int wholeNumber4{wholeNumber2 * wholeNumber1};
    cout << "wholeNumber4 equals " << wholeNumber4 << endl;
    int wholeNumber5{wholeNumber4 / wholeNumber1};
    cout << "wholeNumber5 equals " << wholeNumber5 << endl;
    int wholeNumber6{wholeNumber4 % wholeNumber1};
    cout << "wholeNumber6 equals " << wholeNumber6 << endl;

    int32_t whole32BitNumber1{64};
    cout << "whole32BitNumber1 equals " << whole32BitNumber1 << endl;
    int32_t whole32BitNumber2{whole32BitNumber1 + 32};
    cout << "whole32BitNumber2 equals " << whole32BitNumber2 << endl;
    int32_t whole32BitNumber3{whole32BitNumber2 - whole32BitNumber1};
    cout << "whole32BitNumber3 equals " << whole32BitNumber3 << endl;
    int32_t whole32BitNumber4{whole32BitNumber2 * whole32BitNumber1};
    cout << "whole32BitNumber4 equals " << whole32BitNumber4 << endl;
    int32_t whole32BitNumber5{whole32BitNumber4 / whole32BitNumber1};
    cout << "whole32BitNumber5 equals " << whole32BitNumber5 << endl;
    int whole32BitNumber6{whole32BitNumber2 % whole32BitNumber1};
    cout << "whole32BitNumber6 equals " << whole32BitNumber6 << endl;

    return 0;
}

int main_RelationalOperators()
{
    int32_t equal1{10};
    int32_t equal2{10};
    bool isEqual = equal1 == equal2;
    cout << "Are the numbers equal? " << isEqual << endl; //1
    int32_t notEqual1{10};
    int32_t notEqual2{100};

    bool isNotEqual = notEqual1 != notEqual2;
    cout << "Are the numbers equal? " << isNotEqual << endl; //1

    int32_t notGreaterThan1{10};
    int32_t notGreaterThan2{100};
    bool isNotGreaterThan = notGreaterThan1 > notGreaterThan2;
    cout << "Is the left greater than the right? " << isNotGreaterThan << endl;
    return 0;
}
//Chaining Decisions with Logical Operators

int main_logicalOperators()
{
    bool isTrue{(10 == 10) && (12 == 12)};
    cout << "True? " << isTrue << endl;
    bool isFalse = isTrue && (1 == 2);
    cout << "True? " << isFalse << endl;

    bool isTrue2{(1 == 1) || (0 == 1)};
    cout << "True? " << isTrue2 << endl;
    isTrue2 = (0 == 1) || (1 == 1);
    cout << "True? " << isTrue2 << endl;
    isTrue2 = (1 == 1) || (1 == 1);
    cout << "True? " << isTrue2 << endl;
    isTrue2 = (0 == 1) || (1 == 0);
    cout << "True? " << isTrue2 << endl;
    return 0;
}

int main_hexvalues()
{
    uint32_t hexValue{0x89};
    cout << "Decimal: " << hexValue << endl;
    cout << std::hex << "Hexadecimal: " << hexValue << endl;
    cout << std::showbase << std::hex << "Hexadecimal (with base): " << hexValue << endl;
    return 0;
}

//Bit Twiddling with Binary Operators
int main_binaryOperators()
{
    uint32_t bits{0x00011000};
    cout << std::showbase << std::hex;
    cout << "Result of 0x00011000 & 0x00011000: " << (bits & bits) << endl;
    cout << "Result of 0x00011000 & 0x11100111: " << (bits & ~bits) << endl;

    uint32_t leftBits{ 0x00011000 };
    uint32_t rightBits{ 0x00010100 };
    
    cout << "Result of 0x00011000 | 0x00010100: " << (leftBits | rightBits) << endl;
    cout << "Result of 0x00011000 & 0x11100111: " << (leftBits | ~leftBits) << endl;

    cout << "Result of 0x00011000 ^ 0x00010100: " << (leftBits ^ rightBits) << endl;
    cout << "Result of 0x00011000 ^ 0x11100111: " << (leftBits ^ ~leftBits) << endl;


    const uint32_t maskBits{ 16 };
    uint32_t leftShifted{ 0x00001010 << maskBits };
    
    cout<<"0x00001010 left shifted by "<<maskBits<<endl;
    cout << "Left shifted: " << leftShifted << endl;
    //Using a mask to pack values into a variable
    uint32_t lowerMask{ 0x0000FFFF };
    leftShifted |= (0x11110110 & lowerMask);
    cout << "Packed left shifted: " << leftShifted << endl;

    //unmasking
    uint32_t lowerValue{ (leftShifted & lowerMask) };
    cout << "Lower value unmasked: " << lowerValue << endl;
    uint32_t upperValue{ (leftShifted >> maskBits) };
    cout << "Upper value unmasked: " << upperValue << endl;

    // Shifting and narrowing conversions
    // uint32_t narrowingBits{ 0x00008000 << maskBits }; //constant expression evaluates to -2147483648 which cannot be narrowed to type 'uint32_t' (aka 'unsigned int') [-Wc++11-narrowing]
    // cout<<narrowingBits<<endl;

    // Right shifting negative values
    int32_t leftShifted2{ 0x00008080 << maskBits };
    cout << "Left shifted: " << leftShifted2 << endl;

    leftShifted2 |= (0x11110110 & lowerMask);
    cout << "Packed left shifted: " << leftShifted2 << endl;
    int32_t rightShifted{ (leftShifted2 >> maskBits) };
    cout << "Right shifted: " << rightShifted << endl;
    cout << "Unmasked right shifted: " << (rightShifted & lowerMask) << endl;

    return 0;

}
int main()
{
    main_binaryOperators();
    main_hexvalues();
    main_int_cintTypes();
    main_logicalOperators();
    main_RelationalOperators();

        /* code */
    return 0;
}
