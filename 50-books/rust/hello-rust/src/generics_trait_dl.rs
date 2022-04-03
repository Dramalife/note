/*
 * https://www.runoob.com/rust/rust-generics.html
 */

fn generic_struct_same_type() {
    #[derive(Debug)]
    struct Point<T> {
        x: T,
        y: T,
    }
    let p1 = Point { x: 1, y: 2 };
    let p2 = Point { x: 1.2, y: 2.1 };
    println!("Generic:Struct:SameType: {:?}", p1);
    println!("Generic:Struct:SameType: {:?}", p2);

    // error[E0308]: mismatched types
    // let p3 = Point {x: 1, y: 2.1};
}
fn generic_struct_diff_type() {
    struct Point<T1, T2> {
        x: T1,
        y: T2,
    }
    let p = Point { x: 1, y: 2.1 };
    println!("Generic:Struct:DiffType: {}, {}", p.x, p.y);
}
fn generic_struct_diff_type_note1() {
    struct ResultDL<T, E> {
        ret: T,
        err: E,
    }
    let ret = ResultDL {
        ret: -1,
        err: "No such file.",
    };
    println!("Generic:Struct:DiffType:Note1: {}, {}", ret.ret, ret.err);
}

fn generic_struct_method() {
    #[derive(Debug)]
    struct Point<T, U> {
        x: T,
        y: U,
    }
    impl<T, U> Point<T, U> {
        fn getx(&self) -> &T {
            &self.x
        }
        fn mixup<A, B>(self, other: Point<A, B>) -> Point<T, B> {
            Point {
                x: self.x,
                y: other.y,
            }
        }
    }
    let p = Point { x: 1, y: 2.1 };
    println!("Generic:Struct:Method:Basic: p.x = {}", p.getx());
    let other = Point { x: 3.3, y: "bbb" };
    println!(
        "Generic:Struct:Method:Generic: p.mixup = {:?}",
        p.mixup(other)
    );
}

fn trait_default_trait() {
    trait Descriptive {
        fn describe(&self) -> String {
            String::from("Trait:DefaultTrait: [Object]")
        }
    }
    struct Person {
        name: String,
        age: u8,
    }
    impl Descriptive for Person {
        fn describe(&self) -> String {
            format!("{} {}", self.name, self.age)
        }
    }
    let cali = Person {
        name: String::from("Cali"),
        age: 24,
    };
    println!("Trait:DefaultTrait: {}", cali.describe());
}
fn trait_as_arg() {
    // TODO
}
fn trait_as_ret() {
    // TODO
}

pub fn generics_trait_main() {
    generic_struct_same_type();
    generic_struct_diff_type();
    generic_struct_diff_type_note1();
    generic_struct_method();

    trait_default_trait();
    trait_as_arg();
    trait_as_ret();
}
