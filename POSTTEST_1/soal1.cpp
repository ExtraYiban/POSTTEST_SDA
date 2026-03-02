#include <iostream>
using namespace std;

/*
Analisis Kompleksitas Waktu FindMin

Pseudocode                Cost    Tmin      Tmax
----------------------------------------------------
procedure FindMin         C1      1         1
min <- A[0]               C2      1         1
for i <- 1 to n - 1       C3      n         n
if A[i] < min             C4      n-1       n-1
min <- A[i]               C5      0         n-1
end if                    C6      n-1       n-1
end for                   C7      n         n
return min                C8      1         1
end procedure             C9      1         1
----------------------------------------------------
Total waktu (T_n)                 O(n)      O(n)

==========================================================
Penjelasan Perhitungan:

Tmin(n)  (Best Case)
= C1(1) + C2(1) + C3(n) + C4(n-1) + C5(0) + C6(n-1) + C7(n) + C8(1) + C9(1)
=> O(n)

Tmax(n)  (Worst Case)
= C1(1) + C2(1) + C3(n) + C4(n-1) + C5(n-1) + C6(n-1) + C7(n) + C8(1) + C9(1)
=> O(n)

Kesimpulan:
Karena suku dominan adalah n (fungsi linear), maka kompleksitas waktu
baik untuk Best Case maupun Worst Case adalah O(n).
*/

int FindMin(int A[], int n, int &indexMin) {
    int min = A[0];
    indexMin = 0;

    for (int i = 1; i < n; i++) {
        if (A[i] < min) {
            min = A[i];
            indexMin = i;
        }
    }

    return min;
}

int main() {
    int A[8] = {1, 1, 2, 3, 5, 8, 13, 21};
    int indexMin;

    int minimum = FindMin(A, 8, indexMin);

    cout << "Nilai minimum: " << minimum << endl;
    cout << "Indeks minimum: " << indexMin << endl;

    return 0;
}