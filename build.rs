// build.rs
extern crate bindgen;

use std::{
    env,
    path::{Path, PathBuf},
};
//use std::process::Command;

fn main() {
    // TODO: make this generic & work on bot macOS & Windows

    println!("cargo:rerun-if-changed=ae_wrapper.hpp");

    let ae_sdk_path = &env::var("AESDK_ROOT")
        .expect("AESDK_ROOT environment variable not set – cannot find AfterEffcts SDK.
        Please set AESDK_ROOT to the root folder of you AfterEffects SDK installation (this folder contains /Examples & the SDK Guide PDF).");

    // Write the bindings to the $OUT_DIR/bindings.rs file.
    let out_path = PathBuf::from(env::var("OUT_DIR").unwrap());

    let ae_bindings = bindgen::Builder::default()
        .header("ae_wrapper.hpp")

        .whitelist_function("A_.*")
        .whitelist_type("A_.*")
        .whitelist_var("A_.*")

        .whitelist_function("AEGP.*")
        .whitelist_type("AEGP.*")
        .whitelist_var("AEGP.*")
        .whitelist_var("kAEGP.*")

        .whitelist_var("AEIO_.*")

        .whitelist_function("DRAWBOT_.*")
        .whitelist_type("DRAWBOT_.*")
        .whitelist_var("DRAWBOT_.*")
        .whitelist_var("kDRAWBOT_.*")

        .whitelist_var("FIEL_.*")

        .whitelist_function("PF_.*")
        .whitelist_type("PF_.*")
        .whitelist_var("PF_.*")
        .whitelist_var("kPF.*")

        .whitelist_function("PR_.*")
        .whitelist_type("PR_.*")
        .whitelist_var("PR_.*")

        .whitelist_var("kSP.*")

        .clang_arg(format!("-I{}", Path::new( ae_sdk_path ).join("Examples").join("Headers").display()))
        .clang_arg(format!("-I{}", Path::new( ae_sdk_path ).join("Examples").join("Headers").join("SP").display()))
        .clang_arg(format!("-I{}", Path::new( ae_sdk_path ).join("Examples").join("Util").display()))

        //#[cfg(target_os = "macos")]
        .clang_arg("-I/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/System/Library/Frameworks/CoreFoundation.framework/Versions/A/Headers/")
        //.clang_arg("-I/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/System/Library/Frameworks/CoreServices.framework/Versions/A/Headers/")
        .clang_arg("-I/Library/Developer/CommandLineTools/usr/include/c++/v1/")
        .clang_arg("-F/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/System/Library/Frameworks/")

        .parse_callbacks(Box::new(bindgen::CargoCallbacks))
        .generate()
        .expect("Unable to generate AfterEffects bindings");

    // Write the bindings to the $OUT_DIR/bindings.rs file.
    ae_bindings
        .write_to_file(out_path.join("ae_bindings.rs"))
        .expect("Couldn't write AfterEffects bindings!");
}
