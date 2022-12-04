main() {
    var arr, i;
    i = 1;
    arr = [3 of i];
    if(#arr != 3) error #arr;
    if(arr[0] != i) error arr[0];
    if(arr[1] != i) error arr[1];
    if(arr[2] != i) error arr[2];
    return 0;
}