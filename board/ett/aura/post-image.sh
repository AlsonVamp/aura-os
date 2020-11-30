#!/bin/sh

GENIMAGE_CFG="$(dirname $0)/genimage.cfg"
GENIMAGE_TMP="${BUILD_DIR}/genimage.tmp"

rm -rf "${GENIMAGE_TMP}"

# generate sdcard.img with /aura-data contents within data.ext4 partition
genimage \
  --rootpath "${BR2_EXTERNAL_AURA_PATH}/aura-data" \
  --tmppath "${GENIMAGE_TMP}" \
  --inputpath "${BINARIES_DIR}" \
  --outputpath "${BINARIES_DIR}" \
  --config "${GENIMAGE_CFG}"

