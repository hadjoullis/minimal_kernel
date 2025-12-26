## notes:
- build bochs taken from [OSdev wiki](https://wiki.osdev.org/Bochs):
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
