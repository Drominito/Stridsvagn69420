# Void Linux
This guide is about Void Linux for the Raspberry Pi 4.
I'm tired of Raspberry Pi OS being Debian and thus every package being 69 years old and Void is a very good Linux distro for the RPi.
It has official support for the Raspberry Pi 4, is very leight weight and boots fast, plus packages are actually up to date.

## Goals
My Raspberry Pi serves as a little home server and these goals will probably be extended soon:
* Save/move everything from the old installation over to Void
* Install the base system onto the Pi
* Install Nginx as a proxy and enable TLS
* Host Gitea locally
* Host the special webserver I made for the actual website
* Install MariaDB and host it via Nginx with TLS on the LAN
* Configure OpenSSH to only allow public key authentication and enable X11 forwarding
* Install Pi-Hole in Docker/AdGuard Home
* Download SDKs for Rust, Zig, Go, C, C++ and Dart/Flutter
* Download more untils

# Installing the base system onto the Pi
## Formatting the microSD card
I went with this partitioning for my 128 GB microSD card. (Note that I also use GPT for the partition table)
| Device         | Directory | Size                       | Type  | Usage          |
| -------------- | --------- | -------------------------- | ----- | -------------- |
| /dev/mmcblk0p1 | /boot     | 1 GB (1024 MB)             | FAT32 | Boot Partition |
| /dev/mmcblk0p2 | [SWAP]    | 1.5 GB (1536 MB)           | SWAP  | Swap Partition |
| /dev/mmcblk0p3 | /         | 125.5 GB (everything else) | BtrFS | Root Partition |

1. Get your microSD card's name, mostly `/dev/mmcblk0`.
2. Create the partitions with `cfdisk <yourdrive>`.
3. Make sure the partitions are now there with `lsblk`.
4. Create the filesystems:
```sh
mkfs.fat -F32 /dev/mmcblk0p1
mkswap /dev/mmcblk0p2
mkfs.btrfs -L "Void Linux" /dev/mmcblk0p3
```

## Mount the microSD card
Since this will be a tarball install, we'll have to mount the SD card. This is on Linux, so you'll have to use a VM and USB passthrough for this guide if you're on Windows, the same probably goes for macOS too.
```sh
mount /dev/mmcblk0p3 /mnt        # Mounts the main partition
mkdir /mnt/boot
mount /dev/mmcblk0p1 /mnt/boot   # Mounts the boot partition
```

## Write Void Linux to the microSD card
This installation seems pretty fast, and it is! You could install it via chroot with XBPS (given you're already on Void - you also need QEMU if you don't run on aarch64 already) or a rootfs install (similar to chroot with XBPS, but it doesn't have to be Void, though you still need QEMU), but I went with the platformfs method for this guide, because it's pretty straight forward.  
Note that you should directly update the system as soon as you boot into it. My tarball had the timecode `20210930`, so it's from 30.09.2021 - that's almost a year ago!

Anyway, just download the `rootfs tarball` for the `rpi4` and run this command:
```sh
tar xvfp "<filename>.tar.xz" -C /mnt
```

## Configure fstab
You'll have to add the boot and root partitions to `/etc/fstab`. I went with the UUID as the identifier. You can get the partitons' IDs with `lsblk -o NAME,SIZE,TYPE,MOUNTPOINTS,FSTYPE,UUID`.
```fstab
# <file system> <dir>   <type>  <options>               <dump>  <pass>
tmpfs           /tmp    tmpfs   defaults,nosuid,nodev   0       0

# Void Linux microSD
UUID=CE73-E51A                            /boot vfat  defaults 0 2
UUID=b9f46a29-2b46-465b-b10f-581ce5dfc96f /     brtfs defaults 0 1
```

<hr>

This is essentially the entire base installation, nothing special really. Now insert the microSD card into your Raspberry Pi 4 and boot it up!
```sh
umount -R /mnt
```

# Post-install configuration
WIP.
