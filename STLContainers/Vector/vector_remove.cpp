#include <iostream>
#include <vector>

using std::vector;

int main()
{

    // constructors used in the same order as described above:
    std::vector<int> first;                               // empty vector of ints
    std::vector<int> second(4, 100);                      // four ints with value 100
    std::vector<int> third(second.begin(), second.end()); // iterating through second
    std::vector<int> fourth(third);                       // a copy of third

    // the iterator constructor can also be used to construct from arrays:
    int myints[] = {16, 2, 77, 29, 108, 786, 255, 134};
    std::vector<int> fifth(myints, myints + sizeof(myints) / sizeof(int));

    std::cout << "The contents of fifth are:";
    for (std::vector<int>::iterator it = fifth.begin(); it != fifth.end(); ++it)
        std::cout << ' ' << *it;
    std::cout << '\n';

    int m = 2;
    //erase mth element
    std::vector<int> sixth(fifth);                       // a copy of fifth
    sixth.erase (sixth.begin()+m);

    std::cout << "The contents of sixth are:";
    for (std::vector<int>::iterator it = sixth.begin(); it != sixth.end(); ++it)
        std::cout << ' ' << *it;
    std::cout << '\n';

    //erase elements from mth to nth (element n excluded)

    std::vector<int> seventh(fifth);                       // a copy of fifth
    
    int n = 5;
    seventh.erase(seventh.begin()+m, seventh.begin()+n);
     
    std::cout << "The contents of seventh are:";
    for (std::vector<int>::iterator it = seventh.begin(); it != seventh.end(); ++it)
        std::cout << ' ' << *it;
    std::cout << '\n';

    return 0;
}