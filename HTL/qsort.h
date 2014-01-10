#ifndef QSORT_H
#define QSORT_H
namespace HTL {
	template <typename T>
	void quicksort(T& v, int left, int right) {
		if (left < right) {
			int middleIndex = (left + right) / 2;
			int pivotIndex = partition(v, left, right, middleIndex);
			quicksort(v, left, pivotIndex - 1);
			quicksort(v, pivotIndex + 1, right);
		}
	}

	template <typename T>
	int partition(T& v, int left, int right, int pivotIndex) {
		T::data_type pivotValue = *(v.begin() + pivotIndex);
		*(v.begin() + pivotIndex) = *(v.begin() + right);
		*(v.begin() + right) = pivotValue;
		int storeIndex = left;

		for (int i = left; i < right; i++) {
			if (*(v.begin() + i) <= pivotValue) {
				T::data_type iValue = *(v.begin() + i);
				*(v.begin() + i) = *(v.begin() + storeIndex);
				*(v.begin() + storeIndex) = iValue;
				storeIndex++;
			}
		}

		T::data_type rightValue = *(v.begin() + right);
		*(v.begin() + right) = *(v.begin() + storeIndex);
		*(v.begin() + storeIndex) = rightValue;
		return storeIndex;
	}
}
#endif