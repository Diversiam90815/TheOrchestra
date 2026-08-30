# The Orchestra
[![CI](https://github.com/Diversiam90815/TheInstrumentsOfTheOrchestra/actions/workflows/ci.yml/badge.svg?branch=master)](https://github.com/Diversiam90815/TheInstrumentsOfTheOrchestra/actions/workflows/ci.yml)
[![Static Analysis](https://github.com/Diversiam90815/TheInstrumentsOfTheOrchestra/actions/workflows/static-analysis.yml/badge.svg?branch=master)](https://github.com/Diversiam90815/TheInstrumentsOfTheOrchestra/actions/workflows/static-analysis.yml)
[![Release](https://github.com/Diversiam90815/TheInstrumentsOfTheOrchestra/actions/workflows/release.yml/badge.svg)](https://github.com/Diversiam90815/TheInstrumentsOfTheOrchestra/actions/workflows/release.yml)
[![License: MIT](https://img.shields.io/badge/License-MIT-blue.svg)](LICENSE)
[![C++20](https://img.shields.io/badge/C%2B%2B-20-blue.svg)](https://en.cppreference.com/w/cpp/20)
[![JUCE 8](https://img.shields.io/badge/JUCE-8.0.3-8DC63F.svg)](https://juce.com)

**The Orchestra** is a C++20 / JUCE desktop application for studying the instruments of the symphony
orchestra. Pick a family, pick an instrument, and see its range on a real staff, its registers coloured
along a piano roll, the techniques it supports, the roles it typically plays, and the repertoire it is known for,
then play it back from the sampler with your MIDI keyboard.


## Showcase

### Image Preview
<img src="Examples/Example_French_Horn.png" alt="Instrument detail view" width="640">

### Demo Video
![](Examples/Example_Showcase_2.0.gif)


## Features

### Instrument catalogue
- JSON-driven data for 22 instruments across Woodwinds, Brass, Strings and Percussion
- Family-level playing techniques with per-instrument overrides
- Per instrument: written and sounding ranges, registers with timbral descriptions, orchestration roles,
  signature works, supported clefs
- Deterministic 3-digit lookup key encoding family and instrument (e.g. `301` = Violin)

### Notation
- Staves drawn programmatically from a SMuFL font (Bravura)
- Treble, bass, alto and tenor clefs, with automatic selection of whichever keeps a note closest to the staff
- Ledger lines, and automatic `8va` / `8vb` / `15ma` / `15mb` escalation for extreme notes
- Written-vs-sounding toggle for transposing instruments, with the transposition named (`in Bb`, `in F`, …)

### Audio & MIDI
- JUCE `AudioProcessor` + `AudioProcessorEditor` architecture, hosted by a standalone shell
- Multi-sampled playback with round-robin and velocity layers, per articulation
- On-screen piano roll with registers colour-coded across the keys and the playable span highlighted
- All available MIDI inputs enumerated and enabled at startup
- MIDI CC sliders that both send and reflect controller state


## Architecture

```
┌─────────────────┐   ┌──────────────────┐
│  OrchestraApp   │   │  OrchestraPlugin │  Standalone shell / VST3 plugin
└────────┬────────┘   └────────┬─────────┘
         │                     │
         └──────────┬──────────┘
              ┌──────▼──────┐
              │ OrchestraUI │  JUCE components, design tokens, notation rendering
              └──────┬──────┘
                     │
              ┌──────▼──────┐
              │OrchestraCore│  Domain model, sampler, file & config management
              └─────────────┘
```

**`OrchestraCore`** owns the domain: the instrument catalogue, the sampler, path and config resolution, and logging.

**`OrchestraUI`** talks to the domain through exactly one seam: `CoreManager`. Panels expose `std::function` callbacks and the editor wires them up. That keeps every panel independently constructible and testable.

**`OrchestraApp`** is a thin `Main.cpp`: it creates the processor and editor, opens the audio device and routes MIDI.

**`OrchestraPlugin`** builds the same processor/editor as a VST3 instrument (`TheOrchestraPlugin`).


## Building

### Prerequisites

- CMake 4.0+
- A C++20 compiler
- Python 3.10+ (for the build script)

Dependencies (JUCE 8.0.3, nlohmann/json, GoogleTest and the logger) are fetched automatically by
[CPM](https://github.com/cpm-cmake/CPM.cmake) into `libs/cpm-cache` on first configure.

### Platform support

Developed and tested on **Windows** with MSVC. The CMake now guards its MSVC-only compiler flags and all
filesystem paths resolve through JUCE's cross-platform APIs.

### Quick start

```bash
python build.py -b
```

The first run also downloads the sample pack (~395MB, one-time - see [Samples](#samples)) before
configuring, builds the standalone app and the VST3 plugin, and installs both into `install/`.

Or drive CMake directly:

```bash
cmake -S . -B build -G Ninja && cmake --build build && ctest --test-dir build --output-on-failure
```

### Build script arguments

| Argument | Short | Description | Default |
|---------|--------|-------------|---------|
| `--prepare` | `-p` | Generate CMake build files only (no build). | `False` |
| `--build` | `-b` | Generate, build, then run the test suite. | `False` |
| `--platform` | `-pl` | CMake generator (`Ninja`, `VS2022`, `VS2026`). | `Ninja` |
| `--architecture` | `-a` | Target architecture (`x64`, `ARM64`). | `x64` |
| `--configuration` | `-c` | Build configuration (`Debug`, `RelWithDebInfo`, `Release`). | `Release` |
| `--runtest` | `-t` | Run the test suite against an existing build. | `False` |

Examples:

```bash
python build.py -b -pl VS2022 -c Debug
```

```bash
python build.py -t -c Debug
```

Build output lands in `build/<architecture>/`, e.g. `build/x64/`. `-b` runs `cmake --install`
automatically afterwards, so `install/` ends up with everything needed to try the project out:

```
install/
  bin/TheOrchestraApp.exe        Standalone app (+ its Assets/Images)
  lib/VST3/The Orchestra.vst3    VST3 instrument plugin - point your DAW's VST3 folder at this
  lib/TheOrchestraCore.lib       Orchestra static libraries
  lib/TheOrchestraUI.lib
```

### Optional tooling

All off by default, so a fresh clone configures without any of them installed:

| Option | Effect |
|--------|--------|
| `-DENABLE_FORMAT=ON` | Run clang-format over the sources before each build |
| `-DENABLE_CPPCHECK=ON` | Run cppcheck static analysis on the C++ targets |
| `-DENABLE_DOXYGEN=ON` | Add a Doxygen documentation target |
| `-DENABLE_MEMCHECK=ON` | Add a memcheck target |


## Tests

GoogleTest, discovered by CTest, split by the library under test:

- **`OrchestraCore.Tests`**: instrument parsing and lookup, range and register modelling, sampler voice
  and sound behaviour, sample-file management, file/path resolution, and `CoreManager` integration.
- **`OrchestraUI.Tests`**: the UI logic that needs no window: `GridFlow`'s column and row arithmetic, and
  `NotationGeometry`'s staff placement, ottava escalation and transposition naming.

```bash
ctest --test-dir build/x64 -C Debug --output-on-failure
```


## Samples

The sample pack is published as four per-family zip assets (`Brass.zip`, `Percussion.zip`, `Strings.zip`,
`Woodwinds.zip`) on a GitHub Release, and
`python build.py -b` (or `-p`) fetches it automatically via `scripts/fetch_samples.py`, extracting it into
a single shared AppData location:

- Windows: `%ProgramData%\TheOrchestra\Assets\Samples` (falls back to `%APPDATA%\...` if that isn't
  writable)

This one location is what the standalone app, the VST3 plugin, and the test suite all read from. The download is cached under
`libs/samples-cache/` and skipped on subsequent builds once already up to date.

To fetch (or re-fetch) samples without a full build:

```bash
python scripts/fetch_samples.py
```

You can still point the app at a different sample folder from the settings control on the family
switcher; the choice is persisted.


## Repository layout

```
Assets/               Instrument JSON, fonts, images
cmake/                Build modules (options, build info, tooling integrations)
scripts/              Python build helpers used by build.py + other scripts
src/
  OrchestraCore/      Domain model, sampler, file & config management
  OrchestraUI/        Components, theme, notation rendering
  OrchestraApp/       Standalone application shell
  OrchestraPlugin/    VST3 instrument plugin
tests/                GoogleTest suites
```


## License

MIT — see [LICENSE](LICENSE).
