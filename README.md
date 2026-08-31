<p align="center">
    <img src="https://raw.githubusercontent.com/hedge-dev/UnleashedRecompResources/refs/heads/main/images/logo/Logo.png" width="512"/>
</p>

<p align="center">
       <img width="1672" height="941" alt="ChatGPT Image 31 ago 2026, 22_03_23" src="https://github.com/user-attachments/assets/d026d0fd-08c6-40a7-92a6-000c088f8d79" />
</p>
---

Unleashed Recompiled — Wii U Port (Cafe)

This is an unofficial, in-development fork of Unleashed Recompiled targeting the Nintendo Wii U (Cafe), based on the Nintendo Switch fork by givethesourceplox.

Unleashed Recompiled is an unofficial port of the Xbox 360 version of Sonic Unleashed created through static recompilation. This fork aims to bring it to the Wii U, taking advantage of the console's dual-screen (TV + GamePad) capabilities rather than treating the GamePad as a simple mirror.

[!WARNING] This port is in an early, experimental stage. It does not currently produce a bootable build. CMake toolchain support for Wii U (UNLEASHED_RECOMP_WIIU) has been added, but the GX2 graphics backend, OS abstraction layer, and GamePad input driver are still unimplemented. Do not expect a playable release yet — track progress in Wii U Port Status below.

This project does not include any game assets. You must provide the files from your own legally acquired copy of the game to install or build this port.

Table of Contents
Wii U Port Status
Planned Wii U Features
Minimum Requirements
Building
Original Project Features
Credits
Wii U Port Status

This fork is being developed incrementally. Current state:

 CMake toolchain flag (UNLEASHED_RECOMP_WIIU) added to root, UnleashedRecomp, and UnleashedRecompLib build scripts, mirroring the existing Switch (UNLEASHED_RECOMP_SWITCH) path.
 os/wiiu/* OS abstraction layer (logger, media, process, runtime, user, version) — not started.
 hid/driver/wiiu_hid.cpp — VPAD/GamePad input driver — not started.
 GX2 backend for plume (the project's graphics HAL) — the biggest blocker. Plume currently only supports D3D12, Vulkan, and (in progress) Metal. Wii U's Latte GPU requires a dedicated GX2 backend written from scratch.
 devkitPro / wut toolchain integration and .rpx packaging.
 Dual-screen support (see below).
Planned Wii U Features

Once the base port is running on the TV output, the goal is to replicate the dual-screen approach used by games like Sonic Lost World on Wii U, rather than just off-TV play:

Toggle between playing on the TV or the GamePad screen.
When playing on the TV, the GamePad displays a custom Tails' tablet-style UI instead of a game mirror, showing:
Current ring count
Sun and Moon Medals collected
Achievement progress
Rotating gameplay tips from Tails, including development notes about the Wii U port itself

This is a fork-specific addition not present in the original PC/Linux release or the Switch fork.

Minimum Requirements
Console: Nintendo Wii U, any revision, with the Aroma homebrew environment installed.
Storage: SD card or USB storage device with enough free space for the game's install (see original requirements below for reference; final Wii U footprint has not yet been measured).
Game files: Same as the original project — a legally dumped copy of Sonic Unleashed for Xbox 360 (US or EU, JP not supported), ideally with Title Update and DLC. See the original dumping guides for how to acquire these from real Xbox 360 hardware.
Building

[!NOTE] Full step-by-step build instructions for Wii U will be added once the base toolchain is validated. For now, at a high level:

Install devkitPro with the wiiu-dev package group (provides devkitPPC and wut).
Clone this repository and its submodules.
Configure with CMake using -DUNLEASHED_RECOMP_WIIU=ON and the Wii U toolchain file.
Build host-side tools (XenonRecomp, XenosRecomp, x_decompress) on your PC first — cross-compiled Wii U binaries cannot run these themselves.

For the original PC/Linux build instructions (still useful for reference on shared build steps), see the upstream building guide.

Original Project Features

This fork inherits all of the features from the base Unleashed Recompiled project, including the installer wizard, achievements, custom localization, high-fidelity visuals, asynchronous shader compilation, and mod support via Hedge Mod Manager. See the upstream README for full details on these — they are not being re-documented here to avoid drift between forks. Only Wii U-specific behavior and limitations will be documented in this repository going forward.

[!NOTE] Not all upstream features are expected to work identically on Wii U. Anything not explicitly listed under Wii U Port Status or Planned Wii U Features should be assumed unverified on this platform.

Credits
This Fork
Wii U port development based on the work of the Nintendo Switch fork by givethesourceplox.
Unleashed Recompiled (Upstream)

All credit for the base recompilation, its recompilers (XenonRecomp, XenosRecomp), the graphics/audio backends, custom menus, and every other core system belongs to the original hedge-dev/UnleashedRecomp team — see the full credits list upstream. This fork would not exist without their work.

Special Thanks
Mr-Wiseguy — creator of N64: Recompiled, the original inspiration for this class of project.
xenia-project — for extensive public research into the Xbox 360's internals.
