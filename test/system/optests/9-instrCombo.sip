
comp(a, b, c, d) {
  var e, f, g, h;

  e = a + b;
  f = c * d;
  g = e + f;
  h = g * a;

  if (h > 10) {
    h = h * 2;
  } else {
    h = h - 2;
  }

  return h;
}



main() {
  var i, sum;

  i = 0;
  sum = 0;

  for (i : 0 .. 100) {
    sum = sum + comp(i, i+1, i+2, i+3);
  }

  return sum;
}
