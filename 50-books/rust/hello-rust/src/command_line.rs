pub mod print_to_cmdline {
    pub fn print_var() {
        let a = 12;

        println!("a is {}", a);
        println!("a is {}, a again is {}", a, a);
        println!("a is {0}, a again is {0}", a);
        println!("{{}}");
    }
}
pub fn command_line() {
    println!("------------------");
    println!("1. Command line printing;");
    println!("2. Is a func;");

    let a = 66;
    println!("{{");
    println!("a is {0}, again is {0}", a);
}
