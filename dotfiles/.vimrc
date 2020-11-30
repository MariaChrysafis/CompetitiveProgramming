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
"coloring scheme"
colo desert
syntax on
"running easily"
set autowrite 
nnoremap <C-c> :!g++ -std=c++11 % -Wall -g -o %.out && ./%.out<CR>
"copy pasting"
map <c-m> <esc> :%y+<CR>
"stuff"
autocmd filetype cpp nnoremap <C-c> :w <bar> !clear && g++ -std=gnu++14 -O2 % -o %:p:h/%:t:r.exe && ./%:r.exe<CR>

autocmd filetype c nnoremap <C-c> :w <bar> !gcc -std=c99 -lm % -o %:p:h/%:t:r.out && ./%:r.out<CR>

autocmd filetype java nnoremap <C-c> :w <bar> !javac % && java -enableassertions %:p <CR>
autocmd filetype python nnoremap <C-c> :w <bar> !python % <CR>
autocmd filetype perl nnoremap <C-c> :w <bar> !perl % <CR>
autocmd filetype go nnoremap <C-c> :w <bar> !go build % && ./%:p <CR>
map <F5>:echo 'Current time is ' . strftime('%c')<CR>
syntax on
"set t_Co=256"
"colorscheme onehalflight"
let g:airline_theme='onehalfdark'
" lightline
" let g:lightline = { 'colorscheme': 'onehalfdark' }
set mouse+=a

