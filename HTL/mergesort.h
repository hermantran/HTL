#ifndef MERGESORT_H
#define MERGESORT_H
namespace HTL {
	template <typename T>
	T merge_sort(T& list) {
		if (list.size() <= 1) {
			return list;
		}

		T left, right;
		int middle = list.size() / 2;
		for (int i = 0; i < middle; i++) {
			T::data_type value = *(list.begin() + i);
			left.push_back(value);
		}
		for (int i = middle; i < list.size(); i++) {
			T::data_type value = *(list.begin() + i);
			right.push_back(value);
		}

		left = merge_sort(left);
		right = merge_sort(right);

		return merge(left, right);
	}

	template <typename T>
	T merge(T& left, T& right) {
		T result;
		while (left.size() > 0 || right.size() > 0) {
			T::data_type leftValue, rightValue;
			if (left.size() > 0) {
				leftValue = *(left.begin());			
			}
			if (right.size() > 0) {
				rightValue = *(right.begin());
			}

			if (left.size() > 0 && right.size() > 0) {
				if (leftValue <= rightValue) {
					result.push_back(leftValue);
					left.erase(left.begin());
				}
				else {
					result.push_back(rightValue);
					right.erase(right.begin());
				}
			}
			else if (left.size() > 0) {
				result.push_back(leftValue);
				left.erase(left.begin());
			}
			else if (right.size() > 0) {
				result.push_back(rightValue);
				right.erase(right.begin());
			}
		}

		return result;
	}
}
#endif