pub mod command_line {
    pub fn get_args() {
        let args = std::env::args();
        for arg in args {
            println!("File_IO:CL:Arg: {}", arg);
        }
    }

    pub fn read_line() {
        use std::io::stdin;
        let mut str_buf = String::new();

        println!("File_IO:CL:ReadLine: Input please: ");
        //stdin()
        //    .read_line(&mut str_buf)
        //    .expect("File_IO:CL:ReadLine: Failed to read line.");
        println!("File_IO:CL:ReadLine: Input line is \n{}", str_buf);
    }
}

pub mod file_io {
    pub fn read_file() {
        fn read_file_all() {
            use std::fs;
            let text = fs::read_to_string("./Cargo.toml").unwrap();
            println!("File_IO:File:ReadFile(string): \n{}", text);

            let content = fs::read("./Cargo.toml").unwrap();
            println!("File_IO:File:ReadFile(content): \n{:?}", text);
        }
        fn read_file_stream() {
            use std::fs;
            use std::io::prelude::*;
            let mut buffer = [0u8; 5];
            let mut file = fs::File::open("./Cargo.toml").unwrap();
            file.read(&mut buffer).unwrap();
            println!("File_IO:File:ReadFile(content):Stream: {:?}", buffer);
            file.read(&mut buffer).unwrap();
            println!("File_IO:File:ReadFile(content):Stream: {:?}", buffer);
        }

        read_file_all();
        read_file_stream();
    }
    pub fn write_file() {
        fn write_file_truncate() {
            use std::fs;
            let tmp_write = String::from("./fileio.tmp");
            fs::write(&tmp_write, "File_IO:File:WriteFile: FROM RUST PROGRAM!\n").unwrap();

            use std::fs::File;
            use std::io::prelude::*;
            let mut file = File::create(&tmp_write).unwrap();
            file.write(b"File_IO:File:WriteFile: FROM RUST PROGRAM!22\n")
                .unwrap();
        }

        fn write_file_append() -> std::io::Result<()> {
            use std::fs::OpenOptions;
            use std::io::prelude::*;
            let tmp_write = String::from("./fileio.tmp");
            let mut file = OpenOptions::new().append(true).open(&tmp_write)?;
            file.write(b"File_IO:File:WriteFile: FROM RUST PROGRAM!33\n")?;
            Ok(())
        }

        fn write_file_rw() -> std::io::Result<()> {
            use std::fs::OpenOptions;
            use std::io::prelude::*;
            let tmp_write = String::from("./fileio.tmp");
            let mut file = OpenOptions::new().read(true).write(true).open(&tmp_write)?;
            file.write(b"File_IO:File:WriteFile: COVER\n")?;
            Ok(())
        }

        write_file_truncate();
        write_file_append();
        write_file_rw();
    }
}
