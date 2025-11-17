## Overview

**The Orchestra** is a C++20 / JUCE-based orchestral playback and exploration environment.  
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
  - Ranges & Transposition  
  - Displayed vs actual range (e.g. percussion, harp)  
  - Famous works & usage roles
- Deterministic lookup by numeric key (e.g. 301 = Violin) with caching

### Audio & MIDI Engine
- JUCE `AudioProcessor` + `AudioProcessorEditor` architecture
- Automatic enumeration & enabling of all available MIDI inputs on startup
- Sample playback via custom sampler classes (tested)
- Real-time safe routing through `AudioDeviceManager` and `AudioProcessorPlayer`


## Technology Stack

| Layer            | Technologies |
|------------------|-------------|
| Core / Engine    | C++20, JUCE modules |
| UI / Windowing   | JUCE (`DocumentWindow`, custom editor) |
| Audio / MIDI     | JUCE audio & MIDI services |
| Logging          | fmt (via embedded logger) |
| Build System     | CMake |
| Testing          | GoogleTest |
| Tooling (optional) | Clang-Format, CppCheck, Doxygen |


## Build the project

The project uses a modular Python-based build system located in `build.py`, with supporting modules inside the `scripts/` directory. It handles:

- CMake project generation
- Selecting platform, architecture, and configuration
- Automatic versioning
- Environment detection (Dev / Staging / Prod)
- Building and installing
- Running the C++ GoogleTest suite


### Command-Line Arguments

| Argument | Short | Description | Default |
|---------|--------|-------------|---------|
| `--prepare` | `-p` | Generate CMake build files only (no build). | `False` |
| `--build` | `-b` | Generate and build the project (also runs tests). | `False` |
| `--platform` | `-pl` | Select CMake generator (`VS2022`, `Ninja`, `Xcode`). | `Ninja` |
| `--architecture` | `-a` | Target architecture (`x64`, `ARM64`). | `x64` |
| `--configuration` | `-c` | Build configuration (`Debug`, `RelWithDebInfo`, `Release`). | `Release` |
| `--runtest` | `-t` | Run only the CMake test suite | `False` |



### Build Environment

Generate CMake project files:

```bash
python build.py -p
```

#### Platforms

Select platform with the `--platform` (`-pl`) option:

```bash
python build.py -b -pl VS2022
python build.py -b -pl XCode
python build.py -b -pl Ninja
```
Default: Ninja

#### Build Configurations

Select configuration with the `--configuration` (`-c`) option:

```bash
python build.py -b -c Debug
python build.py -b -c RelWithDebInfo
python build.py -b -c Release
```
Default: Release

#### Build Architecture

Select configuration with the `--architecture` (`-a`) option:

```bash
python build.py -b -c x64
python build.py -b -c ARM64
```
Default: x64


### Build directory structure

The script generates the following structure:

```php-template
/build/<Configuration>/<Architecture>/
```

*Example:*

```bash
build/Release/x64/
```


## Showcase

### Image Preview
<img src="Examples/Example_French_Horn.png" alt="Orchestral Overview" width="640" height="360">

### Demo Video
![](Examples/Example_Showcase_2.0.gif)


## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.