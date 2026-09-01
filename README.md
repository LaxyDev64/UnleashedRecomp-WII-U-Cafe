
<p align="center">
  <img width="1672" height="941" alt="Sonic Unleashed Recompiled — Wii U Port banner" src="https://github.com/user-attachments/assets/d026d0fd-08c6-40a7-92a6-000c088f8d79"/>
</p>

<h1 align="center">Unleashed Recompiled — Wii U Port (Cafe)</h1>

<p align="center">
  An unofficial, in-development fork of <a href="https://github.com/hedge-dev/UnleashedRecomp">Unleashed Recompiled</a> targeting the Nintendo Wii U, based on the Nintendo Switch fork by <a href="https://github.com/givethesourceplox/UnleashedRecomp-NX">givethesourceplox</a>.
</p>

<p align="center">
  <img alt="Platform" src="https://img.shields.io/badge/platform-Wii%20U-8B5CF6">
  <img alt="Status" src="https://img.shields.io/badge/status-early%20%2F%20experimental-orange">
  <img alt="License" src="https://img.shields.io/badge/license-GPL--3.0-blue">
  <img alt="Not bootable yet" src="https://img.shields.io/badge/bootable%20build-not%20yet-red">
</p>

---

> [!WARNING]
> This port is in an **early, experimental stage**. It does **not** currently produce a bootable build. CMake toolchain support for Wii U (`UNLEASHED_RECOMP_WIIU`) has been added, but the **GX2 graphics backend**, **OS abstraction layer**, and **GamePad input driver** are still unimplemented. Do not expect a playable release yet — track progress in [Wii U Port Status](#wii-u-port-status).

> [!IMPORTANT]
> This project does **not** include any game assets. You must provide the files from your own legally acquired copy of the game to install or build this port.

Unleashed Recompiled is an unofficial port of the Xbox 360 version of *Sonic Unleashed*, created through static recompilation. This fork aims to bring it to the Wii U — taking full advantage of the console's **dual-screen** capability (TV + GamePad) instead of treating the GamePad as a simple off-TV mirror.

## Table of Contents

- [Wii U Port Status](#wii-u-port-status)
- [Planned Wii U Features](#planned-wii-u-features)
- [Minimum Requirements](#minimum-requirements)
- [Building](#building)
- [Repository Layout](#repository-layout)
- [Original Project Features](#original-project-features)
- [Credits](#credits)
- [License](#license)

## Wii U Port Status

This fork is being developed incrementally. Current state:

| Component | Status |
|---|---|
| CMake toolchain flag (`UNLEASHED_RECOMP_WIIU`) | ✅ Added — mirrors the existing Switch (`UNLEASHED_RECOMP_SWITCH`) path |
| `os/wiiu/*` OS abstraction layer (logger, media, process, runtime, user, version) | ⛔ Not started |
| `hid/driver/wiiu_hid.cpp` — VPAD/GamePad input driver | ⛔ Not started |
| **GX2 backend for plume** (graphics HAL) | 🚧 **Biggest blocker.** Plume currently only supports D3D12, Vulkan, and (in progress) Metal. Wii U's Latte GPU requires a dedicated GX2 backend written from scratch |
| devkitPro / `wut` toolchain integration and `.rpx`/`.wuhb` packaging | 🚧 In progress — icon and TV/GamePad splash assets prepared |
| GamePad dual-screen UI ("Tails' tablet") | 🚧 In progress — code scaffold and art assets (button icons, Sun Medal animation) drafted, not yet wired to a real render target |
| Dual-screen support (see [Planned Wii U Features](#planned-wii-u-features)) | ⛔ Blocked on GX2 backend |

## Planned Wii U Features

Once the base port is running on the TV output, the goal is to replicate the dual-screen approach used by games like *Sonic Lost World* on Wii U, rather than just off-TV play:

- Toggle between playing on the TV or the GamePad screen.
- When playing on the TV, the GamePad displays a custom **Tails' tablet**-style UI instead of a game mirror, showing:
  - Current ring count
  - Sun and Moon Medals collected
  - Achievement progress
  - Rotating gameplay tips from Tails, including development notes about the Wii U port itself

This is a fork-specific addition not present in the original PC/Linux release or the Switch fork.

## Minimum Requirements

- **Console:** Nintendo Wii U, any revision, with the [Aroma](https://aroma.foryour.cafe/) homebrew environment installed.
- **Storage:** SD card or USB storage device with enough free space for the game's install (see original requirements for reference; final Wii U footprint has not yet been measured).
- **Game files:** Same as the original project — a legally dumped copy of *Sonic Unleashed* for Xbox 360 (US or EU; JP not supported), ideally with Title Update and DLC. See the original [dumping guides](docs/DUMPING-en.md) for how to acquire these from real Xbox 360 hardware.

## Building

> [!NOTE]
> Full step-by-step build instructions for Wii U will be added once the base toolchain is validated. For now, at a high level:

1. Install [devkitPro](https://devkitpro.org/wiki/Getting_Started) with the `wiiu-dev` package group (provides `devkitPPC` and `wut`).
2. Clone this repository **with submodules**:
   ```sh
   git clone --recurse-submodules https://github.com/LaxyDev64/UnleashedRecomp-WII-U-Cafe.git
   ```
3. Configure with CMake using `-DUNLEASHED_RECOMP_WIIU=ON` and the Wii U toolchain file.
4. Build the host-side tools (`XenonRecomp`, `XenosRecomp`, `x_decompress`) on your PC first — cross-compiled Wii U binaries cannot run these themselves.

For the original PC/Linux build instructions (still useful as a reference for shared build steps), see the [upstream building guide](https://github.com/hedge-dev/UnleashedRecomp/blob/main/BUILDING.md).

## Repository Layout

```
UnleashedRecomp-WII-U-Cafe/
├── UnleashedRecomp/          Main game source (recompiled game + UI + GPU backend)
│   ├── ui/                   Menus, HUD, and GamePad tablet UI
│   ├── gpu/                  Rendering backend (plume) + ImGui integration
│   └── res/wiiu/             Icon and splash screens for WUHB packaging
├── UnleashedRecompResources/ Submodule — binary assets (textures, fonts, sounds)
├── tools/                    Host-side recompilers and asset conversion utilities
│   ├── XenonRecomp/          PowerPC → C++ recompiler
│   ├── XenosRecomp/          Xbox 360 shader → HLSL converter
│   └── file_to_c/            Binary → C array packer (used for compiled-in assets)
└── docs/                     Build and dumping guides
```

## Original Project Features

This fork inherits all of the features from the base Unleashed Recompiled project, including the installer wizard, achievements, custom localization, high-fidelity visuals, asynchronous shader compilation, and mod support via Hedge Mod Manager. See the [upstream README](https://github.com/hedge-dev/UnleashedRecomp) for full details on these — they are not re-documented here to avoid drift between forks. Only Wii U-specific behavior and limitations will be documented in this repository going forward.

> [!NOTE]
> Not all upstream features are expected to work identically on Wii U. Anything not explicitly listed under [Wii U Port Status](#wii-u-port-status) or [Planned Wii U Features](#planned-wii-u-features) should be assumed unverified on this platform.

## Credits

**This fork**
- Wii U port development based on the work of the Nintendo Switch fork by [givethesourceplox](https://github.com/givethesourceplox/UnleashedRecomp-NX).

**Unleashed Recompiled (Upstream)**
- All credit for the base recompilation, its recompilers ([XenonRecomp](https://github.com/hedge-dev/XenonRecomp), [XenosRecomp](https://github.com/hedge-dev/XenosRecomp)), the graphics/audio backends, custom menus, and every other core system belongs to the original [hedge-dev/UnleashedRecomp](https://github.com/hedge-dev/UnleashedRecomp) team — see the full [credits list](https://github.com/hedge-dev/UnleashedRecomp#credits) upstream. This fork would not exist without their work.

**Special Thanks**
- [Mr-Wiseguy](https://github.com/Mr-Wiseguy) — creator of [N64: Recompiled](https://github.com/Mr-Wiseguy/N64Recomp), the original inspiration for this class of project.
- [xenia-project](https://github.com/xenia-project) — for extensive public research into the Xbox 360's internals.

## License

This project is licensed under **GPL-3.0**, same as the upstream [hedge-dev/UnleashedRecomp](https://github.com/hedge-dev/UnleashedRecomp) project it's forked from.
