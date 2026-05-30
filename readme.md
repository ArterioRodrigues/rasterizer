The SDL library can be easily installed with

```sh
brew install SDL2
```

But you will need to let the LSP know where that file exist which can be done
by creating a `compile_flags.txt` and adding the path to the libary

```sh
sdl2-config --cflags
-I/opt/homebrew/include/SDL2 -D_THREAD_SAFE

touch compile_flags.txt 

-I/opt/homebrew/include/SDL2 -D_THREAD_SAFE > compile_flags
```


