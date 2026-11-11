# TB Automatic Double Tracker (2026 Mac)

TB Automatic Double Tracker for current Macs: **CLAP, VST3 and AU**, universal (Apple
Silicon and Intel), **macOS 11 and later**. Use it in Reaper, FL Studio, Logic,
GarageBand, Tape16 and other hosts.

![panel](https://raw.githubusercontent.com/tonybuzzcock/TB-Automatic-Double-Tracker-2026-MAC/gui-preview/panel_showcase.png)

The sound and panel are the same as the Mac OS X 10.8.5 VST build
([TB-Automatic-Double-Tracker-Mountain-Lion](https://github.com/tonybuzzcock/TB-Automatic-Double-Tracker-Mountain-Lion)).
The DSP code is the same, and the test suite checks that the plugin's output matches it
sample for sample. It's a model of the Bell Electrolabs A.D.T. (Automatic Double
Tracker), built from Krystal's trace of the schematic (`Docs/`). Personal,
non-commercial use.

## Install

GitHub → Actions → latest run → Artifacts → `TB-Automatic-Double-Tracker-mac`, unzip,
then follow `INSTALL.txt`. In short:

- `TB Automatic Double Tracker.vst3` → `VST3/`
- `TB Automatic Double Tracker.component` → `Components/`
- `TB Automatic Double Tracker.clap` → `CLAP/`

These folders are in `/Library/Audio/Plug-Ins/` (the main Library) or
`~/Library/Audio/Plug-Ins/` (your user Library). Use whichever one your other plugins
are in. Apple hasn't notarised the plugins, so run the short Terminal lines in
`INSTALL.txt` for the folder you used. They clear macOS's download tags and re-sign the
plugins on your Mac. Then rescan plugins in your DAW.

## Controls

| Name | Control | Range |
|------|---------|-------|
| Gain | the input stage's gain | +0.0 to +40.1 dB |
| Mix | direct to the double | 0 – 10 |
| Mod | modulation speed | 0 – 10 (about 0.7 Hz at noon, 35 Hz fully clockwise) |
| Dev | modulation depth | 0 – 10 (0 = none) |
| Delay | the BBD clock | 9.6 – 213 ms (30 ms at noon) |
| ADT In/Out | the button: the double in, or out | In / Out |
| Input | *plugin only*: level into the unit (1.0 = 1 V) | ±12 dB |
| Output | *plugin only*: output trim | ±24 dB |

Defaults: Gain 0, Mix 5, Mod 6, Dev 3, Delay 5, ADT in. In stereo, each side runs
through its own copy of the circuit with the same settings; a mono source is processed
once.

## The panel

1040 × 392, laid out like the unit: a mustard knob panel with GAIN, MIX, MOD, DEV and
DELAY (red tops on black knurled skirts, tick scales without numbers, as on the unit),
then the LEVEL light and the ADT in / out button, which glows red with the double in.
The LEVEL light comes on when the double is driven hard (the unit's level indicator).
The strip along the bottom has the TB electronic logo, Input, Output, presets and the
readout.

Drag a knob up or down to turn it (hold Shift for fine control). Double-click a knob
to reset it, or use the scroll wheel. Click the button to switch the double in or out.

**Presets:** click SAVE, then a slot 1–8. Click a saved slot to recall it. The presets
are shared by all three formats, in
`~/Library/Application Support/TB/TB Automatic Double Tracker/Presets.txt`.

## What's modelled

The input gain stage, an NE571 compressor with pre-emphasis, Sallen-Key filters, the
MN3005 bucket brigade clocked by a 4046 VCO, the same filters again, and the NE571
expander with de-emphasis; MIX between the direct signal and the double. The
modulation oscillator (a 741 relaxation oscillator into C37 and DEV) is simulated from
its parts. 4x oversampled. See the Mountain Lion repo's README for the estimates (the
4046's frequency law, the MN3005's gain and clipping, the NE571 level) and the readings
of the trace.

## How it's built

The plugin is written once as a CLAP (`Source/Plugin`).
[clap-wrapper](https://github.com/free-audio/clap-wrapper) v0.17.0 builds the VST3 and
AU from that same code. The SDKs are downloaded at configure time:

    cmake -B build -DCMAKE_BUILD_TYPE=Release
    cmake --build build --config Release

GitHub Actions builds universal binaries and fails unless every plugin has both
architectures and a macOS 11.0 minimum. It ad-hoc signs the plugins, then:

- runs the DSP, preset and CLAP host tests (native and the other architecture)
- opens the panel offscreen through the CLAP GUI extension and drives its controls
- validates with auval (`aufx TBad TBel`), clap-validator and pluginval
- publishes panel screenshots to the `gui-preview` branch

A Linux job builds the CLAP and runs the same tests.
