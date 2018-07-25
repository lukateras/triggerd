with import <nixpkgs> {};

stdenv.mkDerivation {
  name = "triggerd";
  src = lib.cleanSource ./.;

  nativeBuildInputs = [ meson ninja pkgconfig ];
  buildInputs = [ glib ];
}
