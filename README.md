# The Orchestra

Welcome to **The Orchestra**, an interactive and educational C++ application designed to be your comprehensive guide to the world of orchestral instruments. This tool helps you explore and understand the diverse sounds, roles, and characteristics of instruments in an orchestra. Whether you are a student, an aspiring composer, or simply a music enthusiast, this application offers valuable insights and practical experience.

## Tech Stack

- **Core Language**: C++20
- **Framework**: JUCE 8
- **Build System**: CMake
- **IDE**: Developed and tested with Visual Studio 2022
- **Version Control**: Git
- **Scripting**: Python for build automation

## Features

### Implemented

- **Interactive Instrument Encyclopedia**: Access detailed information for a wide array of orchestral instruments, including:
  - **Instrument Families**: Browse through Strings, Woodwinds, Brass, and Percussion.
  - **Playing Ranges**: View the complete note range for each instrument.
  - **Sound Qualities**: Explore the distinct timbral characteristics across different registers.
  - **Historical Context**: Learn about the history and evolution of each instrument.
  - **Playing Techniques**: Discover common and special playing techniques.
  - **Famous Works**: Listen to examples of compositions where the instrument is prominently featured.

- **Visual Keyboard with Range Highlighting**: An interactive piano roll that visually maps out the selected instrument's range, making it easy to see which notes are playable.

- **Audio Previews via MIDI**: Connect a MIDI keyboard to play and listen to high-quality samples of various instruments. The built-in sampler supports multiple articulations to provide a realistic sound experience.

- **Dynamic and Modern UI**: A sleek, user-friendly interface that dynamically updates as you select different instruments, providing a seamless and intuitive learning experience.



## Getting Started

### Cloning the Repository

Clone the repository including:

```bash
git clone git@github.com:Diversiam90815/TheOrchestra.git
```

Keep in mind that you also need to check out the submodules with this project. To do so, you can include --recurse-submodules within the clone command (with git version 2.13 or higher):

```bash
git clone --recurse-submdules git@github.com:Diversiam90815/TheOrchestra.git
```

or if you already cloned the repository call

```bash
git submodule update --init --recursive
```


### Build Instructions

#### Prepare the Build Environment

Before building the project, you need to generate the necessary build files using CMake. This can be done using the `build.py` script with the `--prepare` or `-p` option. The target build configuration can be adjusted in the build.py file: Currently it is set to build a Visual Studio 2022 project.

```bash
cd TheOrchestra
python build.py -p
```

For a **Debug** build, add the `--debug` or `-d` option:

```bash
python build.py -pd
```

#### Build the Project

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