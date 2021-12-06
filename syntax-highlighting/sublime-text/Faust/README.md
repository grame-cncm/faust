# Sublime Text 4 completions and snippets

Copy this folder (`Faust`) to your `Packages/User` directory. On Linux it's `$HOME/.config/sublime-text/Packages/User`.
To find the right directory, use Preferences > Browse Packages..., you will find or create the User folder here.

This only provides completions for the standard library. The available snippets are taken from the atom syntax highlighting provided in this repo.
You can use https://github.com/nuchi/faust-sublime-syntax for syntax highlighting.

This was made for ST4. I (@Simon-L) haven't tested on ST3 or earlier.

The `*.sublime-snippet` files each contain one snippet.
The `faust.sublime-completions` contains all the completions generated with `faust2sublimecompletions`.

The provided `faust.sublime-completions` file here has been generated on Dec. 6 2021 using the command:
`./faust2sublimecompletions aanl.lib all.lib analyzers.lib basics.lib compressors.lib delays.lib demos.lib dx7.lib envelopes.lib fds.lib filters.lib hoa.lib interpolators.lib maths.lib mi.lib misceffects.lib oscillators.lib noises.lib phaflangers.lib platform.lib physmodels.lib quantizers.lib reducemaps.lib reverbs.lib routes.lib spats.lib signals.lib soundfiles.lib synths.lib vaeffects.lib version.lib webaudio.lib wdmodels.lib > faust.sublime-completions`

The libraries included above being these included in `stdfaust.lib`.