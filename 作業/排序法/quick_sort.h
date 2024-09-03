# ifndef QUICK_SORT_H
# define QUICK_SORT_H

// 函數原型聲明
void swap(int *v, int a, int b);
//小到大 快速排序法
void q_sort(int *array_to_sort, int *array_that_sorted_by, int start_index, int end_index);
//反轉陣列
void reverse_array(int *array, int start_index, int end_index);

#endif // QUICK_SORT_H