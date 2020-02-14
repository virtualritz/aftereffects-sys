// build.rs
extern crate bindgen;

use std::env;
use std::path::{Path,PathBuf};
//use std::process::Command;

fn main() {
    // TODO: make this generic & work on bot macOS & Windows

    let ae_sdk_path = &env::var("AESDK_ROOT").expect("AESDK_ROOT environment variable not set – cannot find AfterEffcts SDK.");

    // Write the bindings to the $OUT_DIR/bindings.rs file.
    let out_path = PathBuf::from(env::var("OUT_DIR").unwrap());

    let ae_bindings = bindgen::Builder::default()
        .header("ae_wrapper.hpp")

        .clang_arg(format!("-I{}", Path::new( ae_sdk_path ).join("Examples").join("Headers").display()))
        .clang_arg(format!("-I{}", Path::new( ae_sdk_path ).join("Examples").join("Headers").join("SP").display()))
        .clang_arg(format!("-I{}", Path::new( ae_sdk_path ).join("Examples").join("Util").display()))

        //#[cfg(target_os = "macos")]
        .clang_arg("-I/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/System/Library/Frameworks/CoreFoundation.framework/Versions/A/Headers/")
        //.clang_arg("-I/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/System/Library/Frameworks/CoreServices.framework/Versions/A/Headers/")
        .clang_arg("-I/Library/Developer/CommandLineTools/usr/include/c++/v1/")
        .clang_arg("-F/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/System/Library/Frameworks/")


        .generate()
        .expect("Unable to generate AfterEffects bindings");

    // Write the bindings to the $OUT_DIR/bindings.rs file.
    ae_bindings
        .write_to_file(out_path.join("ae_bindings.rs"))
        .expect("Couldn't write AfterEffects bindings!");
}
