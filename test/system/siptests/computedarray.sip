
main() {
  var a, b;
  a = [ 13, 7, -4, 14, 0 ];

  b = [ #a of a[0] ];



  if (b[3] != 13) error b[3]; // This line is the issue due to a[0]

  return 0;
}
