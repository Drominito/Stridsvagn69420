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

## Set up Wifi
This step is only neccesary if you're using a wireless computer for the installation.

## Enabling Network Time Protocol
The Network Time Protocol aka. NTP automatically syncronized your computer's real-time clock. Enable it with:
```sh
rc-service ntpd start
```

## Install the base system on the drive
1. Since we already mounted the drive, we can just run the `basestrap` command.
```sh
basestrap /mnt base base-devel openrc elogind-openrc linux linux-firmware git ssh
```
2. Then create the fstab file that will mount all the partitions when the systems boots:
```sh
fstabgen -U /mnt >> /mnt/etc/fstab
```

<hr>

**Now, you'll have to chroot into the drive:**
```sh
artix-chroot /mnt
```

## Configure time
Set your timezone with the Region/City scheme, e.g. Europe/Berlin:
```sh
ln -sf /usr/share/zoneinfo/Europe/Berlin /etc/localtime
```

Sync the hardware clock with the system's clock (Note that this is in UTC):
```sh
hwclock --systohc
```

## Configure localization
1. Install a text editor, e.g. `nano` or `vim`/`neovim`:
```sh
pacman -S nano vim
```

2. Then edit /etc/locale.gen and uncomment the languages you want to use, e.g. `de_DE.UTF-8`:
```sh
nano /etc/locale.gen
```

3. Generate the desired locales:
```sh
locale-gen
```

4. Set the locale system-wide by editing `/etc/locale.conf`:
```
LANG=de_DE.UTF-8
LANGUAGE=de_DE:en_US      
LC_TIME=de_DE.UTF-8
LC_MONETARY=de_DE.UTF-8
LC_NUMERIC=de_DE.UTF-8
LC_CTYPE=de_DE.UTF-8
LC_MESSAGES=de_DE.UTF-8
LC_PAPER=de_DE.UTF-8
LC_MEASUREMENT=de_DE.UTF-8
LC_NAME=de_DE.UTF-8
LC_ADDRESS=de_DE.UTF-8
LC_TELEPHONE=de_DE.UTF-8
LC_IDENTIFICATION=de_DE.UTF-8
LC_ALL=
```

5. Set the keyboard layout system-wide by editing `/etc/vconsole.conf`:
```
FONT_MAP=8859-1_to_uni
FONT=lat1-16
KEYMAP=de-latin1
```
6. Modify `/etc/conf.d/keymaps`:
```
keymap="de"
fix_euro="yes"
```

## Configuring the Boot Loader
1. Install the required packages (`os-prober` is optional) as well as your CPU's microcode (`amd-ucode` or `intel-ucode`):
```sh
pacman -S grub efibootmgr os-prober amd-ucode intel-ucode
```

2. Install GRUB for UEFI systems:
```sh
grub-install --target=x86_64-efi --efi-directory=/boot --bootloader-id=grub
```

3. Create the GRUB config:
```sh
grub-mkconfig -o /boot/grub/grub.cfg
```

## Adding your user account:
1. Set the root password with `passwd`

2. Create your new user:
```sh
useradd -m artix
```

3. Set your account's password:
```sh
passwd artix
```

4. Add account to wheel group:
```sh
usermod -aG wheel artix
```

5. Edit sudoers and enable the wheel group:
```sh
EDITOR=nano visudo
```

## Network configuration
1. Set the system's hostname:
```sh
echo "MyHostname" > /etc/hostname
```

2. Configure the `/etc/hosts` file like this:
```
127.0.0.1        localhost
::1              localhost
127.0.1.1        MyHostname.localdomain  MyHostname
```

3. Edit `/etc/conf.d/hostname` like this:
```
hostname='MyHostname'
```

4. Install NetworkManager and the OpenRC Service:
```sh
pacman -S networkmanager networkmanager-openrc
rc-update add NetworkManager default
```

<hr>

**Your base install is now finished!**  
Just exit the chroot, unmount the drive at /mnt and reboot:
```sh
exit
umount -R /mnt
reboot
```
