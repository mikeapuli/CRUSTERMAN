// SPDX-License-Identifier: GPL-3.0-only
// CRUSTERMAN's own recipes (the firmware's, not the reference ones): every value of every piece in its parameter's
// range (a value out of range would make a saved project invalid: project.c), the tempo 60..80 (the set's), the key
// its NACHTFAHRT piece's, and two minutes of each finite, heard and under full scale.
#include <stdio.h>
#include <string.h>
#include "amb.h"

void en_midi_out(uint32_t st, uint32_t d1, uint32_t d2) { (void)st; (void)d1; (void)d2; }

static int32_t buf[512];

int main(void)
{
    static const int ROOT[EN_NPIECES] = {2, 10, 2, 5, 4, 2, 6, 0, 10, 6};   // NACHTFAHRT's: D Bb D F E D F# C Bb F#
    int i, p, fail = 0;
    for (i = 0; i < EN_NPIECES; i++) {
        int16_t pp[P_NPARAMS];
        uint16_t pl;
        int b, j, peak = 0, loud = 0;
        en_init();
        en_piece(i, pp, &pl);
        for (p = 0; p < P_NPARAMS; p++) {
            const en_param_t *q = en_param_info(p);
            if (pp[p] < q->lo || pp[p] > q->hi)
                printf("FAIL %s: %s %d outside %d..%d\n", en_piece_name(i), q->name, pp[p], q->lo, q->hi), fail = 1;
        }
        if (pp[P_TEMPO] < 60 || pp[P_TEMPO] > 80)
            printf("FAIL %s: tempo %d\n", en_piece_name(i), pp[P_TEMPO]), fail = 1;
        if (pp[P_ROOT] != ROOT[i])
            printf("FAIL %s: root %d, not %d\n", en_piece_name(i), pp[P_ROOT], ROOT[i]), fail = 1;
        if (!en_piece_name(i)[0] || strlen(en_piece_name(i)) > 11)
            printf("FAIL piece %d: its name\n", i), fail = 1;
        for (p = 0; p < P_NPARAMS; p++)
            en_set(p, pp[p]);
        en_pool(pl);
        en_piece_theme(i);
        en_regrow();
        en_play(1);
        for (b = 0; b < (int)(120.0f * 44100.0f / 256.0f); b++) {
            en_render(buf, 256, 2048);
            for (j = 0; j < 512; j++) {
                const int v = buf[j] < 0 ? -buf[j] : buf[j];
                if (v > peak)
                    peak = v;
                loud += v > (1 << 23) / 50;
            }
        }
        printf("  %-11s tempo %d, peak %.2f\n", en_piece_name(i), pp[P_TEMPO], (double)((float)peak / 8388608.0f));
        if (peak >= (int)(0.9f * 8388608.0f) || !loud)
            printf("FAIL %s: peak %d, %d samples heard\n", en_piece_name(i), peak, loud), fail = 1;
    }
    printf(fail ? "crust: FAILED\n" : "crust: ok\n");
    return fail;
}
