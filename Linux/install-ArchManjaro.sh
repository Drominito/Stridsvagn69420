#!/bin/sh
echo 'NOTE: This install script is personalized. It might not work on your machine properly or cause damage!'
sleep 6
clear

echo '[Updating System...]'
sudo pacman -Syy
sudo pacman -Syu

#---INSTALLATION---
#Essentials
echo '[Installing Essentials...]'
sudo pacman -S git neofetch lolcat toilet nmap arp-scan nodejs python openssh cmatrix

#GUI Apps
echo '[Installing GUI-Apps...]'
sudo pacman -S chromium vlc thunderbird code steam discord krita

#.NET Core
echo '[Installing .NET Core...]'
sudo pacman -S dotnet-sdk dotnet-runtime

#QEMU
echo '[Installing QEMU...]'
sudo pacman -S qemu qemu-arch-extra qemu-block-gluster qemu-block-iscsi qemu-block-rbd samba

#Snap
echo '[Installing Snap...]'
sudo pacman -S snapd
sudo systemctl enable --now snapd.socket
sudo ln -s /var/lib/snapd/snap /snap

#Spotify
echo '[Installing Snap-Store packages...]'
sudo snap install spotify
sudo snap install powershell --classic

#---END---
echo '[Installation done!]'
neofetch
echo '//////////////////////////////////////////////////////////'
echo 'You should restart your system, after that:'
echo 'You should check the config of: neofetch, samba, chromium, discord, steam, ssh, spotify, git'