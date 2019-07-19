#ifndef STRIDE_ITER_HPP
#define STRIDE_ITER_HPP
#include "stride_iter.hpp"
#endif

#ifndef ALGORITHM
#define ALGORITHM
#include <algorithm>
#endif

#ifndef IOSTREAM
#define IOSTREAM
#include <iostream>
#endif

#include "kstride_iter.hpp"

using std::cout;
using std::endl;
using std::ostream_iterator;

//iterate over a sequence of elements two at a time.
// random-access iterator.
int main_stride_iterator()
{
    int a[] = {0, 1, 2, 3, 4, 5, 6, 7};
    stride_iter<int *> first(a, 2);
    stride_iter<int *> last(a + 8, 2);
    copy(first, last, ostream_iterator<int>(cout, " "));
    return 0;
}

int main_kstride_iterator()
//Since the step size is passed as a template parameter, the compiler can much more effectively optimize the code for the iterator, and the size of the iterator is reduced.
{
    int a[] = {0, 1, 2, 3, 4, 5, 6, 7};
    kstride_iter<int *, 2> first(a);
    kstride_iter<int *, 2> last(a + 8);
    copy(first, last, ostream_iterator<int>(cout, " "));
}


int main(){
    main_kstride_iterator();
    main_stride_iterator();
    return 0;
}