# Faust Syntax Highlighting Files

This folder contains syntax highlighting files for various editors. The editors currently supported are: 

* [KDE Kate/Kwrite](https://kate-editor.org/)
* [GNOME gedit](https://wiki.gnome.org/Apps/Gedit)
* [TextWrangler](https://www.barebones.com/products/textwrangler/)
* [Highlight](http://www.andre-simon.de/)
* [Vim](https://www.vim.org/)
* [GNU Emacs](https://www.gnu.org/software/emacs/)
* [GNU nano](https://www.nano-editor.org/)
* [Atom](https://atom.io/)
* [Visual Studio Code](https://code.visualstudio.com/)

## KDE Kate/Kwrite

Install the file `faust.xml` into Kate syntax folder (`/opt/kde3/share/apps/katepart/syntax` on suse 10.0 or `/usr/share/apps/katepart/syntax` on mandriva and ubuntu)

## gedit

Install the file `faust.lang` into gedit syntax folder (`/usr/share/gtksourceview-2.0/language-specs` on Ubuntu 9.10)

## TextWrangler
Install the file `Faust.plist` into `~/Library/Application Support/TextWrangler/Language Modules/`

## Highlight

Install `dsp.lang` into `/usr/share/highlight/langDefs/`

Examples using highlight:
* `highlight --latex -l -t 4 -i karplus.dsp -o karplus.dsp.tex`
* `highlight -l -t 4 -i mixer.dsp -o mixer.dsp.html`

## Vim

`faust.vim` is a syntax file for VIM contributed by Bjorn Lindig

1. Install the file `faust.vim` into vim syntax folder (`~/.vim/syntax/`)
2. Add the following lines to the file `filetype.vim` in the `~/.vim` directory (if its not there, you have to create it):

```
faust filetype file
    if exists("did_load_filetypes")
      finish
    endif
    augroup filetypedetect
      au! BufRead,BufNewFile *.fst      setfiletype faust
      au! BufRead,BufNewFile *.dsp      setfiletype faust
    augroup END
```

## Emacs
Copy the file `faust-mode.el` into `/usr/share/emacs/site-lisp` and add the following lines to your `.emacs` file:

```
(require 'faust-mode)
(setq auto-mode-alist (cons '("\\.dsp$" . faust-mode) auto-mode-alist))
```

NB: This is the latest version of emacs-faust-mode created by Juan Gabriel Alzate Romero, cf. https://github.com/agraef/emacs-faust-mode.

## nano

1. Copy the file `faust.nanorc` into folder `/usr/share/nano/`
2. Add the following lines to the file `/etc/nanorc`

```
set tabsize 4
include "/usr/share/nano/faust.nanorc"
```

## Atom

Copy the directory `atom/language-faust` into `~/.atom/packages/` and follow the instructions in [atom/language-faust/README.md](atom/language-faust/README.md)

## Visual Studio Code

1. From within Visual Studio Code bring up the Extensions view by clicking on the `Extensions` icon in the Activity Bar on the side of VS Code or the `View: Extensions` command.
2. Enter `faust` in the search field, press Enter and then select the extension.
3. Click Install to automatically download and install the extension.

NB: This is the latest version of [faust extension](https://marketplace.visualstudio.com/items?itemName=glen-anderson.vscode-faust) created by Glen Anderson, cf. https://github.com/hellbent/vscode-faust.
