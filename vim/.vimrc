"关闭vi兼容模式
set nocp
"文件类型检测
filetype plugin indent on 
"显示行标
set nu

"没有源码
set tags+=~/.vim/mytags/stl_tags
"源码位置 /opt/p2p_server/branches/matrix/server/framecommon/src/
"	/opt/p2p_server/branches/matrix/server/srvframe/src/
set tags+=~/.vim/mytags/frame_srv_tags
"源码位置 /usr/local/gmock-1.7.0/gtest/src/ 
"	/usr/local/gmock-1.7.0/src
set tags+=~/.vim/mytags/gtest_gmock_tags
"源码位置 /usr/include/
set tags+=~/.vim/mytags/usr_include_tags
set tags+=./tags
set tags+=/usr/local/gmock-1.7.0/gtest/src/tags
set tags+=/usr/local/gmock-1.7.0/src/tags

"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
" NERDTree
"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
map <silent> <F7> :NERDTreeToggle<cr> 


"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
" Tag list (ctags)
"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
"let Tlist_Ctags_Cmd = '/usr/local/bin/ctags'
let Tlist_Show_One_File = 1            "不同时显示多个文件的tag，只显示当前文件的
let Tlist_Exit_OnlyWindow = 1          "如果taglist窗口是最后一个窗口，则退出vim
let Tlist_Use_Right_Window = 1         "在右侧窗口中显示taglist窗口 
map <silent> <F8> :TlistToggle<cr> 


"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
" cscope setting
"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
if has("cscope")
	set csprg=/usr/bin/cscope
	set csto=1
	set cst
	set nocsverb
	" add any database in current directory
	if filereadable("cscope.out")
		cs add cscope.out
	endif
	set csverb
endif

nmap <C-@>s :cs find s <C-R>=expand("<cword>")<CR><CR>
nmap <C-@>g :cs find g <C-R>=expand("<cword>")<CR><CR>
nmap <C-@>c :cs find c <C-R>=expand("<cword>")<CR><CR>
nmap <C-@>t :cs find t <C-R>=expand("<cword>")<CR><CR>
nmap <C-@>e :cs find e <C-R>=expand("<cword>")<CR><CR>
nmap <C-@>f :cs find f <C-R>=expand("<cfile>")<CR><CR>
nmap <C-@>i :cs find i ^<C-R>=expand("<cfile>")<CR>$<CR>
nmap <C-@>d :cs find d <C-R>=expand("<cword>")<CR><CR>


"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
" omini setting
"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
"关闭omin提示预览窗口
set completeopt=longest,menu 

let OmniCpp_MayCompleteDot=1    "打开  . 操作符
let OmniCpp_MayCompleteArrow=1  "打开 -> 操作符
let OmniCpp_MayCompleteScope=1  "打开 :: 操作符
let OmniCpp_NamespaceSearch=2   "search namespaces in the current buffer and in included files
let OmniCpp_DisplayMode = 1
let OmniCpp_GlobalScopeSearch=1  
let OmniCpp_DefaultNamespaces=["std", "MYFRAMECOMMON", "testing"]  
let OmniCpp_ShowPrototypeInAbbr=1  "打开显示函数原型
let OmniCpp_SelectFirstItem = 2    "自动弹出时自动跳至第一个


inoremap <expr> <CR>       pumvisible()?"\<C-Y>":"\<CR>"
inoremap <expr> <C-F>      pumvisible()?"\<PageDown>\<C-N>\<C-P>":"\<C-X><C-O>"
inoremap <expr> <C-B>      pumvisible()?"\<PageUp>\<C-P>\<C-N>":"\<C-B>"
inoremap <expr> <C-U>      pumvisible()?"\<C-E>":"\<C-U>" 



"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
" supertab setting
"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
"let g:SuperTabRetainCompletionType = 2
"let g:SuperTabDefaultCompletionType = "<C-X><C-O>" 


"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
" Winmanager setting
"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
let g:NERDTree_title="[NERDTree]"
let g:winManagerWindowLayout="NERDTree|TagList"  
function! NERDTree_Start()  
	exec 'NERDTree'  
endfunction  ]
function! NERDTree_IsValid()  
	return 1  
endfunction  
nmap wm :WMToggle<CR>  





"Set mapleader
let mapleader = ","
nmap <silent> <leader>t :NERDTreeToggle<cr> 
"ctags -R --c++-kinds=+p --fields=+iaS --extra=+q .
"ctags -R --c++-kinds=+p --fields=+iaS --extra=+q framecommon/
"ctags -Ra --c++-kinds=+p --fields=+iaS --extra=+q srvframe/
