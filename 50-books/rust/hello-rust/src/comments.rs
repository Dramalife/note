/*
 * https://www.runoob.com/rust/rust-comments.html
 * */

/*
 * cargo doc
 * ls target/doc/hello_rust
 * */
pub mod comments_dl {
    /// Adds one to the number given.
    ///
    /// # Examples
    ///
    /// ```
    /// let x = add(1, 2);
    ///
    /// ```

    fn add(a: i32, b: i32) -> i32 {
        return a + b;
    }
}
