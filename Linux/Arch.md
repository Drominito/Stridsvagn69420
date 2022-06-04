# Before you begin:
* `$` means you can (and should) run it as a normal user, while `#` means you need to run it as root, either via `sudo` or by logging in as root. 

<hr>

# Installing Arch Linux
This is only for a base Install of Arch Linux, the very lightest.


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
