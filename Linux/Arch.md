# Before you begin:
* `$` means you can (and should) run it as a normal user, while `#` means you need to run it as root, either via `sudo` or by logging in as root. 
* Get yourself an [Arch Linux Live Install ISO](https://archlinux.org/download/) and flash it onto a USB drive, preferably one with USB 3.0 and better.
* Disable Secure Boot for the installation process and then go into the Boot Menu and select your USB drive. For me it's F1 for the BIOS and F12 for the Boot Menu.

<hr>

# Installing Arch Linux
This is only for a base Install of Arch Linux, the very lightest. You should've already booted into the Arch Linux Live USB.


<!--End-->

<hr>

# Extending the install
## AUR
1. You need Git installed:
```
# pacman -S git
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
* `rsync`: File transfer and backing up the system.
* `code`: Visual Studio Code (Open-Source/no-Microsoft build)
* `dotnet-core`: Latest .NET Core with SDK and Runtime (Built from source)

## Other packages (Yay)
* `visual-studio-code-bin`: Microsoft's build of Visual Studio Code.
* `powershell-bin`: PowerShell (Binary Package)
* `powershell`: PowerShell (Compiled from Source)
* `dotnet-core-bin`: Latest .NET Core with SDK and Runtime (Binary Package)
