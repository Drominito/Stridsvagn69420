#!/bin/sh
echo '[Updating Snap packages...]'
sudo snap refresh
echo '[Updating Pacman packages...]'
sudo pacman -Syu
echo '[Updating done!]'