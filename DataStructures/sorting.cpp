//QuickSort
#include <algorithm>//for rand()
#include<iostream>
#include<vector>
#include<string>
#include<iterator>//for ostream_iterator
#include <iomanip>//for setw in bucket sort


using namespace std;


//Util Functions
//*****************************************************************

ostream_iterator<int, char> myOutputIterator(cout, " ");// works like cout << 2013 << " ";

//Create a random array of numbers
struct RandomGenerator {
	int maxValue;
	RandomGenerator(int max) :	maxValue(max) {}
	int operator()() {
		return (rand() % maxValue)+1;//to avoid 0
	}
};

void generateRandomNumVector(vector<int> &vecOfRandomNums,int maxRandValue = 100) {
	// Generate 10 random numbers by a Functor and fill it in vector
	std::generate(vecOfRandomNums.begin(), vecOfRandomNums.end(),
								RandomGenerator(maxRandValue)); //not truly random????
	
	/* //Random Shuffle
	random_shuffle(dataInput.begin(), dataInput.end());
	cout << endl;
	copy(dataInput.begin(), dataInput.end(), myOutputIterator);*/
}

//*****************************************************************
//Sortings 
//Quick Sort

int Partition(vector<int> &dataInput, int low, int high) {
	//int pivot = low + rand()%(high - low + 1);//TODO:better to select a random pivot 
	int pivot = low;
	for (int i = pivot + 1; i <= high; ++i)
	{
		if (dataInput[i] < dataInput[pivot])
		{
			std::swap(dataInput[i], dataInput[pivot]);
			if (i != pivot + 1)
			{
				std::swap(dataInput[i], dataInput[pivot + 1]);
			}
			pivot = pivot + 1;
		}
	}
	return pivot;
}

void QuickSort(vector<int> & dataInput, int low, int high) {
	if (low >= high) return;
	int pivot = Partition(dataInput, low, high);//returns pivot
	cout << "\nAfter partition, " << dataInput[pivot]<<" as Pivot: ";
	copy(dataInput.begin(), dataInput.end(), myOutputIterator);
	QuickSort(dataInput, low, pivot - 1);
	QuickSort(dataInput, pivot + 1, high);
}
//*****************************************************************

//Selection sort
//useful for small lists and where swapping is expensive
// does at most n swaps


void SelectionSort(std::vector<int> & dataInput,bool order = 0) {
	vector<int>::iterator elemSelected;
	int length = static_cast<int>(dataInput.size());

	for (int i = 1; i < length; ++i) {
		elemSelected = min_element(dataInput.begin()+i, dataInput.end()); //returns iterator of minimum element
		if (dataInput[i - 1] >= *elemSelected) {//start comparison with first element
			std::swap(dataInput[i - 1], *elemSelected);
		}
	}
}


void SelectionSort_2(std::vector<int> & dataInput)
{
	int length = static_cast<int>(dataInput.size());
	for (int i = 0; i < length; ++i)
	{
		int min = i;
		for (int j = i + 1; j < length; ++j)
		{
			if (dataInput[j] < dataInput[min])
			{
				min = j;
			}
		}
		if (min != i)
		{
			swap(dataInput[i], dataInput[min]);
		}
	}
}
//*****************************************************************

//Insertion sort
//useful for small and mostly sorted lists
//expensive to move array elements

//
//void insertionSort(int arr[], int length) {
//	int i, j, tmp;
//	for (i = 1; i < length; i++) {
//		j = i;
//		while (j > 0 && arr[j - 1] > arr[j]) {
//			tmp = arr[j];
//			arr[j] = arr[j - 1];
//			arr[j - 1] = tmp;
//			j--;
//		}
//	}
//}

void InsertionSort(std::vector<int>& dataInput, bool order = 0) {	
	int i, j=0;

	int length = static_cast<int>(dataInput.size());
	for (i = 1; i < length ; i++) 
	{
		j = i; 
		while(j>0 && dataInput[j] < dataInput[j-1])
		{
			std::swap(dataInput[j], dataInput[j - 1]);//use insert instead of swap//?????
			j--;
		}
	}
}


void InsertionSort_2(std::vector<int> & dataInput)
{
	int length = static_cast<int>(dataInput.size());
	for (int i = 1; i < length; ++i)
	{
		bool inplace = true;
		int j = 0;
		for (; j < i; ++j)
		{
			if (dataInput[i] < dataInput[j])
			{
				inplace = false;
				break;
			}
		}

		if (!inplace)
		{
			int save = dataInput[i];
			for (int k = i; k > j; --k)
			{
				dataInput[k] = dataInput[k - 1];
			}
			dataInput[j] = save;
		}
	}
}


//*****************************************************************
//Merge Sort

void Merge(std::vector<int> & data, int lowl, int highl, int lowr, int highr)
{
	int tmp_low = lowl;
	std::vector<int> tmp;

	while (lowl <= highl && lowr <= highr)
	{
		if (data[lowl] < data[lowr])
		{
			tmp.push_back(data[lowl++]);
		}
		else if (data[lowr] < data[lowl])
		{
			tmp.push_back(data[lowr++]);
		}
		else
		{
			tmp.push_back(data[lowl++]);
			tmp.push_back(data[lowr++]);
		}
	}

	while (lowl <= highl)
	{
		tmp.push_back(data[lowl++]);
	}

	while (lowr <= highr)
	{
		tmp.push_back(data[lowr++]);
	}

	std::vector<int>::const_iterator iter = tmp.begin();

	for (; iter != tmp.end(); ++iter)
	{
		data[tmp_low++] = *iter;
	}
}

void MergeSort(std::vector<int> & data, int low, int high)
{
	if (low >= high)
	{
		return;
	}

	int mid = low + (high - low) / 2;

	MergeSort(data, low, mid);

	MergeSort(data, mid + 1, high);

	Merge(data, low, mid, mid + 1, high);
}

//http://www.bogotobogo.com/Algorithms/bucketsort.php

#define NARRAY 8  /* array size */
#define NBUCKET 5 /* bucket size */
#define INTERVAL 10 /* bucket range */

struct Node
{
	int data;
	struct Node *next;
};

void BucketSort(int arr[]);
struct Node *InsertionSort(struct Node *list);
void print(int arr[]);
void printBuckets(struct Node *list);
int getBucketIndex(int value);

void BucketSort(int arr[])
{
	int i, j;
	struct Node **buckets;

	/* allocate memory for array of pointers to the buckets */
	buckets = (struct Node **)malloc(sizeof(struct Node*) * NBUCKET);

	/* initialize pointers to the buckets */
	for (i = 0; i < NBUCKET; ++i) {
		buckets[i] = NULL;
	}

	/* put items into the buckets */
	for (i = 0; i < NARRAY; ++i) {
		struct Node *current;
		int pos = getBucketIndex(arr[i]);
		current = (struct Node *) malloc(sizeof(struct Node));
		current->data = arr[i];
		current->next = buckets[pos];
		buckets[pos] = current;
	}

	/* check what's in each bucket */
	for (i = 0; i < NBUCKET; i++) {
		cout << "Bucket[" << i << "] : ";
		printBuckets(buckets[i]);
		cout << endl;
	}

	/* sorting bucket using Insertion Sort */
	for (i = 0; i < NBUCKET; ++i) {
		buckets[i] = InsertionSort(buckets[i]);
	}

	/* check what's in each bucket */
	cout << "-------------" << endl;
	cout << "Bucktets after sorted" << endl;
	for (i = 0; i < NBUCKET; i++) {
		cout << "Bucket[" << i << "] : ";
		printBuckets(buckets[i]);
		cout << endl;
	}

	/* put items back to original array */
	for (j = 0, i = 0; i < NBUCKET; ++i) {
		struct Node *node;
		node = buckets[i];
		while (node) {
			arr[j++] = node->data;
			node = node->next;
		}
	}

	/* free memory */
	for (i = 0; i < NBUCKET; ++i) {
		struct Node *node;
		node = buckets[i];
		while (node) {
			struct Node *tmp;
			tmp = node;
			node = node->next;
			free(tmp);
		}
	}
	free(buckets);
	return;
}

/* Insertion Sort */
struct Node *InsertionSort(struct Node *list)
{
	struct Node *k, *nodeList;
	/* need at least two items to sort */
	if (list == 0 || list->next == 0) {
		return list;
	}

	nodeList = list;
	k = list->next;
	nodeList->next = 0; /* 1st node is new list */
	while (k != 0) {
		struct Node *ptr;
		/* check if insert before first */
		if (nodeList->data > k->data) {
			struct Node *tmp;
			tmp = k;
			k = k->next;
			tmp->next = nodeList;
			nodeList = tmp;
			continue;
		}

		for (ptr = nodeList; ptr->next != 0; ptr = ptr->next) {
			if (ptr->next->data > k->data) break;
		}

		if (ptr->next != 0) {
			struct Node *tmp;
			tmp = k;
			k = k->next;
			tmp->next = ptr->next;
			ptr->next = tmp;
			continue;
		}
		else {
			ptr->next = k;
			k = k->next;
			ptr->next->next = 0;
			continue;
		}
	}
	return nodeList;
}

int getBucketIndex(int value)
{
	return value / INTERVAL;
}

void print(int ar[])
{
	int i;
	for (i = 0; i < NARRAY; ++i) {
		cout << setw(3) << ar[i];
	}
	cout << endl;
}

void printBuckets(struct Node *list)
{
	struct Node *cur = list;
	while (cur) {
		cout << setw(3) << cur->data;
		cur = cur->next;
	}
}

int main(void)
{
	int array[NARRAY] = { 29,25,3,49,9,37,21,43 };

	cout << "Initial array" << endl;
	print(array);
	cout << "-------------" << endl;

	BucketSort(array);
	cout << "-------------" << endl;
	cout << "Sorted array" << endl;
	print(array);
	return 0;
}



//*****************************************************************

/*
TODO: class to generate input sequence - random, sorted, partially sorted,& so on.
*/

int main_General() {

	cout << "Sorting Algorithms:\n";
	cout << "Enter: \n 1 to generate 10 random numbers < 100 \n 2 for user input \n\n";
	
	//vector<int> dataInput;
	//dataInput.reserve(10);//to use generate vector must be initialized
	vector<int> dataInput(10);
	generateRandomNumVector(dataInput);

	//ostream_iterator template works like an adapter,which is a class or function that converts an interface to another interface
	
	copy(dataInput.begin(), dataInput.end(), myOutputIterator);

	/*Choose a sorting*/
	cout << "\nChoose a sorting:\n";
	cout << "1. Quick Sort" << endl;
	cout << "2. Selection Sort" << endl;
	//QuickSort(dataInput, 0, static_cast<int>(dataInput.size()) - 1); //should have wrapper that takes only a vector

	//SelectionSort(dataInput);
	InsertionSort(dataInput);

	cout << "\n\nSorted:" ;
	copy(dataInput.begin(), dataInput.end(), myOutputIterator);
	return 0;
}



//Design a strategy pattern of sort algorithms
class AllSorts
{
public:
	AllSorts();
	~AllSorts();

protected:
	vector<int> m_dataInput;
	int low = 0;
	int high = static_cast<int>( m_dataInput.size());
};


class QuickSort : public AllSorts {


};

AllSorts::AllSorts()
{
}

AllSorts::~AllSorts()
{
}