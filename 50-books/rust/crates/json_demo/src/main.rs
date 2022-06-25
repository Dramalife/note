use json;
//use std::fs;
fn main() {
    //let content = fs::read_to_string("./1.json").unwrap();
    let content = String::from(r#"{"project":{"inc":1024,"src":4096}}"#);
    let parse = json::parse(content.as_str()).unwrap();
    println!("  {}", parse["project"]);
    println!("  {}", parse["project"][0]);
    println!("  {}", parse["project"]["src"]);

    println!("Hello, world!");
}
