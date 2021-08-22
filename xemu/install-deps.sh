#!/bin/bash
MSYSTEM_LOWER="${MSYSTEM,,}"
echo $MSYSTEM_LOWER
ninja install
if [ ! -d "${XEMU_DEV_DIR}/xemu-dist/$MSYSTEM_LOWER" ]
then
  exit -1
fi

cd ${XEMU_DEV_DIR}/xemu-dist/$MSYSTEM_LOWER
rm *.dll || true

NAME_PREFIX=qemu

dependList=$( ldd $NAME_PREFIX-system-ppc | awk -v prefix="/$MSYSTEM_LOWER" '{if (match($3,prefix)){ print $3}}' )
echo $dependList
cp -ap $dependList .

dependList=$( ldd $NAME_PREFIX-system-ppc64 | awk -v prefix="/$MSYSTEM_LOWER" '{if (match($3,prefix)){ print $3}}' )
echo $dependList
cp -ap $dependList .

dependList=$( ldd $NAME_PREFIX-system-arm | awk -v prefix="/$MSYSTEM_LOWER" '{if (match($3,prefix)){ print $3}}' )
echo $dependList
cp -ap $dependList .

dependList=$( ldd $NAME_PREFIX-system-aarch64 | awk -v prefix="/$MSYSTEM_LOWER" '{if (match($3,prefix)){ print $3}}' )
echo $dependList
cp -ap $dependList .

dependList=$( ldd $NAME_PREFIX-system-i386 | awk -v prefix="/$MSYSTEM_LOWER" '{if (match($3,prefix)){ print $3}}' )
echo $dependList
cp -ap $dependList .

dependList=$( ldd $NAME_PREFIX-system-x86_64 | awk -v prefix="/$MSYSTEM_LOWER" '{if (match($3,prefix)){ print $3}}' )
echo $dependList
cp -ap $dependList .
