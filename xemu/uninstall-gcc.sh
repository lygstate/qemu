PACKAGE_LSIT=`pacman -Q -q | grep mingw`
echo $PACKAGE_LSIT
pacman -R $PACKAGE_LSIT

# Then remove mingw64, and recover it from zip file