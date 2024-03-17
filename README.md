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

Then run `./build.bat` and it'll place a ROM named `dk64-kioskrestoration-dev.z64` in the ROM folder.

Kiosk is very unstable, and I'm working on fixing some of the stability issues. In the meanwhile, I've found best results with PJ64 3.0.1, and using the interpreter core.

## TODO

- Fix stability issues
- Fix broken texture mapping for the remaining 600-700 textures
- Add a map warp GUI on the press start screen
- Add a stack trace for better crash debugging
