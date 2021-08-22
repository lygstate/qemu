#!/bin/bash
MSYSTEM_LOWER="${MSYSTEM,,}"
echo $MSYSTEM_LOWER
ninja install
if [ ! -d "${XEMU_DEV_DIR}/xemu-dist/$MSYSTEM_LOWER" ]
then
  exit -1
fi

cd ${XEMU_DEV_DIR}/xemu-dist/$MSYSTEM_LOWER
rm *.dll

rm -rf qemu*
rm -rf QEMU*
rm -rf applications
rm -rf icons
dependList=$( ldd xemu-core-system-ppc | awk -v prefix="/$MSYSTEM_LOWER" '{if (match($3,prefix)){ print $3}}' )
echo $dependList
cp -ap $dependList .

dependList=$( ldd xemu-core-system-ppc64 | awk -v prefix="/$MSYSTEM_LOWER" '{if (match($3,prefix)){ print $3}}' )
echo $dependList
cp -ap $dependList .

dependList=$( ldd xemu-core-system-arm | awk -v prefix="/$MSYSTEM_LOWER" '{if (match($3,prefix)){ print $3}}' )
echo $dependList
cp -ap $dependList .

dependList=$( ldd xemu-core-system-aarch64 | awk -v prefix="/$MSYSTEM_LOWER" '{if (match($3,prefix)){ print $3}}' )
echo $dependList
cp -ap $dependList .
