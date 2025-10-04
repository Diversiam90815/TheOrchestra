## Overview

TheOrchestra is a C++20 / JUCE-based orchestral playback and exploration environment.  
It focuses on:  
- Managing structured instrument metadata (range, transposition, techniques, roles, famous works) loaded from JSON  
- Real-time MIDI + audio processing (standalone app and plugin-style architecture)  
- Sample-driven playback (sampler voices + instrument selection)  
- Fast, structured logging (fmt-backed)  
- Comprehensive automated tests (GoogleTest) for core musical domain logic

The project is in active development and aims to become a lightweight orchestral study / sketching tool and foundation for more advanced articulation and performance modeling.


## Features

### Instrument Data & Metadata
- JSON-driven instrument catalog (Woodwinds, Brass, Strings, Percussion)
- Family -> instrument technique inheritance with instrument-level overrides
- Rich descriptors:  
  - Playing techniques  
  - Qualities / timbral zones  
  - Transposition (including octave transposers)  
  - Displayed vs actual range (e.g. percussion, harp)  
  - Famous works & usage roles
- Deterministic lookup by numeric key (e.g. 301 = Violin) with caching

### Audio & MIDI Engine
- JUCE `AudioProcessor` + `AudioProcessorEditor` architecture
- Automatic enumeration & enabling of all available MIDI inputs on startup
- Sample playback via custom sampler classes (tested)
- Real-time safe routing through `AudioDeviceManager` and `AudioProcessorPlayer`

### Robust Testing
- GoogleTest suite covering:
  - JSON load integrity & presence of all expected instruments
  - Technique inheritance and override logic
  - Transposition semantics (octave / interval / non-transposing)
  - Range formatting consistency
  - Sampler integration & voice behavior
  - File management (paths, asset resolution)

### Logging & Diagnostics
- Central logging abstraction using `{fmt}` formatting
- Startup build info (branch, commit, timestamp)
- Structured device enablement traces

### Code Quality & Structure
- C++20 (concepts-ready codebase)
- Separation of concerns:
  - Core domain (instrument, sampler, helper utilities)
  - App/UI layer (standalone window)
  - Tests
- Vendor / third-party dependencies vendored under `_deps`



## Technology Stack

| Layer            | Technologies |
|------------------|-------------|
| Core / Engine    | C++20, JUCE modules |
| UI / Windowing   | JUCE (`DocumentWindow`, custom editor) |
| Audio / MIDI     | JUCE audio & MIDI services |
| Logging          | fmt (via embedded logger) |
| Build System     | CMake |
| Testing          | GoogleTest |
| JSON / Data      | JUCE `var` / `DynamicObject` parsing |
| Tooling (optional) | Clang-Format, CppCheck, Doxygen |


## Build the project

### Cloning the Repository

Clone the repository including:

```bash
git clone git@github.com:Diversiam90815/TheOrchestra.git
```

### Prepare the Build Environment

Before building the project, you need to generate the necessary build files using CMake. This can be done using the `build.py` script with the `--prepare` or `-p` option. The target build configuration can be adjusted in the build.py file: Currently it is set to build a Visual Studio 2022 project.

```bash
cd TheOrchestra
python build.py -p
```

For a **Debug** build, add the `--debug` or `-d` option:

```bash
python build.py -pd
```

### Build the Project

To build the project, use the `--build` or `-b` option:

```bash
python build.py -b
```

This will compile the project using the build files generated during the preparation step.

- **Release Build**: By default, the build is configured for a Release build.
- **Debug Build**: To build the project in Debug mode, include the `--debug` or `-d` option:

  ```bash
  python build.py -bd
  ```

**Important**: You do not need to run the `--prepare` step separately, the script will automatically prepare the build environment before building.


### Running the Plugin

After a successful build, the application can be found in the build output directory. Currently, the app is set to build standalone executable binary. They can be found within the respective folder.


## Showcase

### Image Preview
<img src="Examples/Example_French_Horn.png" alt="Orchestral Overview" width="640" height="360">

### Demo Video
![](Examples/Example_Showcase_2.0.gif)


## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.