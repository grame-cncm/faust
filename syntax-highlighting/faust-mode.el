;;; faust-mode.el --- Faust syntax colorizer for Emacs.

;; Copyright (C) 2016 Juan A. Romero

;; Author: rukano <rukano@gmail.com>
;; Author: Juan A. Romero <rukano@gmail.com>
;; Author: Yassin Philip <xaccrocheur@gmail.com>
;; Maintainer: Yassin Philip <xaccrocheur@gmail.com>
;; Maintainer: Juan A. Romero <rukano@gmail.com>
;; Keywords: languages, faust
;; Version: 0.2
;; URL: https://github.com/rukano/emacs-faust-mode
;; License: GPLv3
;; MELPA: yes
;; MELPA-stable: yes

;; This program is free software; you can redistribute it and/or modify
;; it under the terms of the GNU General Public License as published by
;; the Free Software Foundation, either version 3 of the License, or
;; (at your option) any later version.

;; This program is distributed in the hope that it will be useful,
;; but WITHOUT ANY WARRANTY; without even the implied warranty of
;; MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
;; GNU General Public License for more details.

;; You should have received a copy of the GNU General Public License
;; along with this program.  If not, see <http://www.gnu.org/licenses/>.

;;; Commentary:

;; ## Features

;; - Syntax highlighting of *all* the Faust commands and operators
;; - Indentation rules
;; - [Compatible](https://github.com/syl20bnr/spacemacs/tree/develop/layers/%2Blang/faust) with SpaceEmacs

;; ## Installation

;; ### Easy

;; - Install it from [MELPA](https://melpa.org).

;; ### Hard

;; - Copy/clone this repository in `load-path`
;; - Add
;; ```elisp
;; (require 'faust-mode)
;; ```
;; to your init file

;; ### Faust

;; Oh, and of course install [the latest
;; Faust](http://faust.grame.fr/download/) and ensure it's in the
;; PATH.

;; ### Faustine

;; Based on faust-mode, [Faustine](https://bitbucket.org/yphil/faustine) goes even further into turning Emacs into a full-fledged Faust IDE.

;;; Code:


;; disabled for now until we have a Faust grammar for SMIE - agraef
;; (require 'smie)

(defvar ac-sources)

(defconst faust-keywords-statements
  '("process" "with" "case" "seq" "par" "sum" "prod" "include" "import" "component" "library" "environment" "declare" "define" "undef" "error" "pragma" "ident" "if" "def" "else" "elif" "endif" "line" "warning"))

(defconst faust-keywords-functions
  '("mem" "prefix" "int" "float" "rdtable" "rwtable" "select2" "select3" "ffunction" "fconstant" "fvariable" "attach" "acos" "asin" "atan" "atan2" "cos" "sin" "tan" "exp" "log" "log10" "pow" "sqrt" "abs" "min" "max" "fmod" "remainder" "floor" "ceil" "rint"))

(defconst faust-keywords-math
  '("mem" "prefix" "int" "float" "rdtable" "rwtable" "select2" "select3" "ffunction" "fconstant" "fvariable" "attach" "acos" "asin" "atan" "atan2" "cos" "sin" "tan" "exp" "log" "log10" "pow" "sqrt" "abs" "min" "max" "fmod" "remainder" "floor" "ceil" "rint"))

(defconst faust-keywords-ui
  '("button" "checkbox" "vslider" "hslider" "nentry" "vgroup" "hgroup" "tgroup" "vbargraph" "hbargraph"))

(defconst faust-keywords-lib-analyzer
  '("amp_follower" "amp_follower_ud" "amp_follower_ar" "mth_octave_analyzer[N]" "mth_octave_spectral_level6e" "octave_filterbank" "octave_analyzer" "half_octave_filterbank" "half_octave_analyzer" "third_octave_filterbank" "third_octave_analyzer" "analyzer"))

(defconst faust-keywords-lib-basic
  '("samp2sec" "sec2samp" "db2linear" "linear2db" "lin2LogGain" "log2LinGain" "tau2pole" "pole2tau" "midikey2hz" "pianokey2hz" "hz2pianokey" "countdown" "countup" "sweep" "time" "tempo" "period" "pulse" "pulsen" "beat" "count" "take" "subseq" "if" "selector" "selectn" "select2stereo" "Other" "latch" "sAndH" "peakhold" "peakholder" "impulsify" "automat" "bypass1" "bypass2"))

(defconst faust-keywords-lib-compressor
  '("compressor_mono" "compressor_stereo" "limiter_*"))

(defconst faust-keywords-lib-delay
  '("delay" "fdelay" "sdelay" "fdelaylti" "fdelayltv" "fdelay[n]" "fdelay[n]a"))

(defconst faust-keywords-lib-demo
  '("Analyzers" "mth_octave_spectral_level_demo" "Filters" "parametric_eq_demo" "spectral_tilt_demo" "mth_octave_filterbank_demo" "filterbank_demo" "Effects" "cubicnl_demo" "gate_demo" "compressor_demo" "exciter" "moog_vcf_demo" "wah4_demo" "crybaby_demo" "vocoder_demo" "flanger_demo" "phaser2_demo" "freeverb_demo" "stereo_reverb_tester" "fdnrev0_demo" "zita_rev_fdn_demo" "zita_rev1" "Generators" "sawtooth_demo" "virtual_analog_oscillator_demo" "oscrs_demo"))

(defconst faust-keywords-lib-envelope
  '("smoothEnvelope" "ar" "asr" "adsr"))

(defconst faust-keywords-lib-filter
  '("zero" "pole" "integrator" "dcblockerat" "dcblocker" "ff_comb" "ff_fcomb" "ffcombfilter" "fb_comb" "fb_fcomb" "rev1" "fbcombfilter" "ffbcombfilter" "allpass_comb" "allpass_fcomb" "rev2" "allpass_fcomb5" "allpass_fcomb1a" "iir" "fir" "conv" "convN" "tf1" "tf2" "tf3" "notchw" "tf21" "tf22" "tf22t" "tf21t" "av2sv" "bvav2nuv" "iir_lat2" "allpassnt" "iir_kl" "allpassnklt" "iir_lat1" "allpassn1mt" "iir_nl" "allpassnnlt" "tf2np" "wgr" "nlf2" "apnl" "allpassn" "allpassnn" "allpasskl" "allpass1m" "tf2s" "tf2snp" "tf3slf" "tf1s" "tf2sb" "tf1sb" "resonlp" "resonhp" "resonbp" "lowpass" "highpass" "lowpass0_highpass1" "lowpass_plus|minus_highpass" "lowpass_plus|minus_highpass" "lowpass3e" "lowpass6e" "highpass3e" "highpass6e" "bandpass" "bandstop" "bandpass6e" "bandpass12e" "low_shelf" "lowshelf_other_freq" "high_shelf" "highshelf_other_freq" "peak_eq" "cubicnl" "gate_mono" "gate_stereo" "Filtering" "speakerbp" "piano_dispersion_filter" "stereo_width" "echo" "transpose" "mesh_square"))

(defconst faust-keywords-lib-hoa
  '("encoder" "decoder" "decoderStereo" "optimBasic" "optimMaxRe" "optimInPhase" "Usage" "wider" "map" "rotate"))

(defconst faust-keywords-lib-math
  '("SR" "BS" "PI" "FTZ" "neg" "sub(x,y)" "inv" "cbrt" "hypot" "ldexp" "scalb" "log1p" "logb" "ilogb" "log2" "expm1" "acosh" "asinh" "atanh" "sinh" "cosh" "tanh" "erf" "erfc" "gamma" "lgamma" "J0" "J1" "Jn" "Y0" "Y1" "Yn" "fabs" "fmax" "fmin" "np2" "frac" "isnan" "chebychev" "chebychevpoly" "diffn"))

(defconst faust-keywords-lib-misceffect
  '("Dynamic" "cubicnl" "gate_mono" "gate_stereo" "Filtering" "speakerbp" "piano_dispersion_filter" "stereo_width" "echo" "transpose" "Meshes" "mesh_square"))

(defconst faust-keywords-lib-miscoscillator
  '("sinwaveform" "coswaveform" "phasor" "oscsin" "osc" "oscos" "oscp" "osci" "lf_imptrain" "lf_pulsetrainpos" "lf_squarewavepos" "lf_squarewave" "lf_trianglepos" "lf_rawsaw" "lf_sawpos" "lf_sawpos_phase" "sawN(N,freq)" "sawNp" "saw2dpw(freq)" "saw2(freq)" "saw3(freq)" "saw4(freq)" "saw5(freq)" "saw6(freq)" "sawtooth(freq)" "saw2f2(freq)" "saw2f4(freq)" "pulsetrainN" "pulsetrain" "squareN" "square" "imptrain" "imptrainN" "triangle" "triangleN" "oscb" "oscr" "oscrs" "oscs" "oscs" "oscw" "oscwq" "oscwc" "oscws"))

(defconst faust-keywords-lib-noise
  '("noise" "multirandom" "multinoise" "noises" "pink_noise" "pink_noise_vm" "lfnoise" "lfnoise0" "lfnoiseN"))

(defconst faust-keywords-lib-phafla
  '("flanger_mono" "flanger_stereo" "phaser2_mono" "phaser2_stereo"))

(defconst faust-keywords-lib-pm
  '("chain" "input" "output" "terminations" "fullTerminations" "leftTermination" "rightTermination" "waveguide" "idealString"))

(defconst faust-keywords-lib-reverb
  '("jcrev" "satrev" "mono_freeverb" "stereo_freeverb" "fdnrev0" "zita_rev_fdn" "zita_rev1_stereo" "zita_rev1_ambi"))

(defconst faust-keywords-lib-route
  '("cross" "crossnn" "crossn1" "interleave" "butterfly" "hadamard" "recursivize"))

(defconst faust-keywords-lib-signal
  '("bus" "block" "interpolate" "smooth" "smoo" "polySmooth" "bsmooth" "lag_ud" "dot"))

(defconst faust-keywords-lib-spat
  '("panner" "spat" "stereoize"))

(defconst faust-keywords-lib-synth
  '("popFilterPerc" "dubDub" "sawTrombone" "combString" "additiveDrum" "additiveDrum"))

(defconst faust-keywords-lib-vaeffect
  '("moog_vcf" "moog_vcf_2b" "wah4" "autowah" "crybaby" "vocoder"))

(defvar faust-keywords-lib
  (append
   faust-keywords-lib-analyzer
   faust-keywords-lib-basic
   faust-keywords-lib-compressor
   faust-keywords-lib-delay
   faust-keywords-lib-demo
   faust-keywords-lib-envelope
   faust-keywords-lib-filter
   faust-keywords-lib-hoa
   faust-keywords-lib-math
   faust-keywords-lib-misceffect
   faust-keywords-lib-miscoscillator
   faust-keywords-lib-noise
   faust-keywords-lib-phafla
   faust-keywords-lib-pm
   faust-keywords-lib-reverb
   faust-keywords-lib-route
   faust-keywords-lib-signal
   faust-keywords-lib-spat
   faust-keywords-lib-synth
   faust-keywords-lib-vaeffect)
  "All the Faust library function keywords.")

(defvar faust-mode-ac-source
  '((candidates . faust-keywords-lib)))

(defvar faust-regexp-keywords-function (regexp-opt faust-keywords-functions 'words))
(defvar faust-regexp-keywords-statement (regexp-opt faust-keywords-statements 'words))
(defvar faust-regexp-keywords-ui (regexp-opt faust-keywords-ui 'words))
(defvar faust-regexp-keywords-lib (regexp-opt faust-keywords-lib 'words))

(defconst faust-regexp-faust-operator (rx (any ",:*-+><")))

(defconst faust-regexp-faust-delimiters (rx (any "{}()[];")))

(defconst faust-regexp-faust-numbers (rx (one-or-more digit)))

(defconst faust-mode-font-lock-keywords
  `((,faust-regexp-keywords-function . font-lock-function-name-face)
    (,faust-regexp-keywords-statement . font-lock-keyword-face)
    (,faust-regexp-keywords-lib . font-lock-keyword-face)
    (,faust-regexp-keywords-ui . font-lock-variable-name-face)
    (,faust-regexp-faust-operator . font-lock-type-face)
    (,faust-regexp-keywords-lib . font-lock-builtin-face)
    (,faust-regexp-faust-delimiters . font-lock-reference-face)
    (,faust-regexp-faust-numbers . font-lock-negation-char-face)))

(defvar faust-mode-syntax-table
  (let ((st (make-syntax-table)))
    (modify-syntax-entry ?/  ". 124b" st)
    (modify-syntax-entry ?*  ". 23" st)
    (modify-syntax-entry ?\n "> b" st)
    (modify-syntax-entry ?\^m "> b" st)
    st)
  "Syntax table for `faust-mode'.")

;;;###autoload
(define-derived-mode faust-mode prog-mode
  "Faust"
  "Major mode for editing
[Faust](http://faust.grame.fr) (Functional AUdio STream) files.

Syntax highlighting of *all* the Faust commands and operators, as
well as indentation rules."

  (setq
   comment-start "//"
   comment-end ""
   font-lock-defaults '(faust-mode-font-lock-keywords))

  (if (boundp 'ac-sources)
      (progn
        (add-to-list 'ac-modes 'faust-mode)
        (add-to-list 'ac-sources 'faust-mode-ac-source))
    (message "You really should install and use auto-complete"))

  ;; disabled for now until we have a Faust grammar for SMIE - agraef
  ;; (smie-setup nil #'ignore)

  (set-syntax-table faust-mode-syntax-table))

(provide 'faust-mode)

;; End:
;;; faust-mode.el ends here
