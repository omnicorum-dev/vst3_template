# VST3 Plugin Template

A minimal code generator for a Steinberg VST3 plug-in. Fill in `config.txt`,
run one script, and you get a ready-to-build CMake project (a processor, a
controller, and a factory) with your plug-in's name, company info, and class
IDs already wired in.

The generator itself (`build_template.py`) is plain Python and produces
plain CMake + C++, so the generated project builds on macOS, Windows, and
Linux. The steps below have been verified on macOS; the Windows and Linux
steps follow Steinberg's own documented requirements for building against
the VST3 SDK but haven't been tested against this template yet — see the
per-platform notes for the parts most likely to need adjustment.

## 1. Prerequisites

You need the VST3 SDK itself on every platform. Clone it (with submodules,
even though this template disables the VSTGUI submodule at CMake configure
time, so it doesn't strictly need to be checked out):

```
git clone --recursive https://github.com/steinbergmedia/vst3sdk.git
```

You also need **CMake 3.25 or newer** on every platform — check with
`cmake --version`. This template's generated `CMakeLists.txt` requires
3.25, and several Linux distros ship an older CMake by default (Ubuntu
22.04's `apt` package, for example, is 3.22). If `cmake --version` is too
old, install a newer one via `pip install cmake --break-system-packages`,
the Kitware APT repo, or the installer from cmake.org.

### macOS

- Xcode (or at least the Xcode Command Line Tools: `xcode-select --install`)
- CMake (`brew install cmake`)

This is the path that's already been confirmed working.

### Windows

- Visual Studio 2019 (16.9+) or 2022, with the "Desktop development with
  C++" workload — or the standalone Build Tools for Visual Studio
- CMake (`winget install Kitware.CMake` or the installer from cmake.org)
- **Enable Developer Mode** (Settings → Privacy & Security → For
  developers), or plan to run your terminal as Administrator. The VST3
  SDK's CMake scripts create a symlink from the build output into your
  VST3 plug-ins folder so hosts can find it during development, and
  creating symlinks on Windows requires either Developer Mode or elevated
  privileges. Without one of those, plug-in linking will fail even though
  the compile itself succeeds.

### Linux

- GCC or Clang, plus CMake as noted above
- A handful of development packages. Steinberg's documented list (for
  Ubuntu) is:

  ```
  sudo apt install cmake gcc libstdc++6 libx11-xcb-dev libxcb-util-dev \
    libxcb-cursor-dev libxcb-xkb-dev libxkbcommon-dev libxkbcommon-x11-dev \
    libfontconfig1-dev libcairo2-dev libgtkmm-3.0-dev libsqlite3-dev \
    libxcb-keysyms1-dev
  ```

  Most of that list (the X11/XCB/Cairo/GTK packages in particular) exists
  to support VSTGUI, which this template turns off
  (`SMTG_ENABLE_VSTGUI_SUPPORT OFF`). It's possible a smaller subset is
  enough for a GUI-less plug-in like this one, but that hasn't been
  verified — if `cmake` configure fails on a missing package, install
  from the full list above rather than guessing at a minimal set.

## 2. Configure your plug-in

Edit `config.txt`:

```
ProjectName: examplePlugin
ProjectVersion: 1.0.0
PluginName: Example Plugin
CompanyName: Omnicorum
CompanyCopyright: (c) 2026
CompanyWebsite: https://omnicorum.com/
CompanyEmail: omnicorum@omnicorum.com

ProcessorUID: 0xb4c1e2a7-8f3d4a9e-9c2d7b61-5e8a1f03
ControllerUID: 0xd7a3f291-6b4c4e1a-ae9f2c58-7d0b4361

VST3_SDK_Path: /Users/nicorusso/Development/VST3_SDK/
```

- `ProcessorUID` / `ControllerUID` must be unique per plug-in and, once you
  ship a build, must never change — hosts use them to identify the
  plug-in. Generate fresh ones for each new plug-in (any UUID generator
  works; the script just re-slices the hex digits into the SDK's expected
  format).
- `VST3_SDK_Path` is the absolute path to your local clone of the SDK from
  step 1, and **it's machine- and platform-specific** — set it separately
  on each computer you build on. Use forward slashes even on Windows (for
  example `C:/Dev/vst3sdk/`); CMake accepts them on all platforms, and it
  avoids backslash-escaping problems in the generated `CMakeLists.txt`.

## 3. Generate the project

```
python3 build_template.py
```

This writes `src/` (the C++ sources with your names and IDs filled in) and
a top-level `CMakeLists.txt`. Re-run it any time you change `config.txt`;
it overwrites those generated files.

## 4. Build

### macOS

```
mkdir build && cd build
cmake -GXcode ..
cmake --build . --config Release
```

(A Unix Makefiles or Ninja generator works too if you don't want an Xcode
project — `cmake -GNinja ..`.)

### Windows

```
mkdir build && cd build
cmake -G "Visual Studio 17 2022" -A x64 ..
cmake --build . --config Release
```

### Linux

```
mkdir build && cd build
cmake -DCMAKE_BUILD_TYPE=Release ..
cmake --build .
```

## 5. Find the built plug-in

The build produces a `.vst3` bundle under `build/VST3/<Release|Debug>/`,
named after `ProjectName`. Copy or symlink it into your system's VST3
folder to load it in a host:

- **macOS**: `~/Library/Audio/Plug-Ins/VST3/` (per-user) or
  `/Library/Audio/Plug-Ins/VST3/` (all users)
- **Windows**: `C:\Program Files\Common Files\VST3\`
- **Linux**: `~/.vst3/` (per-user) or `/usr/lib/vst3/` (all users)

In practice the SDK's CMake scripts try to symlink the build output into
the per-user VST3 folder automatically during the build (this is the
Windows Developer Mode requirement mentioned above) — check that folder
before copying manually.

## Known limitations

- Only the macOS build path has actually been run end-to-end. The Windows
  and Linux steps above match Steinberg's documented setup but should be
  treated as a starting point, not a guarantee — particularly the exact
  Linux package list, which may include more than a GUI-less plug-in
  strictly needs.
- `config.txt` is per-machine (because of `VST3_SDK_Path`) — don't expect
  to share one copy of it across platforms without editing that line.
