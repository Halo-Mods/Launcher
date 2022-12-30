# Halomods Launcher

The Halomods Launcher for Halo MCC allows you to join your friends through Discord, and select whether to launch the game with or without the Halomods extensions, so you can still play with EAC enabled for matchmaking.

## Installation instructions

1. In your Halo MCC install directory, rename `mcclauncher.exe` to `_mcclauncher.exe`.
2. Extract the contents from the latest Github release's zip archive into your Halo MCC install folder.
3. In Steam, choose to launch Halo MCC with EAC on. This may seem counter-intuitive, but this is how we run our launcher, by overriding EAC's mcclauncher.exe.

## Configuration

The Halomods launcher creates an INI called HMSettings.ini in the root of your Halo MCC install folder.

```ini
[Launcher]
Autolaunch
```
Having Autolaunch set to 1 will launch without EAC and with the Halomods extensions, and 0 will launch vanilla with EAC. Remove the setting in the INI to disable Autolaunch and enable the Halomods launcher UI when you launch Halo MCC.

```ini
[Discord]
EnableRichPresence
```
This setting is straightforward. Set it to 1 to enable Rich Presence, and vice versa.

## Build instructions

You need to create a `Directory.Build.Props` file in the root of the repo for MSBuild. Configure it like so:
```xml
<Project>
    <PropertyGroup>
        <MCCDir>(PATH TO MCC)</MCCDir>
    </PropertyGroup>
</Project>
```
Building for Debug will output to your MCC directory. Building for Release will still output in the default MSBuild directory.
