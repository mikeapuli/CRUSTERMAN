#!/bin/sh
# SPDX-License-Identifier: GPL-3.0-only
# Build the AMB-1 host simulator (the whole app on this machine) into build/host/amb_host.
# Same sources as the firmware, -ffp-contract=off like the device (no fused multiply-add).
set -e
cd "$(dirname "$0")/.."
CC="${CC:-cc} -D_GNU_SOURCE"          # (Linux hides clock_gettime and friends under -std=c99)
mkdir -p build/gen build/host
[ -f build/gen/felucca_font.h ] || python3 tools/gen_font.py build/gen/felucca_font.h >/dev/null
python3 tools/gen_words.py firmware/words.tsv web/words build/gen/ann_words.h >/dev/null
# (CRUSTERMAN) AMB_HOST_DEFS=-DEN_REF_PIECES AMB_HOST_OUT=build/host/amb_host_ref: the simulator with NACHTFAHRT's
# recipes, for the scenarios written against them (tests/run_tests.sh)
OUTB="${AMB_HOST_OUT:-build/host/amb_host}"
$CC -O2 -ffp-contract=off -std=c99 -Wall -Wextra -Wno-unused-function -Wno-unused-parameter \
    -DEN_HOST ${AMB_HOST_DEFS:-} -Ifirmware/src -Ifirmware/src/dsp -Ibuild/gen -o "$OUTB" host/amb_host.c \
    firmware/src/dsp/amb.c -lm
echo "host: $OUTB"
