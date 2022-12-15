// boolean type test for codegen

main() {
  var x, y;
  x = true;
  y = false;
  if(y) error 0;
  if(not x) error 1;
  return 0;
}
