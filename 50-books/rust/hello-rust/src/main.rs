fn main() {
  println !("Hello, world!");

  command_line();

  let ret = func_arg_int(77, 88);
  println !("ret={}", ret);
}

fn command_line() {
  println !("------------------");
  println !("1. Command line printing;");
  println !("2. Is a func;");

  let a = 66;
  println !("{{");
  println !("a is {0}, again is {0}", a);
}

fn func_arg_int(ax : i32, ay : i32)->i32 {
  println !("------------------");
  println !("1. Func with arg;");
  println !("2. Func with ret;");

  println !("ax={}", ax);
  println !("ay={}", ay);

  return ax + ay;
}
