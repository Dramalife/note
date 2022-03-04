pub fn string_dl() {
    let s = String::from("broadcast");

    //let part1 = &s[0..5];
    let part1 = &s[..5];

    //let part2 = &s[5..9];
    let part2 = &s[5..];

    let part_all = &s[..];

    println!("{} = {} + {}", part_all, part1, part2);
}

/*
* str: String Slice
* String:
* String -> &str */
pub fn convert_string_to_refstr() {
    let s1 = String::from("hello");
    let s2 = &s1[..];
    println!("Slice: String({}), &str({})", s1, s2);
}

pub fn array_dl() {
    let arr = [1, 2, 3, 4, 5];
    let part = &arr[..3];
    for i in part.iter() {
        println!("Slice:Array: {}", i);
    }
}
