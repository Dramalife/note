#### 0 Contents
[TOC]


#### 1 Reference
[The Cargo Book](https://doc.rust-lang.org/cargo/index.html)
[Install Rust](https://www.rust-lang.org/zh-CN/tools/install)
[crates.io](crates.io)



#### 2 Common

##### Tools
|Tool |Description |
|--|--|
|Rustup| Rust安装器和版本管理工具|
|Cargo| Rust 构建工具和包管理器|

##### Files
|File |Description |
|--|--|
|Cargo.lock| 记录本地所用依赖库的精确版本|
|Cargo.toml| |

##### Install

```bash
# RUSTUP_HOME
# CARGO_HOME
curl --proto '=https' --tlsv1.2 -sSf https://sh.rustup.rs | sh

## Select 
# 1) Proceed with installation (default)
# 2) Customize installation
# 3) Cancel installation

source ~/.bashrc
```

##### Uninstall
```bash
rustup self uninstall
```

##### Mirror
```bash

```

##### Project, Build & Exec
```bash
# Cargo.toml 为 Rust 的清单文件。其中包含了项目的元数据和依赖库。
# src/main.rs 为编写应用代码的地方。
cargo new hello-rust

cargo run
```

##### Dependents
```
# crates.io

vi Cargo.toml
#+ [dependencies]
#+ ferris-says = "0.2"

```



#### 3 Editor

##### 3.1 VIM

```
https://github.com/rust-lang/rust.vim
```
