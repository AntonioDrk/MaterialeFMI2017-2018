#include <iostream>
#define BITS 2

void radixsort(int *a, int n) {
    int i, b[500], m = a[0], pos = 0;
    int buckets=1<<BITS;
    int mask=buckets-1;
    for (i = 0; i < n; i++) if (a[i] > m) m = a[i];

    while ((m>>(pos*BITS)) > 0) {
        int bucket[1<<BITS] = { 0 };
        for (i = 0; i < n; i++)       bucket[(a[i]>>(pos*BITS)) & mask]++;
        for (i = 1; i < buckets; i++) bucket[i] += bucket[i - 1];
        for (i = n - 1; i >= 0; i--)  b[--bucket[(a[i]>>(pos*BITS)) & mask]] = a[i];
        for (i = 0; i < n; i++)       a[i] = b[i];
        pos++;
    }
}


void afisare(struct Node root) {
    struct Node *p = root;
    if (p != NULL) {
        printf("%d varf=", p->data);
    }
    p = p->next;
    while (p != NULL) {
        printf(" %d ", p->data);
        if (p->next == NULL) {
            printf("%d baza", p->data);
        }
        p = p->next;
    }
}


int main() {
    int a[] = {-11,-23,-100,10,43,21,0,33,2,1,0,49,13,123,69,90};
    radixsort(a,16);
    for (int i = 0; i < 16; ++i) {
        std::cout << a[i] << " ";
    }
    return 0;
}