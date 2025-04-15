# Description
*exodist* is an open-source audio plugin. This audio plugin is a clipper and is mainly focussed around distortion. This can be from soft to heavy distortion.


# How to install
## Windows
1. Go onto the [releases](https://github.com/arcathrax/exodist/releases) page.
2. Download the latest windows version (should have `win-x64` in the name).
3. Unzip the archive.
4. Place it in `C:\Program Files\Common Files\VST3`.
5. Rescan for new plugins in your DAW of choice.


## MacOS
1. Go onto the [releases](https://github.com/arcathrax/exodist/releases) page.
2. Download the latest windows version (should have `macos-universal` in the name).
3. Unzip the archive.
4. Place it in `/Library/Audio/Plug-Ins/VST3`
5. Open your terminal
6. Copy and paste this command `sudo xattr -dr com.apple.quarantine /Library/Audio/Plug-Ins/VST3/exodist-1.0-macos-universal/exodist.vst3`
7. Rescan for new plugins in your DAW of choice.


# Parameters
- **gain**: set the gain before the clipping algorithm.
- **softness**: adjust how hard the algorithm is.
- **threshold**: adjust, when the distortion starts.
- **mix**: adjust the mix of the plugin.
- **volume**: adjust the gain after the distortion.


# Sources
- textures: [texturelabs.org](https://texturelabs.org/)