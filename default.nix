with import <nixpkgs> {};

stdenv.mkDerivation {
  name = "triggerd";

  nativeBuildInputs = [ pkgconfig ];
  buildInputs = [ glib ];

  buildCommand = ''
    cc ${./triggerd.c} $(pkg-config --cflags --libs gio-2.0 glib-2.0) -o $out
  '';
}
