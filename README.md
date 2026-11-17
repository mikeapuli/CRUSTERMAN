# CRUSTERMAN for the M-VAVE FM-1

CRUSTERMAN is a fork of [NACHTFAHRT](https://github.com/FartyPants/fm1-nachtfahrt) by Cranky Man, the generative
Berlin School firmware for the M-VAVE FM-1. It is made to be played **next to** NACHTFAHRT: one FM-1 runs
NACHTFAHRT, a second runs CRUSTERMAN, and piece N here is written as the other half of piece N there.

It changes two things and leaves the rest of NACHTFAHRT as it is (engine, voices, effects, pages):

1. **Ten different pieces**, each a companion to NACHTFAHRT's piece in the same slot.
2. **Four ways to play the form by hand** that NACHTFAHRT doesn't have.

NACHTFAHRT's own README is kept in [docs/NACHTFAHRT-README.md](docs/NACHTFAHRT-README.md) and its manual in
[docs/MANUAL.md](docs/MANUAL.md); everything there still applies unless this page says otherwise.

## The pieces

Each is named after the NACHTFAHRT piece it goes with, with a K in front: KTimewind goes with Timewind, and so on.

Same root as the NACHTFAHRT piece, the same scale or a subset of it, so the two units stay in key while each walks
its own chords. Opposite role, register and voice. All between 60 and 74 BPM, with slow attacks and sparse notes, so
they sit against a second unit with no clock between the two.

| # | Piece | Key, tempo | |
|---|---|---|---|
| 1 | KTimewind | D minor, 72 | Strings, glass lines of 13 and 11 an octave up, a flute. No wind |
| 2 | KWahnfried | B♭ Dorian, 60 | The pulse under the strings: plucked lines of 8 and 5, low; the Lead waits |
| 3 | KPhaedra | D minor, 74 | A horn drone whose filter is the movement, a few high bells, a low theremin, surf |
| 4 | KRubycon | F minor, 72 | Vibes of 5 and glass of 9 an octave up, a thin glass drone, a high flute |
| 5 | KStratosfear | E minor, 69 | A Moog line of 6 two octaves down, dark saws; the Lead waits |
| 6 | KSunrain | D major pentatonic, 65 | Marimbas of 7 and 5 with hardly an echo, a quiet organ, a reed |
| 7 | KMirage | F♯ minor pentatonic, 63 | A low dark organ, an electric piano an octave down, a low Mini, tape |
| 8 | KCyborg | C Phrygian, 70 | A low pulse of 5 and a pluck of 7, a long echo; the Lead (a choir) waits |
| 9 | KSakura Rain | B♭ Dorian, 60 | Sakura Rain's eight chords, looping, on glass; a flute that waits; drops |
| 10 | KUmeda | F♯ major pentatonic, 60 | Water, a slow string pad, a few glass notes; a soft theremin that waits |

The recipes are in `firmware/src/dsp/amb.c` (`PC_KTIMEWIND` and on). They were set by
measurement in the simulator, not by ear on two units: expect to tune levels and tempos on the hardware.

## What it adds

| | How | What it does |
|---|---|---|
| **Wait** | The Arc page (GLO twice), KNOB 1, Lead in: one step past Off | The Lead plays nothing of its own. Play three notes or more on the white keys and pause: it answers, and goes on growing ideas out of your figure for 45 to 150 seconds (the Memory knob), then is silent till you play again. KWahnfried, KStratosfear, KCyborg, KSakura Rain and KUmeda start this way |
| **Conduct** | Hold EDIT, press a white key | The chord goes to that step of the scale at once (the first white key is home). For following the other unit by ear: it changes chord, one key puts this unit on the same one. With Drift at Hold the chord stays until your next key. Press the key within about a second of holding EDIT: EDIT held alone for 1.5 s still makes new chords, as in NACHTFAHRT |
| **Section** | PERFORM (tap SEL), black keys 6 to 9 | Emerge, Flow, Solo, Bridge: the arc goes there now. The four are lit; the section playing blinks. Emerge restarts the arc (the intros close and open again) |
| **Downbeat** | PERFORM (tap SEL), black key 10 | The bar starts from its top now, both sequences from their first step. Tap it on the other unit's downbeat to put the two in phase without a clock. Does nothing under an external MIDI clock |

Saves from NACHTFAHRT are not read (the pieces are different): CRUSTERMAN starts from its own recipes.

## Build and install

The repository builds itself on GitHub: **Actions → build → Run workflow**. The firmware package is attached to the
finished run as the artifact `crusterman-firmware` (a zip with `amb.fwsc` in it).

Install it from a computer with the FM-1 on USB (needs Python 3 and `pip3 install mido python-rtmidi`):

```
python3 tools/fm1_install.py amb.fwsc
```

Installing firmware is at your own risk. Going back to stock firmware and recovery are described in
[BUILDING.md](BUILDING.md). To build locally instead, see the same file.

Tests: `sh tests/run_tests.sh`. The engine's own tests run against NACHTFAHRT's recipes (kept for the tests only, built
with `-DEN_REF_PIECES`), which shows the engine's sound is unchanged; `tests/crusterman/` covers the pieces and the
four additions.

## Changes from NACHTFAHRT (2026-11-17)

- `firmware/src/dsp/amb.c`, `amb.h`: the ten recipes replaced; Lead in's Wait; `en_goto_section`, `en_downbeat`,
  `en_chord_deg`; no piece has a written theme.
- `firmware/src/app/ui.c`: EDIT held with a white key; PERFORM's black keys 6 to 10; the name on the screens.
- `firmware/src/app/app.h`: the saved project's magic.
- `tests/`, `host/build_host.sh`, `.github/workflows/build.yml`, this README.

## Credits and licence

GPL-3.0-only, as NACHTFAHRT. NACHTFAHRT is by Cranky Man; it is a fork of
[DUB-1](https://github.com/sbegueria/fm1-dub), itself a fork of [AMB-1](https://github.com/charlesvestal/fm1-amb) by
Charles Vestal, on the Felucca platform by Leo Kuroshita. See [LICENSING.md](LICENSING.md) for every component.
CRUSTERMAN is not connected with any of them, nor with the artists NACHTFAHRT's pieces are named after.
