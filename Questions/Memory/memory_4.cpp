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
using namespace std::chrono;

#ifndef CHRONO
#define CHRONO
#include <chrono>
#endif

// Calculating Performance Impacts of Code Changes
void RunTest(unsigned int numberIterations)
{
    auto start = std::chrono::high_resolution_clock::now();
    for (unsigned int i{0}; i < numberIterations; ++i)
    {
        unsigned int squared{i * i};
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto difference = end - start;
    cout << "Time taken: "
         << std::chrono::duration_cast<std::chrono::microseconds>(difference).count()
         << " microseconds!" << endl;
}
int main_PerformanceImpact()
{
    RunTest(10000000);
    RunTest(100000000);
    RunTest(1000000000);
    return 0;
}

//Exploring the Performance Impacts of Memory Access Patterns

const int NUM_ROWS{10000};
const int NUM_COLUMNS{1000};
int elements[NUM_ROWS][NUM_COLUMNS];
int *pElements[NUM_ROWS][NUM_COLUMNS];
int main_MemoryAccessPatterns()
{
    for (int i{0}; i < NUM_ROWS; ++i)
    {
        for (int j{0}; j < NUM_COLUMNS; ++j)
        {
            elements[i][j] = i * j;
            pElements[i][j] = new int{elements[i][j]};
        }
    }
    auto start = std::chrono::high_resolution_clock::now();
    for (int i{0}; i < NUM_ROWS; ++i)
    {
        for (int j{0}; j < NUM_COLUMNS; ++j)
        {
            const int result{elements[j][i]};
        }
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto difference = end - start;
    cout << "Time taken for j then i: "
         << std::chrono::duration_cast<std::chrono::microseconds>(difference).count()
         << " microseconds!" << endl;
    start = std::chrono::high_resolution_clock::now();
    for (int i{0}; i < NUM_ROWS; ++i)
    {
        for (int j{0}; j < NUM_COLUMNS; ++j)
        {
            const int result{elements[i][j]};
        }
    }
    end = std::chrono::high_resolution_clock::now();
    difference = end - start;
    cout << "Time taken for i then j: "
         << std::chrono::duration_cast<std::chrono::microseconds>(difference).count()
         << " microseconds!" << endl;
    start = std::chrono::high_resolution_clock::now();
    for (int i{0}; i < NUM_ROWS; ++i)
    {
        for (int j{0}; j < NUM_COLUMNS; ++j)
        {
            const int result{*(pElements[i][j])};
        }
    }
    end = std::chrono::high_resolution_clock::now();
    difference = end - start;
    cout << "Time taken for pointers with i then j: "
         << std::chrono::duration_cast<std::chrono::microseconds>(difference).count()
         << " microseconds!" << endl;
    return 0;
}

//Reducing Memory Fragmentation

class SmallBlockAllocator
{
  public:
    static const unsigned int BLOCK_SIZE{32};

  private:
    static const unsigned int NUM_BLOCKS{1024};
    static const unsigned int PAGE_SIZE{NUM_BLOCKS * BLOCK_SIZE};
    class Page
    {
      private:
        char m_Memory[PAGE_SIZE];
        bool m_Free[NUM_BLOCKS];
        Page *m_pNextPage;

      public:
        Page()
            : m_pNextPage{nullptr}
        {
            memset(m_Free, 1, NUM_BLOCKS);
        }
        ~Page()
        {
            if (m_pNextPage)
            {
                delete m_pNextPage;
                m_pNextPage = nullptr;
            }
        }
        void *Alloc()
        {
            void *pMem{nullptr};
            for (unsigned int i{0}; i < NUM_BLOCKS; ++i)
            {
                if (m_Free[i] == true)
                {
                    m_Free[i] = false;
                    pMem = &m_Memory[i * BLOCK_SIZE];
                    break;
                }
            }
            if (pMem == nullptr)
            {
                if (m_pNextPage == nullptr)
                {
                    m_pNextPage = new Page();
                }
                pMem = m_pNextPage->Alloc();
            }
            return pMem;
        }
        bool Free(void *pMem)
        {
            bool freed{false};
            bool inPage{pMem >= m_Memory &&
                        pMem <= &m_Memory[(NUM_BLOCKS * BLOCK_SIZE) - 1]};
            if (inPage)
            {
                // unsigned int index{
                //     //non-constant-expression cannot be narrowed from type 'unsigned long' to 'unsigned int' in initializer list [-Wc++11-narrowing]
                //     (reinterpret_cast<uintptr_t >(pMem) -
                //      reinterpret_cast<uintptr_t>(m_Memory)) /BLOCK_SIZE};//cast from pointer to smaller type 'unsigned int' loses information

                unsigned int index = 0; //ToDO: for compilation - temporary fix

                m_Free[index] = true;
                freed = true;
            }
            else if (m_pNextPage)
            {
                freed = m_pNextPage->Free(pMem);
                if (freed && m_pNextPage->IsEmpty())
                {
                    Page *old = m_pNextPage;
                    m_pNextPage = old->m_pNextPage;
                    old->m_pNextPage = nullptr;
                    delete m_pNextPage;
                }
            }
            return freed;
        }
        bool IsEmpty() const
        {
            bool isEmpty{true};
            for (unsigned int i{0}; i < NUM_BLOCKS; ++i)
            {
                if (m_Free[i] == false)
                {
                    isEmpty = false;
                    break;
                }
            }
            return isEmpty;
        }
    };
    Page m_FirstPage;

  public:
    SmallBlockAllocator() = default;
    void *Alloc()
    {
        return m_FirstPage.Alloc();
    }
    bool Free(void *pMem)
    {
        return m_FirstPage.Free(pMem);
    }
};
static SmallBlockAllocator sba;
void *operator new(size_t numBytes, const std::nothrow_t &tag) noexcept
{
    void *pMem{nullptr};
    if (numBytes <= SmallBlockAllocator::BLOCK_SIZE)
    {
        pMem = sba.Alloc();
    }
    else
    {
        pMem = malloc(numBytes);
    }
    return pMem;
}
void *operator new[](size_t numBytes, const std::nothrow_t &tag) noexcept
{
    void *pMem{nullptr};
    if (numBytes <= SmallBlockAllocator::BLOCK_SIZE)
    {
        pMem = sba.Alloc();
    }
    else
    {
        pMem = malloc(numBytes);
    }
    return pMem;
}
void operator delete(void *pMemory)
{
    if (!sba.Free(pMemory))
    {
        free(pMemory);
    }
}
void operator delete[](void *pMemory)
{
    if (!sba.Free(pMemory))
    {
        free(pMemory);
    }
}
int mai_SmallBlockAllocator(int argc, char *argv[])
{
    const unsigned int NUM_ALLOCS{2148};
    int *pInts[NUM_ALLOCS];
    for (unsigned int i{0}; i < NUM_ALLOCS; ++i)
    {
        pInts[i] = new int;
        *pInts[i] = i;
    }
    for (unsigned int i{0}; i < NUM_ALLOCS; ++i)
    {
        delete pInts[i];
        pInts[i] = nullptr;
    }
    return 0;
}

int main()
{
    main_MemoryAccessPatterns();
    main_PerformanceImpact();
    return 0;
}