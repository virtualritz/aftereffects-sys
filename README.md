# aftereffects-sys

Rust crate that generates raw AfterEffects API bindings via [bindgen](https://github.com/rust-lang/rust-bindgen).

This is WIP – only tested on _macOS_. Will likely require additional work to build on _Windows_.

## Prequisites:
Download the [Adobe AfterEffects SDK](https://console.adobe.io/downloads/ae).
> Note that the SDK published by Adobe is outdated if you are using the 3D Artisan API to
> write your own 3D renderer plug-in.
> Contact the AfterEffects SDK team and ask nicely and they may send you an updated SDK.
>
> Ignore this if you just want to develop regular 2D plugins.

Define an `AESDK_ROOT` environment variable that contains the path to your AfterEffects SDK.
Typically the directory structure will look like this:
```
AfterEffectsSDK
├── After_Effects_SDK_Guide.pdf
├── Examples
    ├── AEGP
    ├── Effect
    ├── ...
```

## Configure

The `build.rs` specifically looks into some of the folders under `$AESDK_ROOT/Examples`.

The file `ae_wrapper.hpp` contains the headers you need to build your AfterEffects plugin.
Modify as needed. If the header is some (new) SDK folder that `build.rs` does not yet list, add it.

### macOS

The `build.rs` contains Clang arguments to find neccessary system headers. This configured for _macOS 10.15_ (Catalina).

You may need to edit this if you are targeting older system headers. 

### Windows

TBD.

## Build

```bash
cargo build
```

## Use

Suggested use until published: use a local copy in a subdirectory of your project. Aka:
```toml
[dependencies]
aftereffects-sys = { path = "aftereffects-sys" }
```

