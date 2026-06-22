# OpenKey for Linux (Fcitx5)

Vietnamese input for Linux, built as a [Fcitx5](https://fcitx-im.org/) input
method addon that reuses OpenKey's platform independent engine
(`Sources/OpenKey/engine`). This is the recommended setup for KDE Plasma / Qt /
Wayland.

> Status: **v1 (core typing)** — Telex, VNI and Simple Telex input, spell
> checking, modern tone placement and the quick-typing options, configured
> through Fcitx5's own config tool. Macros, the encoding convert tool and a
> standalone control panel are not part of this first version.

## Requirements

Build tools (Arch Linux):

```bash
sudo pacman -S --needed cmake fcitx5
# already pulled in by a normal dev setup: base-devel (gcc), make
# optional, for input in GTK apps (Firefox, GNOME apps):
sudo pacman -S --needed fcitx5-gtk
```

The Fcitx5 headers and CMake files are part of the `fcitx5` package on Arch, so
no separate `-dev` package is needed.

## Build & install

```bash
cd Sources/OpenKey/linux
cmake -B build -DCMAKE_INSTALL_PREFIX=/usr
cmake --build build
sudo cmake --install build
```

Installs:

- `/usr/lib/fcitx5/openkey.so` — the addon
- `/usr/share/fcitx5/addon/openkey.conf` — addon descriptor
- `/usr/share/fcitx5/inputmethod/openkey.conf` — input method descriptor

Then restart Fcitx5 so it picks up the new addon:

```bash
fcitx5 -r -d
```

## Enable it

1. **KDE Plasma (Wayland):** System Settings → Input & Output → Virtual
   Keyboard → select **Fcitx 5** (KWin launches the input method on Wayland).
2. Open **Fcitx5 Configuration** (`fcitx5-configtool`), and in *Input Method*
   add **OpenKey** to your active list (it appears under Vietnamese / `vi`).
3. Switch to OpenKey with the Fcitx5 toggle (default **Ctrl + Space**) and type.

Settings (input method, spell check, modern orthography, quick Telex, …) live in
`fcitx5-configtool` → Addons → **OpenKey**, or Input Method → OpenKey → gear
icon.

## Try it

In any text field (Kate, KWrite, a browser):

| Mode  | Type            | Result      |
|-------|-----------------|-------------|
| Telex | `tieengs vieet` | `tiếng việt`|
| VNI   | `tie61ng vie65t`| `tiếng việt`|

The syllable being composed shows as underlined preedit and is committed on
space / punctuation.

## Troubleshooting

- Run `fcitx5 -r` from a terminal and watch the output while typing, or run
  `fcitx5-diagnose`.
- If OpenKey is not listed after install, confirm
  `/usr/lib/fcitx5/openkey.so` and the two `openkey.conf` files exist, then
  `fcitx5 -r -d` again.

## How it works

`src/openkeyengine.cpp` is a thin bridge: it feeds each key into the OpenKey
engine (`vKeyHandleEvent`, key code from `Key::code()` which matches the XKB
codes in `engine/platforms/linux.h`), then applies the engine's
"delete N / emit M characters" result to the Fcitx5 preedit buffer, committing
at word boundaries. Configuration options map onto the engine's global `v*`
settings. The pattern mirrors `fcitx5-unikey`.
