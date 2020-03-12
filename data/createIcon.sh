#!/bin/bash -x

#if $XDG_CACHE_HOME is empty, use $HOME/.cache
if [ -z "$XDG_CACHE_HOME" ]; then
  echo "XDG_CACHE_HOME is empty, use .cache instead"
  XDG_CACHE_HOME="$HOME/.cache"
fi


#check if properties are inside the png:
convert original.png -set "Thumb::URI" "$XDG_CACHE_HOME/thumbnails/normal/FitTraining.png" 1.png
convert 1.png -set "Thumb::MTime" "0" 2.png 

#$XDG_CACHE_HOME/thumbnails/
mkdir -p $XDG_CACHE_HOME/thumbnails/normal


NAME=$(echo -n "file:///home/gwerners/Desktop/AppImage/data/FitTraining" | md5sum | awk '{print $1}')
NAME_APPIMAGE=$(echo -n "file:///home/gwerners/Desktop/AppImage/FitTraining-x86_64.AppImage" | md5sum | awk '{print $1}')
rm 1.png
cp 2.png $XDG_CACHE_HOME/thumbnails/normal/$NAME.png
mv 2.png $XDG_CACHE_HOME/thumbnails/normal/$NAME_APPIMAGE.png

identify -verbose /home/gwerners/.cache/thumbnails/normal/$NAME.png
