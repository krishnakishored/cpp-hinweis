#ifndef IOSTREAM
#define IOSTREAM
#include <iostream>
#endif

#ifndef MEMORY
#define MEMORY
#include <memory>
#endif

#ifndef CSTDLIB
#define CSTDLIB
#include <cstdlib>
#endif


using std::cout;
using std::endl;

//Debugging Memory Problems by Overloading new and delete
/*

//void* operator new(size_t size);
//void delete(void* ptr);

These two function overloads cause segmentation faults
*/


struct MemoryHeader
{
    const char *m_Filename{nullptr};
    int m_Line{-1};
};
void *operator new(size_t size, const char *filename, int line) noexcept
{
    void *pMemory{malloc(size + sizeof(MemoryHeader))};
    MemoryHeader *pMemoryHeader{reinterpret_cast<MemoryHeader *>(pMemory)};
    pMemoryHeader->m_Filename = filename;
    pMemoryHeader->m_Line = line;
    return static_cast<void *>(static_cast<char *>(pMemory) + sizeof(MemoryHeader));
}

void operator delete(void *pMemory) noexcept
{
    char *pMemoryHeaderStart{reinterpret_cast<char *>(pMemory) - sizeof(MemoryHeader)};
    MemoryHeader *pMemoryHeader{reinterpret_cast<MemoryHeader *>(pMemoryHeaderStart)};
    cout << "Deleting memory allocated from: "
         << pMemoryHeader->m_Filename << ":" << pMemoryHeader->m_Line << endl;
    free(pMemoryHeader);
}

void *operator new[](size_t size, const char *filename, int line) noexcept
{
    void *pMemory{malloc(size + sizeof(MemoryHeader))};
    MemoryHeader *pMemoryHeader{reinterpret_cast<MemoryHeader *>(pMemory)};
    pMemoryHeader->m_Filename = filename;
    pMemoryHeader->m_Line = line;
    return static_cast<void *>(static_cast<char *>(pMemory) + sizeof(MemoryHeader));
}

void operator delete[](void *pMemory) noexcept
{
    char *pMemoryHeaderStart{reinterpret_cast<char *>(pMemory) - sizeof(MemoryHeader)};
    MemoryHeader *pMemoryHeader{reinterpret_cast<MemoryHeader *>(pMemoryHeaderStart)};
    cout << "Deleting memory allocated from: "
         << pMemoryHeader->m_Filename << ":" << pMemoryHeader->m_Line << endl;
    free(pMemoryHeader);
}

#define new new (__FILE__, __LINE__)
class MyClass1
{
  private:
    int m_Value{1};
};



int main_NewDelete()
{
    int *pInt{new int};
    *pInt = 1;
    delete pInt;
    MyClass1 *pClass{new MyClass1};
    delete pClass;
    return 0;
}

int main_globalOverloadNewDeleteArray()
{
    int *pInt{new int};
    *pInt = 1;
    delete pInt;
    MyClass1 *pClass{new MyClass1};
    delete pClass;
    const unsigned int NUM_ELEMENTS{5};
    int *pArray{new int[NUM_ELEMENTS]};
    delete[] pArray;
    return 0;
}

/*
//error: Not Compiling -  function returning function is not allowed
class MyClass
{
private:
    int m_Value{ 1 };
public:
    void* operator new(size_t size, const char* filename, int line) noexcept
    {
        cout << "Allocating memory for MyClass!" << endl;
        return malloc(size);
    }
    void operator delete(void* pMemory) noexcept
    {
        cout << "Freeing memory for MyClass!" << endl;
        free(pMemory);
    }
};

int main_operatorNew(int argc, char *argv[])
{
    int *pInt{new int};
    *pInt = 1;
    delete pInt;
    MyClass *pClass{new MyClass};
    delete pClass;
    const unsigned int NUM_ELEMENTS{5};
    MyClass *pArray{new MyClass[NUM_ELEMENTS]};
    delete[] pArray;
    return 0;
}

*/

int main(){
    main_globalOverloadNewDeleteArray();
    main_NewDelete();

    return 0;
}