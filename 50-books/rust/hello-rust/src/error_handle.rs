/*
 * https://www.runoob.com/rust/rust-error-handle.html
 */

pub fn error_handle() {
    fn sample_open_file() {
        use std::fs::File;

        let f = File::open("hello.txt");
        match f {
            Ok(fileee) => {
                println!("ErrorHandle:OpenFile:Match: File opened successfully.");
            }
            Err(errrr) => {
                println!("ErrorHandle:OpenFile:Match: Failed to open the file.");
            }
        }

        let f = File::open("hello.txt");
        if let Ok(ffff) = f {
            println!("ErrorHandle:OpenFile:If: File opened successfully.");
        } else {
            println!("ErrorHandle:OpenFile:If: Failed to open the file.");
        }
    }

    fn sample_unwrap_expect() {
        use std::fs::File;
        // let f1 = File::open("hello.txt").unwrap();
        // let f2 = File::open("hello.txt").expect("Failed to open.");
    }

    fn passing_error() {
        fn f(i: i32) -> Result<i32, bool> {
            if i >= 0 {
                Ok(i)
            } else {
                Err(false)
            }
        }
        fn g(i: i32) -> Result<i32, bool> {
            let t = f(i)?; // Err? return!
            Ok(t)
        }
        fn m() {
            let r = g(10000);
            if let Ok(v) = r {
                println!("ErrorHandle:PassingError: Ok, g(10000) = {}", v);
            } else {
                println!("ErrorHandle:PassingError: Err.");
            }
        }

        m();
    }

    fn sample_kind() {
        use std::fs::File;
        use std::io;
        use std::io::Read;
        fn read_text_from_file(path: &str) -> Result<String, io::Error> {
            let mut f = File::open(path)?;
            let mut s = String::new();
            f.read_to_string(&mut s)?;
            Ok(s)
        }

        fn m() {
            let str_file = read_text_from_file("hello.txt");
            match str_file {
                Ok(sss) => {
                    println!("ErrorHandle:Kind: Str({}).", sss)
                }
                Err(eee) => match eee.kind() {
                    io::ErrorKind::NotFound => {
                        println!("ErrorHandle:Kind: No such file.");
                    }
                    _ => {
                        println!("ErrorHandle:Kind: Cannot read the file.");
                    }
                },
            }
        }
        m();
    }

    sample_open_file();
    sample_unwrap_expect();
    passing_error();
    sample_kind();
}
