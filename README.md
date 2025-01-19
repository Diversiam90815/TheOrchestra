# The Orchestra

Welcome to **The Orchestra**. This C++ application serves as an introductory guide for orchestral instruments! 
It is designed to help you explore and understand the diverse sounds and capabilities of orchestral instruments. Whether you're a newcomer to orchestration or an entry-level composer, this app provides a comprehensive overview of different instruments, with additional information such as
- their total range, 
- their qualities or sub ranges, 
- some historical context,
- the most common playing techniques and style,
- and examples of compositions where they are prominently featured. 

Additionally, it includes basic sampling functionalities using a MIDI keyboard to enhance your learning experience. (Though not all instruments are available as of now)

## Features

- **Instrument Information**: Detailed descriptions of various orchestral instruments, including their history, technical details, and roles in the orchestra.
- **MIDI Sampling**: Use a MIDI keyboard to listen to and experiment with the sounds of different instruments. *(in development)*
- **Composition Examples**: Examples of compositions featuring different instruments to illustrate their typical use cases and highlight their versatility.
- **Continuous Updates**: New features and instruments are regularly added as this project is still in development.

## Usage

- **Explore Instruments**: Browse through the list of orchestral instruments to learn about their characteristics and history.
- **Use MIDI Sampling**: Connect your MIDI keyboard to your computer and select an instrument to play its sound samples.
- **Learn Through Examples**: Review provided examples of compositions to see how composers utilize different instruments in their works.


## Roadmap
- **Implement Advanced Sampling Features**: Enhance the MIDI sampling functionality by adding features like multiple articulations, dynamic control, and other expressive playing techniques to provide a more realistic and nuanced sound.
- **Add More Educational Resources and Tutorials**: Integrate comprehensive tutorials, video lessons, and interactive guides to help users learn orchestration, composition techniques, and instrument-specific playing tips.
- **Notation and Score Viewing**: Add features for viewing and interacting with musical scores, including playback functionality, annotation capabilities, and synchronization with MIDI inputs for real-time score following.


## Getting Started

### Cloning the Repository

Clone the repository including:

```bash
git clone https://github.com/Diversiam90815/TheOrchestra.git
```

### Build Instructions

#### 1. Prepare the Build Environment

Before building the project, you need to generate the necessary build files using CMake. This can be done using the `build.py` script with the `--prepare` or `-p` option. The target build configuration can be adjusted in the build.py file: Currently it is set to build a Visual Studio 2022 project.

```bash
cd TheOrchestra
python build.py --prepare
```

For a **Debug** build, add the `--debug` or `-d` option:

```bash
python build.py --prepare --debug
```

#### 2. Build the Project

To build the project, use the `--build` or `-b` option:

```bash
python build.py --build
```

This will compile the project using the build files generated during the preparation step.

- **Release Build**: By default, the build is configured for a Release build.
- **Debug Build**: To build the project in Debug mode, include the `--debug` or `-d` option:

  ```bash
  python build.py --build --debug
  ```

**Important**: If you did not run the `--prepare` step separately, the script will automatically prepare the build environment before building.

#### 3. Combined Preparation and Build

You can combine preparation and building in a single command. This is useful if you want to ensure that your build environment is up-to-date before compiling.

- **Release Build**:

  ```bash
  python build.py --prepare --build
  ```

- **Debug Build**:

  ```bash
  python build.py --prepare --build --debug
  ```

In both cases, including the `--debug` or `-d` option switches the configuration to Debug mode.

### Running the Plugin

After a successful build, the application can be found in the build output directory. Currently, the app is set to build standalone executable binary. They can be found within the respective folder.


---

Thank you for using the Orchestral Instruments Guide! We hope it helps you on your journey to mastering orchestration.
