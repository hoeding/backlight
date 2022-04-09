# backlight
Simple program to adjust backlight brightness

## Usage:

To increase brightness by 10%

`bli 10`

To decrease brightness by 20%

`bld -20`

To set brightness to 75%

`bla 75`

To generate simple config files

`bl-scanner --xdg` 

`bl-scanner --etc`
  
`bl-scanner --dir=/tmp/foo/`
  

## Configuration:
tldr; `mkdir --parents ~/.config/backlight/config && ls /sys/class/backlight/ >> ~/.config/backlight/config`.

Default configuration paths are `/etc/backlight/config` and `~/.config/backlight/config`. All configured backlights will get adjusted. For now the format is one device per line. To find your device `ls /sys/class/backlight`.

## Build and install
Requires a C++20 compiler.
### Build
`git clone https://github.com/hoeding/backlight.git`

`mkdir build`

`cd build`

`cmake ../backlight`

`make`

`su`

`make install`
## Troubleshooting:


# swayutil
*not final name

swayutil is intended to provide useful information to your sway desktop. It currently monitors screen brightness, time and battery remaining.

## Usage

In your sway config file (~/.config/sway/config) replace the default status_command line with

`status_command swayutil`

