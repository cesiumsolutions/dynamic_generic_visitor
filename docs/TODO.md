# Dyynamic Generic Visitor TODO List

- Make Visitable able to distinguish between Reference and Value types.
  - Especially when loading a value from Plugin, Boost.DLL closes the library
    when it goes out of scope making the currently referenced value invalid.
