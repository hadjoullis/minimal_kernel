# minimal kernel
- writing from scratch a very simple kernel for 32bit x86 architecture
- following [The little book about OS development](https://littleosbook.github.io/book.pdf)

## BUILDING
Install dependencies:
- grub-legacy 0.97
- bochs 3.0.0
- cdrtools
- nasm

Run:
```
make && make run
```

## notes:
- configure script for bochs taken from [OSdev wiki](https://wiki.osdev.org/Bochs):
    ./configure --enable-smp \
        --enable-cpu-level=6 \
        --enable-all-optimizations \
        --enable-x86-64 \
        --enable-pci \
        --enable-vmx \
        --enable-debugger \
        --enable-debugger-gui \
        --enable-logging \
        --enable-fpu \
        --enable-3dnow \
        --enable-sb16=dummy \
        --enable-cdrom \
        --enable-x86-debugger \
        --enable-iodebug \
        --disable-plugins \
        --disable-docbook \
        --with-x --with-x11 --with-term --with-sdl2
