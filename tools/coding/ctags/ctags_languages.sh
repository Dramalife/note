#! /bin/bash
#
# note "ctags" related file
# Copyright (C) 2019 Dramalife@live.com
# 
# This file is part of [note](https://github.com/Dramalife/note.git)
# 
# note is distributed in the hope that it will be useful, but
# WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
#
# bash --version
# GNU bash, version 4.4.20(1)-release (x86_64-pc-linux-gnu)
# Copyright (C) 2016 Free Software Foundation, Inc.
# License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>
# 
# This is free software; you are free to change and redistribute it.
# There is NO WARRANTY, to the extent permitted by law.
# ;
#
# Init : 2019.10.04;
# Update :
#



# 1. SHOW
# --list-maps[=language|all]
#          Lists the file extensions and file name patterns which associate a file name with a language for either the specified language or all languages,
#	   and then exits. See the --langmap option, and SOURCE FILES, above.

ctags --list-maps
# Ant      *.build.xml
# Asm      *.asm *.ASM *.s *.S *.A51 *.29[kK] *.[68][68][kKsSxX] *.[xX][68][68]
# Asp      *.asp *.asa
# Awk      *.awk *.gawk *.mawk
# Basic    *.bas *.bi *.bb *.pb
# BETA     *.bet
# C        *.c
# C++      *.c++ *.cc *.cp *.cpp *.cxx *.h *.h++ *.hh *.hp *.hpp *.hxx *.C *.H
# C#       *.cs
# Cobol    *.cbl *.cob *.CBL *.COB
# DosBatch *.bat *.cmd
# Eiffel   *.e
# Erlang   *.erl *.ERL *.hrl *.HRL
# Flex     *.as *.mxml
# Fortran  *.f *.for *.ftn *.f77 *.f90 *.f95 *.F *.FOR *.FTN *.F77 *.F90 *.F95
# HTML     *.htm *.html
# Java     *.java
# JavaScript *.js
# Lisp     *.cl *.clisp *.el *.l *.lisp *.lsp
# Lua      *.lua
# Make     *.mak *.mk [Mm]akefile GNUmakefile
# MatLab   *.m
# OCaml    *.ml *.mli
# Pascal   *.p *.pas
# Perl     *.pl *.pm *.plx *.perl
# PHP      *.php *.php3 *.phtml
# Python   *.py *.pyx *.pxd *.pxi *.scons
# REXX     *.cmd *.rexx *.rx
# Ruby     *.rb *.ruby
# Scheme   *.SCM *.SM *.sch *.scheme *.scm *.sm
# Sh       *.sh *.SH *.bsh *.bash *.ksh *.zsh
# SLang    *.sl
# SML      *.sml *.sig
# SQL      *.sql
# Tcl      *.tcl *.tk *.wish *.itcl
# Tex      *.tex
# Vera     *.vr *.vri *.vrh
# Verilog  *.v
# VHDL     *.vhdl *.vhd
# Vim      *.vim
# YACC     *.y


# 2. SET


# 3. SAMPLE
# 3.1 Tell it that file end with "*.cpp" is in type of c++
ctags --langmap=c++:+.cpp -R

# 3.2 Scan specific type(s)
# OLD:
#_ # pri kind tag                file
#_ 1 F   v    audit_get_session  bindings/swig/python/audit.py
#_ 		audit_get_session = _audit.audit_get_session
#_ 2 F   f    audit_get_session  bindings/swig/python/audit.py
#_ 		def audit_get_session():
#_ 3 F   v    audit_get_session  bindings/swig/python3/audit.py
#_ 		audit_get_session = _audit.audit_get_session
#_ 4 F   f    audit_get_session  bindings/swig/python3/audit.py
#_ 		def audit_get_session() -> "uint32_t":
#_ 5 F   f    audit_get_session  lib/libaudit.c
#_ 		uint32_t audit_get_session(void)
#_ Type number and <Enter> (empty cancels):
# NEW:  
#_ # pri kind tag                file
#_ 1 F   f    audit_get_session  lib/libaudit.c
#_              uint32_t audit_get_session(void)
#_ Type number and <Enter> (empty cancels):
ctags --languages=c -R

