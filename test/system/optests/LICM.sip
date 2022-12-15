
fold(a, i, f) {
  var s, e, x, y;
  s = i;
  x = 10;
  y = 20;

  for (e : a) {                 // iterator-style for loop
    s = f(s,e) + (x * y);
    output s;
  }
  return s;
}

sum(x,y) { return x + y; }

main() {
  var a;
  a = [ 13, 7, -4, 14, 0 ];

  output fold(a, 2, sum);

  return 0;
}
