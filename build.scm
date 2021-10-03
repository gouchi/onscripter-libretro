(use-modules
 (gnu packages compression)
 (gnu packages fontutils)
 (gnu packages image)
 (gnu packages sdl)
 (gnu packages xiph)
 (guix build-system gnu)
 (guix download)
 (guix gexp)
 (guix git)
 ((guix licenses) #:prefix license:)
 (guix packages)
 (guix utils))

(package
  (name "libretro-onscripter")
  (version "0.0")
  (source (local-file (dirname (current-filename))
                      #:recursive? #t
                      #:select?
                      (lambda (file stat)
                        (not (string=? (basename file) ".git")))))
  (build-system gnu-build-system)
  (arguments
   `(#:tests? #f
     #:make-flags (list (string-append "CC=" ,(cc-for-target))
                        (string-append "CXX=" ,(cxx-for-target)))
     #:phases
     (modify-phases %standard-phases
       (replace 'configure
         (lambda* (#:key inputs #:allow-other-keys)
           (for-each
            (lambda (dep)
              (define destdir (string-append "deps/" dep))
              (mkdir-p destdir)
              (invoke "tar" "-C" destdir
                      "--strip-components=1" "-xvf"
                      (assoc-ref inputs dep)))
            '("bzip2" "freetype" "libogg" "libvorbis" "libjpeg-turbo"
              "sdl" "sdl-image" "sdl-mixer" "sdl-ttf" "onscripter"))
           (copy-recursively "deps/config/freetype"
                             "deps/freetype/include/freetype/config")
           (copy-recursively "deps/config/libjpeg-turbo"
                             "deps/libjpeg-turbo")
           (copy-recursively "deps/config/libogg"
                             "deps/libogg/include/ogg")
           (copy-recursively "deps/config/sdl"
                             "deps/sdl/include")))
       (replace 'install
         (lambda* (#:key outputs #:allow-other-keys)
           (let* ((out (assoc-ref outputs "out"))
                  (libretrodir (string-append out "/lib/libretro")))
             (install-file "onscripter_libretro.so"
                           libretrodir)))))))
  (inputs
   `(("bzip2" ,(package-source bzip2))
     ("freetype" ,(package-source freetype))
     ("libogg" ,(package-source libogg))
     ("libvorbis" ,(package-source libvorbis))
     ("libjpeg-turbo" ,(package-source libjpeg-turbo))
     ("sdl" ,(package-source sdl))
     ("sdl-image" ,(package-source sdl-image))
     ("sdl-mixer" ,(package-source sdl-mixer))
     ("sdl-ttf" ,(package-source sdl-ttf))
     ("onscripter" ,(origin
                     (method url-fetch)
                     (uri "http://onscripter.osdn.jp/onscripter-20200722.tar.gz")
                     (sha256
                      (base32
                       "0pnkki59k26pqxv1lh0rdcryc2w477ag2vqnpx3dmqva6fng9r8j"))))))
  (home-page "https://github.com/iyzsong/onscripter-libretro/")
  (synopsis "Libretro core for ONScripter")
  (description "ONScripter is a visual novel games engine compatible
to NScripter, this package provides a libretro core allowing the
ONScripter visual novel games to be played with libretro frontends
such as RetroArch.")
  (license license:gpl3+))
