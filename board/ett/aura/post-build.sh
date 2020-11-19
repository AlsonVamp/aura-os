#!/bin/sh

BOARD_DIR="$(dirname $0)"
cp $BOARD_DIR/uEnv.txt $BINARIES_DIR/uEnv.txt


# Create image
DATA_SIZE=500M
DATA_IMAGE="${BINARIES_DIR}/data.ext4"
dd if=/dev/zero of=${DATA_IMAGE} bs=${DATA_SIZE} count=1
mkfs.ext4 -L "aura-data" -E lazy_itable_init=0,lazy_journal_init=0 -O ^extent,^64bit "$DATA_IMAGE"

# Copy user files
AURA_DATA="${BR2_EXTERNAL_AURA_PATH}/aura-data"
mkdir -p ${BINARIES_DIR}/temp
sudo mount -o loop ${DATA_IMAGE} ${BINARIES_DIR}/temp
cp -r ${AURA_DATA} ${BINARIES_DIR}/temp
sudo umount ${BINARIES_DIR}/temp
rm -rf ${BINARIES_DIR}/temp
