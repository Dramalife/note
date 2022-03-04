/*
 * Ref: https://www.runoob.com/rust/rust-ownership.html
 */

pub mod ownership {
    pub mod func {

        /* Heap: auto free */
        pub fn sample_basic() {
            /* 1. Move */
            /* 1.1 in heap */
            let s4move = String::from("hello");
            let s_move = s4move; // s4move=NULL;
                                 /*   error[E0382]: borrow of moved value: `s4move` */
            //println!("{}, world!", s4move);
            println!("Move :in_heap : {}, world!", s_move);

            /* 1.2 in stack: i32, i64; bool; f32, f64; char;
            tuples(only inc above); */
            let i4move = 5;
            let i_move = i4move;
            println!("Move :in_stack: {}, {}", i4move, i_move);

            /* 2. Clone */
            let s4clone = String::from("hello");
            let s_clone = s4clone.clone();
            println!("Clone:in_heap : {}, {}!", s4clone, s_clone);

            // Heap: auto free s_move, s_clone & s4clone
        }

        pub fn funcall_arg() {
            fn takes_ownership(some_string: String) {
                println!("Large_type:Take: {}", some_string);
            }
            fn makes_copy(some_integer: i32) {
                println!("Basic_type:Take: {}", some_integer);
            }

            let s = String::from("hello");
            takes_ownership(s);
            println!("Large_type:After_move: {}", ">BORROW OF MOVED VALUE<");

            let x = 5;
            makes_copy(x);
            println!("Basic_type:After_move: {}", x);
        }

        pub fn funcall_ret() {
            fn gives_ownership() -> String {
                let some_string = String::from("hello");
                return some_string;
            }
            fn takes_and_gives_back(a_string: String) -> String {
                a_string
            }

            let s1 = gives_ownership();
            println!("Give to s1: {}", s1);
            let s2 = String::from("hello_s2");
            let s3 = takes_and_gives_back(s2);
            println!(
                "Give from s2 to s3: {}, s2:{}",
                s3, ">BORROW OF MOVED VALUE<"
            );
        }
    }

    pub mod ref_b {
        pub fn func_ref_borrow() {
            fn calculate_length(s: &String) -> usize {
                s.len()
            }

            let s1 = String::from("hello");
            let mut s2 = &s1;
            let len = calculate_length(&s1);
            println!(
                "Reference: length of '{}' is {}, refed by s2({}).",
                s1, len, s2
            );
            let mut s3 = s1;
            println!(
                "Reference: After_move: s3({}), s2({}).",
                s3, "cannot move out of `s1` because it is borrowed"
            );

            s2 = &s3; // RO
            println!("Reference: After_move: s3({}), Re-Ref by s2({}).", s3, s2);
            /*  `s2` is a `&` reference, so the data it refers to cannot be borrowed as mutable
             *   s2.push_str("oob");
             */

            let s4 = &mut s3; // RW
            s4.push_str("oob");
            println!("Reference: Mut_Ref: Change: s4({}).", s4);

            // let s5 = &mut s3;  // Error: second mutable borrow occurs here. (&mut: MAX==1)
            // let s6 = &s3;      // Error: mutable borrow
            // // println!("Reference: s6({}), s5({}), s4({})", s6, s5, s4);  // ^^^^

            // fn dangle() -> &String { // expected named lifetime parameter
            //   let s = String::from("hello_s");
            //   &s
            // }
            // let ref_to_nothing = dangle();
        }
    }
}
