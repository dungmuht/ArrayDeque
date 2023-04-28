    #include<stdio.h>
#include <stdlib.h>
typedef struct Deque {
    char* fData;
    char* bData;
    int fLast;
    int bLast;
    int size;
} Deque;
Deque createDeque() {
    Deque dq;
    printf("Enter the size of Deque: ");
    scanf("%d", &dq.size);
    dq.fData = (char*)malloc(sizeof(char)*dq.size/2);
    dq.bData = (char*)malloc(sizeof(char)*dq.size/2 + dq.size%2);
    dq.fLast = 0;
    dq.bLast = 0;
    return dq;
}
int isDeQEmpty(Deque dq) {
    if (dq.fLast || dq.bLast) {
        return 0;
    } else {
        return 1;
    }
}
int lShift(Deque* dq, int value) { // value = 3
    if (dq->fLast+value <= dq->size/2) { // fLast = 4 <= dq->size/2 = 50
        int i;
        for (i=dq->fLast-1; i>=0; i--) { // i -> 3 ~ 0
            dq->fData[i+value] = dq->fData[i]; // fData[6 ~ 3] = fData[3~0]
        }
        dq->fLast += value;
        for (; i>=-value; i--) { // i -> -1 ~ -3
            dq->fData[i+value] = dq->bData[-i-1]; // fData[2~0] = bData[0~2]
        }
        dq->bLast -= value;
        for (i=0; i<dq->bLast; i++) { // i -> 3 ~ 5
            dq->bData[i] = dq->bData[i+value]; // bData[3~5] = bData[6~8]
        }
        return 1;
    } else {
        printf("LeftDeque is almost full\n");
        return 0;
    }
}
int rShift(Deque* dq, int value) { // value = 3
    if (dq->bLast + value <= dq->size/2 + dq->size%2) { // (bLast = 5) + (value = 3) <= (dq->size/2 = 50) + (dq->size%2 = 0)
        int i;
        for (i=dq->bLast-1; i>=0; i--) { // i -> 4 ~ 0
            dq->bData[i+value] = dq->bData[i];  // bData[7 ~ 3] = bData[4~0]
        }
        dq->bLast += value;
        for (; i>=-value; i--) { // i -> -1 ~ -3
            dq->bData[i+value] = dq->fData[-i-1]; // bData[2~0] = fData[0~2]
        }
        dq->fLast -= value;
        for (i=0; i<dq->fLast; i++) { // i -> 3 ~ 5
            dq->fData[i] = dq->fData[i+value]; // fData[3~5] = fData[6~8]
        }
        return 1;
    } else {
        printf("RightDeque is almost full\n");
        return 0;
    }
}
void insertFront(Deque* dq, char item) {
    if (isDeQEmpty(*dq)) {
        dq->bData[0] = item;
        dq->bLast = 1;
    } else if (dq->fLast < dq->size/2) {
        dq->fData[dq->fLast] = item;
        dq->fLast += 1;
    } else if (dq->bLast < dq->size/2 + dq->size%2) {
        if (rShift(dq, (dq->fLast - dq->bLast)/2 + (dq->fLast - dq->bLast)%2)){
            dq->fData[dq->fLast] = item;
            dq->fLast += 1;
        }
    } else {
        printf("Deque is full\n");
    }
}
void insertRear(Deque* dq, char item) {
    if (dq->bLast < dq->size/2 + dq->size%2) {
        dq->bData[dq->bLast] = item;
        dq->bLast += 1;
    } else if (lShift(dq, (dq->bLast - dq->fLast)/2 + (dq->bLast - dq->fLast)%2)) {
        dq->bData[dq->bLast] = item;
        dq->bLast += 1;
    } else {
        printf("Deque is full\n");
    }

}
char deleteFront(Deque* dq) {
    if (isDeQEmpty(*dq)) {
        printf("Deque is empty\n");
        return;
    } else if (dq->fLast != 0) {
        dq->fLast -= 1;
    } else {
        int i = 1;
        for (; i <= dq->bLast/2 + dq->bLast%2; i++) {
            dq->fData[dq->bLast/2-i] = dq->bData[i]; 
        }
        for (; i < dq->bLast; i++) {
            dq->bData[i-dq->bLast/2] = dq->bData[i];
        }
        dq->bLast /= 2;
        dq->fLast = dq->bLast + dq->bLast%2;
    }
}
char deleteRear(Deque* dq) {
    if (isDeQEmpty(*dq)) {
        printf("Deque is empty\n");
        return;
    } else if (dq->bLast != 0) {
        dq->bLast -= 1;
    } else { // 012345
        int i = 1;
        for (; i < dq->fLast/2 + dq->fLast%2; i++) { // i < 3 ->  1, 2
            dq->bData[dq->fLast/2-i] = dq->fData[i]; // 2-i -> 1, 0
        }
        for (; i < dq->fLast; i++) { // i < 5  -> 3, 4
            dq->fData[i-dq->fLast/2] = dq->fData[i]; // i-2.5 -> 0, 1
        }
        dq->fLast /= 2;
        dq->bLast = dq->fLast + dq->bLast%2;
    }
}
char peekFront(Deque* dq) {
    return dq->fData[dq->fLast-1];
}
char peekRear(Deque* dq) {
    return dq->bData[dq->bLast-1];
}
void printdq(Deque* dq) {
    printf("Deque = [");
    for (int i=dq->fLast-1; i>=0; i--) {
        printf("%c", dq->fData[i]);
    }
    printf("|");
    for (int i=0; i<dq->bLast; i++) {
        printf("%c", dq->bData[i]);
    }
    printf("]\n");
}
void main() {
    Deque deque = createDeque();
    Deque* deque1 = &deque;
    for (int i=0; i<deque1->size/2 + deque1->size%2; i++) {
        insertFront(deque1, 'a'+i);
    }
    //for (int i=0; i<deque1->size/2; i++) {
    //    insertRear(deque1, '0'+i);
    //
    insertRear(deque1, '0' + 0);
    insertRear(deque1, '0' + 1);
    insertRear(deque1, '0' + 2);
    insertRear(deque1, '0' + 3);
    insertRear(deque1, '0' + 4);
    printdq(deque1);
}