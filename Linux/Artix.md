# Artix Linux
This guide is about Artix Linux, an Arch-based distro without systemd, and installing it on a USB 3.0 Drive.
The key difference is that it's supposed to use less I/O to keep the flash storage healthy and not block anything else.  

## Goals
I want to use this as a light Linux install for troubleshooting and development on the go:
* Artix Linux with OpenRC
* btrfs for the main file system (only FAT32 for UEFI-Boot, no Swap)
* Installing SDDM, LXQt and awesome and theming it
* Configuring XOrg, ALSA and Pipewire and XTerm
* Configuring Neovim as a terminal IDE
* Code-OSS and language SDKs for development as well as Git
* Brave as a privacy-friendly browser
* eatmydata to not screw with the USB drive
* tmpfs for everything that is unneccesary

# Installing the base system
Boot into the Artix Base ISO that you want to use. Set your timezone and keyboard layout, then proceed to boot into the Live ISO.  
Either login as root or login as artix, but then remember to use sudo for the system commands.

## Formatting the disk
All computers that I know have UEFI enabled so there's no need for me to support legacy BIOS. This is the table I went with for my 128GB USB drive:
| Mountpoint | Filesystem    | Label   | Size   | Usage          |
| ---------- | ------------- | ------- | ------ | -------------- |
| `/boot`    | fat (FAT32)   | `BOOT`  | 500M   | Boot Partition |
| `/`        | btrfs (Btrfs) | `Artix` | 127.5G | Main Partition |

1. Get your target drive's name with `lsblk`. Look for the drive that seems like the one you want to use. Make sure it's a GPT one.
2. Partition your disk like above with `cfdisk /dev/yourdrive`. If it asks for a partition table, go with `gpt`.
3. Format the partitions:
```sh
mkfs.fat -F 32 /dev/yourdrive1
fatlabel /dev/yourdrive1 BOOT
mkfs.btrfs -L Artix /dev/yourdrive2
```
4. Mount the drive on `/mnt`:
```
mount /dev/disk/by-label/Artix /mnt
mkdir /mnt/boot
mount /dev/disk/by-label/BOOT /mnt/boot
```
