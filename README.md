# `aftereffects-sys`

Raw AfterEffects (Ae) API bindings via [bindgen](https://github.com/rust-lang/rust-bindgen).

This is WIP – only tested on `macOS`. Will likely require additional work to
build on `Windows`.

> :warning: There are safe, high-level bindings in the
[`aftereffects`](https://github.com/virtualritz/aftereffects) crate. I am
talking to Adobe atm as they wrap some API parts which are not public. I
hope to make the resp. repository public asap. Ping me if you want early
access.

## Prequisites

Download the [*Adobe AfterEffects SDK*](https://console.adobe.io/downloads/ae).
> Note that the SDK published by Adobe is outdated if you are using the 3D
> Artisan API to write your own 3D renderer plug-in.
> Also see [Features](#features) below for more information.
>
> Ignore this if you just want to develop 2D plugins (which still have
access to 3D data).

Define the `AESDK_ROOT` environment variable that contains the path to your
Ae SDK. Typically the directory structure will look like this:

```
AfterEffectsSDK
├── After_Effects_SDK_Guide.pdf
├── Examples
    ├── AEGP
    ├── Effect
    ├── ...
```

Crate `version 0.1.5` was tested with the *Ae SDK* from **October 2021**.

## Configuration

The `build.rs` specifically looks into some of the folders under
`$AESDK_ROOT/Examples`.

The `wrapper.hpp` file contains the headers you need to build your Ae
plugin. Modify as needed. If the header is some (new) SDK folder that
`build.rs` does not yet list, add it.

### Features

* `artisan-2-api` – Use the 2nd generation Artisan 3D API. This is not
  included in the official SDK. Specifically it requires:
  * `AE_Scene3D_Private.h`
  * `PR_Feature.h`

  Contact the Ae SDK team and ask nicely and they may send you theses
  headers.

### macOS

The `build.rs` contains `Clang` arguments to find neccessary system headers.
This is configured for _macOS 10.15_ (Catalina).

You may need to edit this if you are targeting older system headers.

### Windows

TBD. Help wanted!

## Usage

Until this is published it is suggested to use a link to this repository:

```toml
[dependencies]
aftereffects-sys = { git = "https://github.com/virtualritz/aftereffects-sys" }
```

License: Apache-2.0 OR BSD-3-Clause OR MIT OR Zlib
