#include <stdlib.h>
#include <stdio.h>

void array_random_numbers(int *m, int cnt, int a, int b){
    for (int i = 0; i < cnt; i++){
        m[i] = (rand() % (b - a)) + a;
    }
}

void in_keyboard(int *m, int cnt){
    for (int i = 0; i < cnt; i++) {
    scanf("%d", &m[i]);
    }
}

void out(int *m, int cnt, int f){
    for (int i = 1; i <= cnt; i++){
        printf("%3d", i);
    }
    printf("\n");

    for (int i = 0; i < cnt; i++){
        printf("%3d", m[i]);
    }
    printf("\n");
    if (f == 1) printf("\n");
}

void swap(int *x, int *y){
    int temp;
    temp=*x;
    *x=*y;
    *y=temp;
}


// ----------Хоар-----------

void QuickSort(int A[], int n, int first, int last, unsigned long int *a, unsigned long int *c){
    int l = first, r = last; /*левый и правый счетчики*/
    int pivot = A[(l+r)/2]; /*опорное значение*/
    *a += 1;
    while (l <= r) {
        *c += 1;
        while (A[l] < pivot){
            *c += 1;
            l++;
        }
        *c += 1;
        while (A[r] > pivot){
            *c += 1;
            r--;
        }
        if (l<=r){
            swap(&A[l],&A[r]); /*перестановка двух элементов*/
            if (l != r) out(A, n, 1);
            *a += 3;
            l++;
            r--;
        }
    } /*Рекурсивная сортировка:*/
    if (first<r){
        QuickSort(A, n, first, r, a, c); /*- левого участка, */
    }
    if (l<last){
        QuickSort(A, n, l, last, a, c); /*- правого участка.*/
    }
}


// ---------Пирамида---------

void TreeRebuild(int A[], int i, int n, int N, unsigned long int *a, unsigned long int *c){
    int ancestor = i;
    int top = A[ancestor];
    *a += 1;
    int descendant = 2 * ancestor + 1;
    int pp = 0;
    while (descendant <= n && !pp) {
        if (descendant < n){// если потомков 2
            *c += 1;
            if (A[descendant] < A[descendant+1]) // находим наибольшего потомка
                descendant++;
        }
        *c += 1;;
        if (top <= A[descendant]){
            A[ancestor] = A[descendant];
            *a += 1;
            ancestor = descendant; 
            descendant = 2 * ancestor + 1;
        }
        else {
            pp = 1;
        }
    }
    if (A[ancestor] != top){
        A[ancestor] = top;
        *a += 1;
        out(A, N, 1);
    }
}

void TreeSort(int A[], int n, unsigned long int *a, unsigned long int *c){
    for (int i=n/2-1; i>=0; i--){
        TreeRebuild(A, i, n-1, n, a, c);
    }
    for (int i=n-1; i>=1; i--) {
        swap(&A[0],&A[i]);
        out(A, n, 1);
        *a += 3;
        TreeRebuild(A, 0, i-1, n, a, c); 
    }
}

int main()
{
    int n;
    scanf("%d", &n);
    int A[n], B[n];
    // in_keyboard(A, n);
    array_random_numbers(A, n, 0, 100);
    for (int i = 0; i < n; i++){ 
        B[i] = A[i];
    }
    unsigned long int assignment_pyr = 0, comparison_pyr = 0;
    unsigned long int assignment_hoar = 0, comparison_hoar = 0;

    out(A, n, 1);

    // Хоар
    QuickSort(B, n, 0, n-1, &assignment_hoar, &comparison_hoar);
    printf("%lu %lu\n", assignment_hoar, comparison_hoar);
    printf("\n");

    // Пирамида
    TreeSort(A, n, &assignment_pyr, &comparison_pyr);
    printf("%lu %lu\n", assignment_pyr, comparison_pyr);
    
    return 0;
}