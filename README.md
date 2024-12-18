```abc
                      #        TM
       $    $  $     $ #     #
       $$   $   $   $   #   #
       $ $  $    $ $     # #
       $  $ $     $       #
       $   $$     $      # #
       $    $     $     #   #
  
  
              Nyx-CNG

Authors: IsmailHamza
```
# Nyx-CNG (*C*urses *N*ew-*G*eneration)
Nyx-CNG is an ever-growing project having related but independent features.

CNG is an acronym for _**C**urses **N**ew-**G**eneration._

The Nyx-CNG has various header files for different features. A breif overview of them is given.

## Nyx-CNG.h
**Headers required:** `iostream`, `Nyx-ANSI`  
**OS compatibility:** `All`  
### Features:
- `gotoyx`
- `Complex boxes`
- `Menu`
- `Menu Bar`

### Features (TBA):
- `List (One)`
- `Select (Multiple)`
- `Toggle Buttons`
- `Labels & Text Inputs`

## Nyx-ANSI.h
**Headers required:** `void`  
**OS compatibility:** `All`  
### Features:
- `Clear Screen/Line/EOL etc`
- `Colouring & Styling`


## Nyx-Mouse.h
**Headers required:** `termios.h`, `unistd.h`  
**OS compatibility:** `LINUX specific`  
### Features:
- `Non canonical Input/Output`
- `Handle Mouse Position/Click/Scroll/SHIFT+ALT+CTRL Modifiers etc`