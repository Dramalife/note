/*
 * https://www.runoob.com/rust/rust-enum.html
 */

pub fn enum_dl() {
    fn enum_basic() {
        #[derive(Debug)]
        enum Book {
            Papery,
            Electronic,
        }

        let book = Book::Papery;
        println!("Enum:Basic: {:?}", book);
    }

    fn enum_tuple() {
        #[derive(Debug)]
        enum Book {
            Papery(u32),
            Test(u32),
            Electronic(String),
        }
        let book = Book::Papery(1001);
        let book2 = Book::Test(9999);
        let ebook = Book::Electronic(String::from("url://..."));
        println!("Enum:Tuple: {:?}", book);
        println!("Enum:Tuple: {:?}", ebook);
        fn enum_tuple_match(b: &Book) {
            match b {
                Book::Papery(xname) => {
                    println!("Enum:Tuple:Match: ({:?})", xname);
                }
                Book::Test(yname) => {
                    println!("Enum:Tuple:Match: ({:?})", yname);
                }
                Book::Electronic(xname) => {
                    println!("Enum:Tuple:Match: ({:?})", xname);
                }
            }
        }

        enum_tuple_match(&book);
        enum_tuple_match(&book2);
        enum_tuple_match(&ebook);
    }

    fn enum_struct() {
        #[derive(Debug)]
        enum Book {
            Papery { index: u32 },
            Electronic { url: String },
        }
        let book = Book::Papery { index: 1001 };
        let ebook = Book::Electronic {
            url: String::from("url ..."),
        };
        println!("{} {:?}", "Enum:Struct:", book);
        println!("{} {:?}", "Enum:Struct:", ebook);
        fn enum_struct_match(b: &Book) {
            match b {
                Book::Papery { index } => {
                    println!("{} {:?}", "Enum:Struct:Match:", index);
                }
                Book::Electronic { url } => {
                    println!("{} {:?}", "Enum:Struct:Match:", url);
                }
            }
        }

        enum_struct_match(&book);
        enum_struct_match(&ebook);
    }

    fn enum_match() {
        enum Book {
            Papery(u32),
            Electronic { url: String },
        }
        let book = Book::Papery(1001);
        let ebook = Book::Electronic {
            url: String::from("url .. .."),
        };

        fn enum_match(b: &Book) {
            match b {
                Book::Papery(i) => {
                    println!("Enum:Match: {}", i);
                }
                Book::Electronic { url } => {
                    println!("Enum:Match: {}", url);
                }
            }
        }
        enum_match(&book);
        enum_match(&ebook);
    }

    fn non_enum_match() {
        let t = "abc";
        match t {
            "abc" => println!("Yes"),
            _ => {}
        }
    }

    enum_basic();
    enum_tuple();
    enum_struct();
    enum_match();
    non_enum_match();

    // TODO: Option
}
