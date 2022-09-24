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
