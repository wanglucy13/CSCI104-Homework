#ifndef MSORT_H
#define MSORT_H
#include <vector>

using namespace std;

template <class T, class Comparator>
void msort (vector<T>& myArray, Comparator comp){
	MergeSort(myArray, 0, myArray.size() - 1, comp);
}

template <class T, class Comparator>
void MergeSort(vector<T>& myArray, int l, int r, Comparator comp)
{
    if (l<r) { // otherwise, just one element, which is sorted
        int m = (l+r)/2;
        MergeSort(myArray, l, m, comp);
        MergeSort(myArray, m+1, r, comp);
        merge(myArray, l, r, m, comp); // this is a separate function given below
    }
}

template <class T, class Comparator>
void merge (vector<T>& myArray, int l, int r, int m, Comparator comp)
{
  T temp[r+1-l];
  // trace through the two subarrays, copying into a temporary one
  int i = l, j = m+1, k = 0;
  while (i <= m || j <= r)  // at least one subarray contains another element
       {
         if (i <= m && (j > r || comp(myArray[i], myArray[j])))
            // next smallest element in left subarray
            { temp[k] = myArray[i]; i ++; k ++; }
         else { temp[k] = myArray[j]; j ++; k ++; }
            // next smallest element in right subarray
       }
  // now copy over the merged array into the original
  for (k = 0; k < r+1-l; k ++){
		myArray[k+l] = temp[k];
  }
}

#endif