with import <nixpkgs> {};

let
  # Use the let-in clause to assign the derivation to a variable
  install = pkgs.writeShellScriptBin "libsnark-circuit" ''
    pwd \
    && cd libsnark-circuit/depends \
    && git init \
    && git submodule add https://github.com/scipr-lab/libsnark.git libsnark \
    && git submodule update --init --recursive \
    && cd .. \
    && cmake . \
    && make

    '';
in
stdenv.mkDerivation rec {
  name = "libsnark-circuit-env";

  # Add the derivation to the PATH
  buildInputs = [
    install
    pkgs.procps
    pkgs.git
    pkgs.gmp
    pkgs.openssl
    pkgs.boost
    pkgs.cmake
    pkgs.pkg-config
 ];
}
