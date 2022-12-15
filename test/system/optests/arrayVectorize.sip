main() {
    var arr1, arr2, arr3, i;

    i = 0;
    arr1 = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10];
    arr2 = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10];
    arr3 = [10 of 0];

    for (i : 0 .. 10) {
        arr3[i] = arr1[i] * arr2[i];
        output arr3[i];
    }

    return 0;
}