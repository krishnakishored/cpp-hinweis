#ifndef IOSTREAM
#define IOSTREAM
#include <iostream>
#endif

#ifndef VECTOR
#define VECTOR
#include <vector>
#endif

#ifndef STRING
#define STRING
#include <string>
#endif

#ifndef LIST
#define LIST
#include <list>
#endif

#ifndef ALOGORITHM
#define ALOGORITHM
#include <algorithm>
#endif

#ifndef ITERATOR
#define ITERATOR
#include <iterator>
#endif


#ifndef SET
#define SET
#include <set>
#endif

using std::ostream;
using std::istream_iterator;
using std::cout;
using std::endl;
using std::cin;
using std::set;
using std::vector;



template <typename Fwd>
void printRange(Fwd first, Fwd last, char delim = ',', ostream &out = cout)
{
    out << "{";
    while (first != last)
    {
        out << *first;
        if (++first != last)
            out << delim << ' ';
    }
    out << "}" << endl;
}


template <typename C>
void printContainer(const C &c, char delim = ',', ostream &out = cout)
{
    printRange(c.begin(), c.end(), delim, out);
}