# Arch Linux
Before you begin with [installing Arch Linux](#installing-arch-linux)
* Get yourself an [Arch Linux Live Install ISO](https://archlinux.org/download/) and flash it onto a USB drive, preferably one with USB 3.0 and better.
* Disable Secure Boot for the installation process and then go into the Boot Menu and select your USB drive. For me it's F1 for the BIOS and F12 for the Boot Menu.
* Make sure your target drive uses GPT instead of MBR. You can do all of this via Rufus if you're on Windows.

## Moving files
Files/configs that you can/should copy so that you can use them on your Arch Linux, btw.
* `~/.gitignore`: Your Git config
* `~/.zshrc`: Your ZSH config
* `~/.ssh/`: Your SSH directory containing your config and private keys
* `~/.config/`: Your local config directory
* Pass GPG-Key: [Extracting a private GPG Key](#extracting-a-private-gpg-key)
* Git Signing GPG-Key: [Extracting a private GPG Key](#extracting-a-private-gpg-key)

## Extracting a private GPG Key
1. List all available private keys:
```
$ gpg --list-secret-keys --keyid-format=long
```
2. Copy the key ID:
```
sec   rsa4096/<ID> YYYY-MM-DD [SC]
      <KEY-ID>
uid                 [<Level>] <Name> <<Email>>
ssb   rsa4096/<SUB-ID> YYYY-MM-DD [E]
```
4. Extract the private key:
```
$ gpg --armor --export-secret-keys <KEY-ID> > private.key
```

<hr>

# Installing Arch Linux
This is only for a base Install of Arch Linux, the very lightest. You should've already booted into the Arch Linux Live USB.

## Prepare the environment
1. Select your proper keymap:
```
root@archiso# loadkeys de-latin1
```
3. Connect to a Wi-Fi network if you're not connected via Ethernet:
```
root@archiso# iwctl
[iwd]# station wlan0 get-networks
[iwd]# station wlan0 connect <SSID>
[iwd]# //enter passphrase
[iwd]# station wlan0 show
[iwd]# exit
```
3. Snyc the system time using NTP:
```
root@archiso# timedatectl set-ntp true
root@archiso# timedatectl status
```

## Format Target Drive
This is the "partition table" that I went with for my My Passport Go with 500GB:
| Device    | Directory | Size                 | Usage            | Type  | Mountpoint (Arch Install) |
| ------    | --------- | -------------------- | ---------------- | ----- | ------------------------- |
| /dev/sdX1 | /boot     | `500MB` (500 MB)     | EFI-Boot         | FAT32 | /mnt/boot/efi             |
| /dev/sdX2 | [SWAP]    | `6G` (6GB)           | Swap-Partition   | Swap  | [SWAP]                    |
| /dev/sdX3 | /home     | `120G` (120GB)       | Home-Partition   | BtrFS | /mnt/home                 |
| /dev/sdX4 | /         | `372.5G` (372.5GB)¹  | System-Partition | Ext4  | /mnt                      |

¹: Everything left, since <Amount>GB labeled drives have actually always a bit less than <Amount>.

1. Get your Target Drive's name (/dev/sdX): `# lsblk`
2. Create Partitions like above: `# cfdisk /dev/sdX`
3. Check if partitions are written: `# lsblk`
4. Create filesystems:
```sh
mkfs.fat -F32 /dev/sdX1
mkswap /dev/sdX2
mkfs.brtfs -L "Home" /dev/sdX3
mkfs.ext4 -L "Arch Linux" /dev/sdX4
```

## Installing the system on the target drive
1. Mount the target drive according to its mountpoints:
```sh
mount /dev/sdX4 /mnt

mkdir /mnt/boot
mkdir /mnt/boot/efi
mount /dev/sdX1 /mnt/boot

mkdir /mnt/home
mount /dev/sdX3 /mnt/home
```

2. Pacstrap Arch onto the target drive:
```sh
pacstrap /mnt base linux linux-firmware base-devel nano btrfs-progs
```

## Configuring the system
1. Create the fstab file for your drive:
```sh
genfstab -U /mnt >> /mnt/etc/fstab
```
2. Change root into your target drive:
```sh
arch-chroot /mnt
```
3. Set your timezone and sync hardware clock:
```
ln -sf /usr/share/zoneinfo/Europe/Berlin /etc/localtime
hwclock --systohc
```
4. Edit `/etc/locale.gen` and uncomment your lanuages, e.g. `en_US.UTF-8` and `de_DE.UTF-8`
5. Run `locale-gen` to generate your languages
6. Edit `/etc/locale.conf`:
```sh
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
7. Set your keymap in `/etc/vconsole.conf`:
```
KEYMAP=de-latin1
```
8. Set your hostname in `/etc/hostname`:
```
iusearchbtw
```
9. Modify `/etc/hosts`:
```
127.0.0.1   localhost
::1         localhost
127.0.1.1   iusearchbtw.localdomain iusearchbtw
```
10. Install packages that you want, e.g.:
```sh
pacman -S zsh dash man-db man-pages tealdeer git zsh-completions bash-completion gcc which xz gzip
```
11. Set the root user's password with `passwd`. Remember it!

## Install GRUB Bootloader
0. Install your CPU's microcode, either `amd-ucode` or `intel-ucode` or both:
```
pacman -S amd-ucode intel-ucode
```
1. Download required packages:
```sh
pacman -S grub efibootmgr
```
2. Install GRUB:
```sh
grub-install --target=x86_64-efi --bootloader=GRUB --efi-directory=/boot/efi --removable
```
3. Create GRUB-Config:
```sh
grub-mkconfig -o /boot/grub/grub.cfg
```
4. Set `GRUB_GFXMODE` in `/etc/default/grub` from `auto` to your screen resolution, e.g. `1920x1080`.
5. Regenerate the GRUB-Config: `grub-mkconfig -o /boot/grub/grub.cfg`

## Get a Network Management Software and restart
1. Install NetworkManager:
```sh
pacman -S networkmanager
systemctl enable NetworkManager
```
2. Exit, unmount and shutdown:
```
exit
umount -R /mnt
shutdown -h now
```

## Post-install configuration
Login as root with the given passwort.
1. Add a user for yourself:
```sh
useradd -m <User> -s /bin/zsh
```
2. Add your user to Sudoers/wheel:
```sh
usermod -aG wheel <User>
```
3. Set your password:
```sh
passwd <User>
```
4. Enable wheel group by uncommenting `wheel  ALL=(ALL) ALL`:
```sh
EDITOR=nano visudo
```
5. Symlink dash to `/bin/sh`:
```sh
ln -sf /bin/dash /bin/sh
```

The install is now complete! Just reboot, then login as your user and update the system:
```
# pacman -Syu
```

<hr>

# Extending the install
## Oh-My-Zsh and Powerlevel10k
Make sure you're using FiraCode or other compatible fonts in your teminal emulator.
1. Install Oh-My-Zsh
```sh
sh -c "$(curl -fsSL https://raw.github.com/robbyrussell/oh-my-zsh/master/tools/install.sh)"
```
2. Get Powerlevel10k
```sh
git clone https://github.com/romkatv/powerlevel10k.git $ZSH_CUSTOM/themes/powerlevel10k
```
3. Edit your `.zshrc`:
```sh
ZSH_THEME="powerlevel10k/powerlevel10k"
```
4. Reload the config:
```
$ source .zshrc
```
5. Configure Powerlevel10k if it doesn't start automatically:
```
$ p10k configure
```
6. Install Plug-Ins:
```sh
git clone https://github.com/zsh-users/zsh-syntax-highlighting.git ${ZSH_CUSTOM:-~/.oh-my-zsh/custom}/plugins/zsh-syntax-highlighting
git clone https://github.com/zsh-users/zsh-autosuggestions ${ZSH_CUSTOM:-~/.oh-my-zsh/custom}/plugins/zsh-autosuggestions
```
7. Enable plugins in `.zshrc`:
```
plugins=(git zsh-syntax-highlighting zsh-autosuggestions)
```

## Graphical UI with KDE and SDDM
How to install KDE and SDDM along with some optional features. (I have it installed, but I didn't write any guide yet ^^')

## awesome as a lightweight WM alongside KDE and SDDM
How to install awesome WM and use it instead of Plasma in SDDM. (Working on this ^^')

## Printing with CUPS
How to setup printing on Arch. I have an Epson WF-2760, so drivers might vary.
1. Install neccesary packages:
```sh
pacman -S cups # Printer Service
pacman -S ghostscript # PostScript interpreter
pacman -S system-config-printer # Printer Config Application
pacman -S gutenprint # Printer driver collection
```

2. Install optional packages:
```sh
pacman -S print-manager # Printer settings for KControl/KDE-Settings
pacman -S samba # If your printer is accessed via SMB, e.g. by printer servers.
pacman -S arp-scan # For detecting LAN devices
```

3. Enable `cups`
You can either enable cups as a always-on background daemon: `# systemctl enable --now cups.service`  
Or you enable the socket, so that it only runs when you want to print: `# systemctl enable cups.socket`

4. Start `system-config-printer`
You can also use "Printer Settings" (or something along this) in your application launcher.

5. Add a new printer.
    * If you know how to connect to your printer, e.g. IPP, LPD or Samba, then go for the corresponding option. Else, go for "finding network printers".  
    * In my case, going by hostname didn't work and my printer has a static IP anyway so I entered it. You can find your printer's IP with `sudo arp-scan -l`.  
    * In my case, again, there we're many options, but there was only one showing the device name, `Epson WF-2760`, which was LPD/LPR. I don't know about other printers but LPD *should* work.

6. Finish the configuration
What the title says. Name, description and location.  
You might want to restart your computer if it can't detect metadata like ink level.

## Importing Pass
1. Install Pass:
```
# pacman -S pass
```
2. Download your Password Database:
```
$ git clone https://github.com/<Username>/<Repo> ~/.password-store
```
3. Import the GPG-Key:
```
$ gpg --import private.key
```


## AUR
1. You need Git installed:
```
# pacman -S --needed git base-devel
```
2. Get [Yay](https://github.com/Jguer/yay):
```
# git clone https://aur.archlinux.org/yay.git /opt/yay
```
3. Get permission for the created directory:
```
# chown -R <username>:wheel /opt/yay
```
5. Go into the directory and build the package:
```
$ cd /opt/yay && makepkg -si
```

## Firewall
1. Install [nftables](https://wiki.archlinux.org/title/Nftables) and [Firewalld](https://wiki.archlinux.org/title/Firewalld):
```
# pacman -S nftables firewalld
```
2. Enable the firewall:
```
# systemctl enable --now firewalld
```
You can graphically configure the firewall later in KDE's settings.

## Fonts
* `adobe-source-code-pro-fonts`: Source Code Pro
* `ttf-jetbrains-mono`: JetBrains Mono
* `ttf-fira-code`: FiraCode
* `ttf-ms-fonts`: (AUR) Microsoft Fonts
* `ttf-vista-fonts`: (AUR) Vista Fonts
* `ttf-fira-sans`: FiraSans (TrueType)
* `otf-fira-sans`: FiraSans (OpenType)
* `ttf-opensans`: Open Sans
* `ttf-google-fonts-git`: (AUR) Huge collection of Google Fonts
* `noto-fonts-cjk`: Noto Fonts for Chinese, Korean and Japanese
* `ttf-hannom`: Vietnamese Chữ Nôm support
* `noto-fonts-emoji`: Noto Fonts for Emojis
* `ttf-twemoji`: (AUR) Twitter Emojis

<hr>

## Other packages (Pacman)
### Programming
* `code`: Visual Studio Code (Open-Source/no-Microsoft build) aka. Code - OSS
* `golang`: Go SDK
* `rustup`: Rustup to install the Rust SDK with rustc and cargo
* `nodejs`: Node.js
* `npm`: Node Package Manager
* `yarn`: Yarn Package Manager
* `gcc`: GNU Compiler Collection/GNU C Compiler
* `clang`: Clang LLVM Compiler
* `dotnet-core`: Latest .NET Core with SDK and Runtime (Built from source)
* `lua`: Lua SDK
* `julia`: Juila SDK
* `kotlin`: Kotlin SDK (Also installs Java)
* `ruby`: Ruby SDK

### Internet
* `steam`: Steam Client
* `discord`: Discord Client
* `ktorrent`: BitTorrent client for KDE

### Utils
* `tealdeer`: tldr but faster, working offline and written in Rust.
* `rsync`: File transfer and backing up the system.
* `arp-scan`: ARP Scan
* `nmap`: NMAP Scan
* `wget`: Basically just a terminal downloader
* `htop`: Terminal Task Manager
* `btop`: The Cooler Terminal Task Manager
* `kwallet`: KWallet Password Wallet

### Fun
* `lolcat`: R a i n b o w
* `neofetch`: I use Arch, btw.
* `cmatrix`: Many hack, so Matrix, very cyber.

## Other packages (Yay)
### Programming
* `visual-studio-code-bin`: Microsoft's build of Visual Studio Code.
* `powershell-bin`: PowerShell (Binary Package)
* `powershell`: PowerShell (Compiled from Source)
* `dotnet-core-bin`: Latest .NET Core with SDK and Runtime (Binary Package)
* `flutter`: Flutter and Dart SDK
* `android-studio`: Android Studio
* `android-sdk`: Android SDK
* `android-sdk-platform-tools`: Android SDK Platform Tools
* `code-icons`: Change Code - OSS icons to VS Code ones
* `code-marketplace`: Enable vscode marketplace in Code OSS

### Internet
* `google-chrome`: Google Chrome
* `ani-cli`: Watch Anime from the command line
* `brave-bin`: Brave Browser (Binary Package) 

# More
If you want to see what else is possible, look at the [repository by pvscvl98](https://github.com/pvscvl98/ArchLinux-Notes) that I used to write this guide.
