"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
" basic
"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
"关闭vi兼容模式
set nocp
"显示行标
set nu
"设置编码
set encoding=utf-8 fileencodings=ucs-bom,utf-8,cp936

map <silent> <F9> :set nonu<cr>
map <silent> <F10> :set nu<cr>


"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
" vundle
"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
set nocompatible              " be iMproved, required
filetype off                  " required

set rtp+=~/.vim/bundle/Vundle.vim
call vundle#begin()
Plugin 'gmarik/Vundle.vim'

"提供展示文件/目录列表的功能
Plugin 'The-NERD-tree'
"快速注释代码
Plugin 'The-NERD-Commenter'
"切换.cpp和.h文件
Plugin 'a.vim'
"文件、函数添加注释和说明
Plugin 'c.vim'
"源码的实时检查
Plugin 'Syntastic'

call vundle#end()            " required
filetype plugin indent on    " required


"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
" NERDTree
"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
map <silent> <F7> :NERDTreeToggle<cr>


"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
" Syntastic
"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
"在打开文件的时候检查
let g:syntastic_check_on_open = 1
let g:syntastic_cpp_include_dirs = ['/usr/include/']
let g:syntastic_cpp_remove_include_errors = 1
let g:syntastic_cpp_check_header = 1
let g:syntastic_cpp_compiler = 'clang++'
let g:syntastic_cpp_compiler_options = '-std=c++11 -stdlib=libstdc++'
"set error or warning signs
let g:syntastic_error_symbol = '>>'
let g:syntastic_warning_symbol = '>!'
"whether to show balloons
let g:syntastic_enable_balloons = 1









