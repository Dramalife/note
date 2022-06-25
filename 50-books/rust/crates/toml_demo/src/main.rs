use std;
use toml;
use serde_derive::Deserialize;


#[derive(Deserialize)]
struct Config {
    package: Package
}
#[derive(Deserialize)]
struct Package {
    name: String,
    version: String,
    edition: String,
}
fn main() {
    let content = std::fs::read_to_string("Cargo.toml").unwrap();
    let config: Config = toml::from_str(content.as_str()).unwrap();

    println!("  name:{}", config.package.name);
    println!("  version:{}", config.package.version);
    println!("  edition:{}", config.package.edition);

    println!("Hello, world!");
}
