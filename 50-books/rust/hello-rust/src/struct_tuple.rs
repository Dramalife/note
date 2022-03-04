/*
 * https://www.runoob.com/rust/rust-struct.html
 */

#[derive(Debug)]
struct Site {
    domain: String,
    name: String,
    nation: String,
    found: u32,
}

pub fn struct_dl() {
    let domain = String::from("www.runoob.com");
    let name = String::from("NAME");

    let runoob = Site {
        domain,
        name,
        nation: String::from("China"),
        found: 2013,
    };
    println!("Struct:{:#?}", runoob);

    let site = Site {
        domain: String::from("www.xxx.com"),
        ..runoob
    };
    println!("Struct:{:?}", site);
}

pub fn tuple_struct() {
    struct Color(u8, u8, u8);
    struct Point(f64, f64);

    let black = Color(0, 0, 0);
    let origin = Point(1.0, 0.6);

    println!(
        "Struct_Tuple:tuple_struct: black = ({}, {}, {})",
        black.0, black.1, black.2
    );
    println!(
        "Struct_Tuple:tuple_struct: origin = ({}, {})",
        origin.0, origin.1
    );
}

pub fn ownership_of_struct() {
    #[derive(Debug)]
    struct Rectangle {
        width: u32,
        height: u32,
    }

    fn print_struct() {
        let rect1 = Rectangle {
            width: 30,
            height: 50,
        };
        println!("Struct_Tuple:print_struct: {:?}", rect1);
        println!("Struct_Tuple:print_struct: {:#?}", rect1);
    }

    /* The Rust language is not object-oriented, as evidenced by the innovations in its ownership
     * mechanism. But the precious ideas of object orientation can be implemented in Rust. */
    fn method_of_struct() {
        impl Rectangle {
            fn area(&self) -> u32 {
                self.width * self.height
            }
            fn wider_than(&self, rect: &Rectangle) -> bool {
                self.width > rect.width
            }
        }
        let rect2 = Rectangle {
            width: 60,
            height: 80,
        };
        let rect3 = Rectangle {
            width: 20,
            height: 90,
        };
        println!(
            "Struct_Tuple:struct_method: 2 {:?}, area is {}",
            rect2,
            rect2.area()
        );
        println!(
            "Struct_Tuple:struct_method: 3 {:?}, area is {}",
            rect3,
            rect3.area()
        );
        println!(
            "Struct_Tuple:struct_method: 2 wider than 3 ? {}",
            rect2.wider_than(&rect3)
        );
    }

    /* eg. String::from */
    fn func_struct() {
        impl Rectangle {
            fn create(width: u32, height: u32) -> Rectangle {
                Rectangle { width, height }
            }
        }
        let rect = Rectangle::create(30, 50);
        println!("Struct_Tuple:func: {:?}", rect);
    }

    print_struct();
    method_of_struct();
    func_struct();
}
