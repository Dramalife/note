pub mod example {

    pub fn arg_int(ax: i32, ay: i32) -> i32 {
        println!("------------------");
        println!("1. Func with arg;");
        println!("2. Func with ret;");

        println!("ax={}", ax);
        println!("ay={}", ay);

        return ax + ay;
    }

    pub fn body_exp() -> i32 {
        fn five() -> i32 {
            let x = 4;
            x + 1
        }
        return five();
    }
}
