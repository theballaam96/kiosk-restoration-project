# DK64 Kiosk Restoration Project
Restoration project for the Kiosk Version of Donkey Kong 64.

## Why?

The Kiosk version of Donkey Kong 64, demonstrated in retailers in September 1999, has a lot of data missing as Rareware stripped the game of most non-vital assets. This results in most deep-dive videos of the Kiosk version of DK64 having a lack of terrain. This hack aims to restore that and return the game into a semi-playable state.

## Building

To build the hack, you must have two ROMs in the `./rom/` directory, as this hack pulls assets from the US version of DK64 and puts it into the Kiosk version of DK64.

```
KIOSK ROM
File name: dk64_kiosk.z64
SHA: b4717e602f07ca9be0d4822813c658cd8b99f993

US 1.0 ROM
File name: dk64_us.z64
SHA: cf806ff2603640a748fca5026ded28802f1f4a50
```

Ensure you're running the latest stable build of python, and you have pip installed the `requests` module for python, as this will be needed to build the hack and download n64chain for the compiler. Afterwards, run `./build.bat` and it'll place a ROM named `dk64-kioskrestoration-dev.z64` in the ROM folder.

## Running

Due to the current state of stability of this project due to the natural instability of vanilla kiosk, your mileage with certain emulators and platforms will vary more than usual. Personally I've had the better end of the experience with Project64 3.0.1, and setting the core type to `Interpreter`. However, other emulators like BizHawk 1.12.1 and even Everdrive seem to function as expected.

## Known Issues

### General Instability
The Kiosk version of DK64 is **incredibly** unstable as it's a mid-development program and has enumerable bugs. I'm working on fixing the general instability issues for Kiosk without impacting the things which make Kiosk unique.

## Textures look weird
For the 190-odd imported maps from the US version, they will have some form of visual abnormalities. This is because the geometry files reference specific texture indexes from a table for the game to load, which is all well and good until you shift the position of all the textures around. I've done a batch re-matching with some code to analyze file differences and re-map textures where the differences surpass a 90% confidence threshold. This leaves about 600-700 textures which I need to manually find a good accurate match for and re-map.

## Radar of things to modify
- Fix stability issues
- Fix broken texture mapping for the remaining 600-700 textures
- Add a stack trace for better crash debugging
