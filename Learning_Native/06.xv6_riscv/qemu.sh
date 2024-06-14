#!/bin/bash
qemu-system-riscv64 -machine virt -bios none -kernel kernel/kernel -m 128M -smp 4 -global virtio-mmio.force-legacy=false -drive file=filesystem/fs.img,if=none,format=raw,id=x0 -device virtio-blk-device,drive=x0,bus=virtio-mmio-bus.0 -nographic