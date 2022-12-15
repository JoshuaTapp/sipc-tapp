// in-place insertion sort for array of integers
main(x) {
  var arr, m, n, i, j;

  m = 1000;
  n = 500;
  i = 0;
  j = 0;
  arr = [(m*n) of x];

  for (i : 0 .. n) {
    for (j : 0 .. m) {
      arr[i*m+j] = arr[i*m+j]+i*x;
      output arr[i*m+j];
    }
  }

  return 0;
}