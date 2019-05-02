{ pkgs ? import ./pkgs.nix {} }: with pkgs;

stdenv.mkDerivation {
  name = "triggerd";
  src = lib.cleanSource ./.;

  nativeBuildInputs = [ meson ninja pkgconfig ];
  buildInputs = [ glib ];

  postFixup = "ln -s $out/bin/triggerd $out/bin/trigger";
}
