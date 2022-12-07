main(num, init, index) {
  var a;
  a = [num of init];
  if(a[index] != init) error a[index];
  if(#a != num) error #a;
  return 0;
}