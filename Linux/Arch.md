# Before you begin:
* `$` means you can (and should) run it as a normal user, while `#` means you need to run it as root, either via `sudo` or by logging in as root. 
* Get yourself an [Arch Linux Live Install ISO](https://archlinux.org/download/) and flash it onto a USB drive, preferably one with USB 3.0 and better.
* Disable Secure Boot for the installation process and then go into the Boot Menu and select your USB drive. For me it's F1 for the BIOS and F12 for the Boot Menu.
* Make sure your target drive uses GPT instead of MBR. You can do all of this via Rufus if you're on Windows.

<hr>

# Moving files
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
| Device    | Directory | Size            | Usage            | Type  | Mountpoint (Arch Install) |
| ------    | --------- | --------------- | ---------------- | ----- | ------------------------- |
| /dev/sdX1 | /boot/efi | `1G` (1GB)      | EFI-Boot         | FAT32 | /mnt/boot/efi             |
| /dev/sdX2 | [SWAP]    | `6G` (6GB)      | Swap-Partition   | Swap  | [SWAP]                    |
| /dev/sdX3 | /home     | `100G` (100GB)  | Home-Partition   | BtrFS | /mnt/home                 |
| /dev/sdX4 | /         | `393G` (393GB)¹ | System-Partition | Ext4  | /mnt                      |

¹: Everything left, since <Amount>GB labeled drives have actually always a bit less than <Amount>.

1. Get your Target Drive's name (/dev/sdX): `# lsblk`
2. Create Partitions like above: `# cfdisk /dev/sdX`
3. Check if partitions are written: `# lsblk`
4. Create filesystems:
```
# mkfs.fat -F32 /dev/sdX1
# mkswap /dev/sdX2
# mkfs.brtfs -L "Home" /dev/sdX3
# mkfs.ext4 -L "Arch Linux" /dev/sdX4
```

<hr>

# Extending the install
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
* `golang`: Go SDK
* `rustup`: Rustup to install the Rust SDK with rustc and cargo
* `nodejs`: Node.js
* `npm`: Node Package Manager
* `yarn`: Yarn Package Manager
* `discord`: Discord Client
* `steam`: Steam Client
* `gcc`: GNU Compiler Collection/GNU C Compiler
* `clang`: Clang LLVM Compiler
* `neofetch`: I use Arch, btw.
* `tealdeer`: TLDR but faster, working offline and written in Rust.
* `rsync`: File transfer and backing up the system.
* `code`: Visual Studio Code (Open-Source/no-Microsoft build) aka. Code - OSS
* `dotnet-core`: Latest .NET Core with SDK and Runtime (Built from source)
* `lolcat`: R a i n b o w
* `cmatrix`: Many hack, so Matrix, very cyber.
* `arp-scan`: ARP Scan
* `nmap`: NMAP Scan
* `wget`: Basically just a terminal downloader
* `htop`: Terminal Task Manager
* `btop`: The Cooler Terminal Task Manager

## Other packages (Yay)
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
