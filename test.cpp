autocmd ColorScheme * highlight! Normal ctermbg=NONE guibg=NONE

set nocompatible              " be iMproved, required
filetype off                  " required
set pythonthreehome=/path/to/Library/Frameworks/Python.framework/Versions/3.X
set pythonthreedll=/path/to/Library/Frameworks/Python.framework/Versions/3.X/lib/libpython3.Xm.dylib
" set the runtime path to include Vundle and initialize
set rtp+=~/.vim/bundle/Vundle.vim
call vundle#begin()
" alternatively, pass a path where Vundle should install plugins
"call vundle#begin('~/some/path/here')

" let Vundle manage Vundle, required
Plugin 'VundleVim/Vundle.vim' 
Plugin 'vim-airline/vim-airline'

call vundle#end()            " required
filetype plugin indent on    " required
colorscheme desert

filetype off
autocmd BufNewFile,BufRead *.cpp set formatprg=astyle\ -T4pb

augroup templates
  au!
  " Check Directory for template files
  autocmd BufNewFile *.* silent! execute '0r ~/.vim/templates/skeleton.'.expand("<afile>:e")
augroup END
set nocompatible              " be iMproved, required
filetype off                  " required
set nowrap
set softtabstop=2
set shiftwidth=2
set tabstop=2
set expandtab
set smarttab
set autoindent
set cindent
set number
filetype indent off
"auto-indentation"
autocmd FileType c,cpp,slang set cindent
"key mapping such that the brackets produce another pair"
inoremap {      {}<Left>
inoremap {<CR>  {<CR>}<Esc>O
inoremap {{     {
inoremap {}     {}
syntax on
set autowrite 
nnoremap <C-c> :!g++ -std=c++11 % -Wall -g -o %.out && ./%.out<CR>
map <c-m> <esc> :%y+<CR>
"autocmd filetype cpp nnoremap <C-c> :w <bar> !clear && g++ -std=gnu++14 -O2 % -o %:p:h/%:t:r.exe && ./%:r.exe<CR>

autocmd filetype c nnoremap <C-c> :w <bar> !gcc -std=c99 -lm % -o %:p:h/%:t:r.out && ./%:r.out<CR>

autocmd filetype java nnoremap <C-c> :w <bar> !javac % && java -enableassertions %:p <CR>
autocmd filetype python nnoremap <C-c> :w <bar> !python % <CR>
autocmd filetype perl nnoremap <C-c> :w <bar> !perl % <CR>
autocmd filetype go nnoremap <C-c> :w <bar> !go build % && ./%:p <CR>
map <F5>:echo 'Current time is ' . strftime('%c')<CR>
set mouse+=a
