mod command_line;
mod comments;
mod enum_dl;
mod error_handle;
mod file_io;
mod function;
mod loop_dl;
mod ownership;
mod project_management;
mod slice;
mod struct_tuple;

fn main() {
    println!("Hello, world!");

    /*
     * Project Management
     */
    project_management::module_dl::sample1_dl::func1_dl();

    use project_management::module_dl::sample1_dl::func1_dl;
    func1_dl();

    use project_management::module_dl::sample1_dl::func1_dl as pm_m_s_func1_dl;
    pm_m_s_func1_dl();

    /*
     * Print To Command Line
     */
    command_line::command_line();
    command_line::print_to_cmdline::print_var();

    /*
     * Function
     */
    use function::example::arg_int as func_arg_int;
    use function::example::body_exp as func_body_exp;
    /*  Arg & Ret; */
    println!("ret={}", func_arg_int(77, 88));
    /*  Function Body */
    println!("func body exp: {}", func_body_exp());

    /*
     * Loop
     */
    println!("Loop");
    loop_dl::func_loop();

    /*
     * Ownership
     */
    use ownership::ownership::func as ososfunc;
    ososfunc::sample_basic();
    ososfunc::funcall_arg();
    ososfunc::funcall_ret();
    ownership::ownership::ref_b::func_ref_borrow();

    /*
     * Slice
     */
    slice::string_dl();
    slice::convert_string_to_refstr();
    slice::array_dl();

    /*
     * Struce
     */
    struct_tuple::struct_dl();
    struct_tuple::tuple_struct();
    struct_tuple::ownership_of_struct();

    /*
     * File & IO
     */
    file_io::command_line::get_args();
    file_io::command_line::read_line();
    file_io::file_io::read_file();
    file_io::file_io::write_file();

    /*
     * Enum
     */
    enum_dl::enum_dl();

    /*
     * Error Handle
     */
    error_handle::error_handle();
}
