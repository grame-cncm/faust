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


(require 'smie)

(defvar ac-sources)

(defconst faust-keywords-statements
  '("process" "with" "letrec" "case" "seq" "par" "sum" "prod" "include" "import" "component" "library" "environment" "declare" "define" "undef" "error" "pragma" "ident" "if" "def" "else" "elif" "endif" "line" "warning"))

(defconst faust-keywords-functions
  '("mem" "prefix" "int" "float" "rdtable" "rwtable" "select2" "select3" "ffunction" "fconstant" "fvariable" "attach" "acos" "asin" "atan" "atan2" "cos" "sin" "tan" "exp" "log" "log10" "pow" "sqrt" "abs" "min" "max" "fmod" "remainder" "floor" "ceil" "rint" "xor"))

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

(defvar faust-keywords-misc
  (append
   faust-keywords-statements
   faust-keywords-functions
   faust-keywords-ui)
  "Miscellaneous Faust keywords and built-in functions.")

(defvar faust-keywords-all
  (append
   faust-keywords-misc
   faust-keywords-lib)
  "All Faust keywords and functions.")

(defvar faust-mode-ac-source
  '((candidates . faust-keywords-all)))

(defvar faust-regexp-keywords-function (regexp-opt faust-keywords-functions 'words))
(defvar faust-regexp-keywords-statement (regexp-opt faust-keywords-statements 'words))
(defvar faust-regexp-keywords-ui (regexp-opt faust-keywords-ui 'words))
(defvar faust-regexp-keywords-lib (regexp-opt faust-keywords-lib 'words))

(defconst faust-regexp-faust-operator (rx (any ",'@:*/%^-+|&~>=<!")))

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

;; agraef: We derive the syntax table from C mode here since it's much closer
;; to Faust's lexical syntax than the default syntax table which seems to be
;; geared more towards Lisp. That way we get comment syntax for free and only
;; need to fix up \ and ' which are just ordinary punction in Faust.
(require 'cc-mode)
(defvar faust-mode-syntax-table
  (let ((st (make-syntax-table c-mode-syntax-table)))
    (modify-syntax-entry ?\\ "." st)
    ;; XXXFIXME: ' should really be punctuation, but for reasons unknown to
    ;; mankind this completely throws off SMIE's automatic indentation
    ;; engine. Adding ' to the SMIE grammar or indentation rules doesn't help
    ;; with that either. We work around this by just declaring ' a prefix
    ;; character for now (word or symbol constituent works, too, but has other
    ;; unwanted implications). If anyone has a better idea on how to fix this,
    ;; please let me know! -agraef
    (modify-syntax-entry ?\' "'" st)
    st)
  "Syntax table for `faust-mode'.")

;; agraef: Preliminary Faust SMIE support. Due to restrictions in SMIE, the
;; grammar given here is just a minimal version of the Faust grammar for the
;; sole purpose of defining proper indentation. We also offer two variables
;; faust-indent and faust-outdent-blocks which let you customize some aspects
;; of the indentation, and it's possible to turn off SMIE altogether if it's
;; not working for you, see below for details.

(defgroup faust nil
  "Major mode for editing Faust code."
  :link '(custom-group-link :tag "Font Lock Faces group" font-lock-faces)
  :prefix "faust-"
  :group 'languages)

(defcustom faust-enable-smie t
  "Whether Faust mode does auto-indentation using SMIE.
Non-nil means that auto-indentation using SMIE is enabled.
Please note that this option will only take effect in newly
created Faust buffers."
  :type 'boolean
  :group 'faust)

;; I prefer small indentation levels, so the default indent is 2, but you can
;; change this by customizing the following variable.

(defcustom faust-indent 2
  "This variable gives the indentation in Faust mode."
  :type 'integer
  :group 'faust)

(make-variable-buffer-local 'faust-indent)

;; Custom indentation of block constructs: `with' and `letrec' are actually
;; part of the expression syntax, so that they'd be indented like this:
;;
;;   lhs = rhs with {
;;           foo = bar;
;;         };
;;
;; But these constructs are most commonly used with the entire rhs of a
;; definition, which suggests the following alternative indentation:
;;
;;   lhs = rhs with {
;;     foo = bar;
;;   };
;;
;; I think that this looks better and it also matches the indentation style
;; used in the Faust Quick Reference, so this is the default right now.
;; But if you prefer the former style, you can get that by setting the
;; `faust-outdent-blocks' variable to `nil'. Also note that even if the latter
;; style is used, you can make sure that a block expression is interpreted as
;; part of the right-hand side (and indented accordingly) by just enclosing
;; the entire block expression in parentheses.

(defun faust-make-smie-grammar (outdent-blocks)
  (smie-prec2->grammar
   (smie-bnf->prec2
    `((id)
      ,(if outdent-blocks
	   '(def ("declare" id)
		 (id "=" exp)
		 (id "=" exp "with" "{" defs "}")
		 (id "=" exp "letrec" "{" defs "}")
		 (exp))
	 '(def ("declare" id)
	       (id "=" exp)
	       (exp)))
      (defs (defs ";" defs) (def))
      (exp (id)
	   (id "(" exp ")")
	   (exp "~" exp)
	   (exp "," exp)
	   (exp ":" exp)
	   (exp "<:" exp) (exp ":>" exp)))
    '((assoc ";"))
    '((nonassoc "=") (assoc "~") (assoc ",") (assoc ":") (assoc "<:" ":>")))))

(defcustom faust-outdent-blocks t
  "Configure indentation of Faust block constructs.
Non-nil means to indent the `with' and `letrec' constructs
relative to the definition, not the right-hand side expression.

Please note that this option will only take effect in newly
created Faust buffers.  To apply the setting to an already
existing Faust buffer, you have to run \\[faust-smie-reset] in
that buffer."
  :type 'boolean
  :set (lambda (_symbol value)
	 (setq-default faust-outdent-blocks value)
	 (setq faust-smie-grammar (faust-make-smie-grammar value)))
  :group 'faust)

(defvar faust-smie-grammar (faust-make-smie-grammar faust-outdent-blocks))

(defun faust-smie-reset ()
  "Reset the SMIE setup in the current Faust buffer."
  (interactive)
  (when (and (derived-mode-p 'faust-mode) faust-enable-smie)
    (smie-setup faust-smie-grammar #'faust-smie-rules)))

(defun faust-smie-rules (kind token)
  (pcase (cons kind token)
    (`(:elem . basic) faust-indent)
    (`(:list-intro . ,_) t)
    (`(,_ . ",") (smie-rule-separator kind))
    (`(:after . "=") faust-indent)
    (`(:before . ,(or `"(" `"{" `"["))
     (if (smie-rule-hanging-p) (smie-rule-parent)))
    ))

(defvar faust-font-lock-syntactic-keywords
  '(;; <mdoc> .. </mdoc> sections are treated as comments
    ("\\(<\\)mdoc>" 1 "!" t) ("</mdoc\\(>\\)" 1 "!" t)))

;;;###autoload
(define-derived-mode faust-mode prog-mode
  "Faust"
  "Major mode for editing Faust code (URL `http://faust.grame.fr').

Provides syntax highlighting of Faust keywords and library
functions, as well as indentation rules. Auto-completion of
library functions is available if you install and enable the
`auto-complete' package available from MELPA."

  (setq
   comment-start "//"
   comment-end ""
   comment-start-skip "\\(//+\\|/\\*+\\)\\s *"
   font-lock-defaults
   '(faust-mode-font-lock-keywords
     nil nil nil nil
     (font-lock-syntactic-keywords . faust-font-lock-syntactic-keywords)))

  (if (boundp 'ac-sources)
      (progn
        (add-to-list 'ac-modes 'faust-mode)
        (add-to-list 'ac-sources 'faust-mode-ac-source))
    (message "You really should install and use auto-complete"))

  (when faust-enable-smie
    (smie-setup faust-smie-grammar #'faust-smie-rules))

  (set-syntax-table faust-mode-syntax-table))

(provide 'faust-mode)

;; End:
;;; faust-mode.el ends here
