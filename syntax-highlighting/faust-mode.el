;;; faust-mode.el --- Basic faust syntax colorizer for emacs.

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; FAUST Mode (very simple syntax colorizing!)
;; by rukano
;; based on the tutorial on:
;; http://xahlee.org/emacs/elisp_syntax_coloring.html
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;; BIG TODOS:
;; Colorize Composition Operators
;; Colorize after keyword {}
;; Colorize arguments (numbers)
;; Colorize [] metadata in string?
;; Run Shell faust w/ custom defaults
;; *** Get rid of the No comment syntax defined warning


;; ROADMAP
;; export option and list possibilities
;; create hotkeys for every compilation
;; view graph

(defvar faust-keywords
  '("process" "with" "case" "seq" "par" "sum" "prod"
    "include" "import" "component" "library" "environment" "declare"
    "define" "undef" "error" "pragma" "ident"
    "if" "def" "else" "elif" "endif" "line" "warning"))
 
(defvar faust-functions
  '("mem" "prefix" "int" "float"
    "rdtable" "rwtable" "select2" "select3"
    "ffunction" "fconstant" "fvariable"
    "attach" "acos" "asin" "atan" "atan2" "cos" "sin" "tan" "exp"
    "log" "log10" "pow" "sqrt" "abs" "min" "max" "fmod"
    "remainder" "floor" "ceil" "rint"))

(defvar faust-ui-keywords
  '("button" "checkbox" "vslider" "hslider" "nentry"
    "vgroup" "hgroup" "tgroup" "vbargraph" "hbargraph"))

;; optimize regex for words
;;(defvar faust-math-op-regexp "[=\+()\{\}*-]")
(defvar faust-variables-regexp "[A-Za-z][A-Za-z]*")
(defvar faust-arguments-regexp "[0-9]")
(defvar faust-operator-regexp "\\([~!_@,<>:;]\\)")
(defvar faust-math-op-regexp "[=\+\{\}()/*-]")
(defvar faust-keywords-regexp (regexp-opt faust-keywords 'words))
(defvar faust-function-regexp (regexp-opt faust-functions 'words))
(defvar faust-ui-keywords-regexp (regexp-opt faust-ui-keywords 'words))

;; create the list for font-lock.
(setq faust-font-lock-keywords
      `(
        (,faust-function-regexp . font-lock-type-face)
        (,faust-ui-keywords-regexp . font-lock-builtin-face)
        (,faust-math-op-regexp . font-lock-function-name-face)
        (,faust-operator-regexp . font-lock-constant-face)
        (,faust-keywords-regexp . font-lock-keyword-face)
        ;;    (,faust-variables-regexp . font-lock-variable-name-face)
        ;;    (,faust-arguments-regexp . font-lock-warning-face)
        ))

;; define the mode
;;;###autoload
(define-derived-mode faust-mode fundamental-mode
  "FAUST mode"
  "Major mode for editing FAUST files (Functional Audio Stream)…"

  ;; code for syntax highlighting
  (setq font-lock-defaults '((faust-font-lock-keywords)))
)

;; comment dwin support
(defun faust-comment-dwim (arg)
"Comment or uncomment current line or region in a smart way.
For detail, see `comment-dwim'."
   (interactive "*P")
   (require 'newcomment)
   (let ((deactivate-mark nil) (comment-start "//") (comment-end ""))
     (comment-dwim arg)))

(modify-syntax-entry ?/  ". 124b" faust-mode-syntax-table)
(modify-syntax-entry ?*  ". 23" faust-mode-syntax-table)
(modify-syntax-entry ?\n "> b" faust-mode-syntax-table)
(modify-syntax-entry ?\^m "> b" faust-mode-syntax-table)

(provide 'faust-mode)

;; End:
;;; faust-mode.el ends here
