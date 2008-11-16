/*
 * CodePress regular expressions for Faust syntax highlighting (derived from Java)
 */
 
// Faust
Language.syntax = [
	{ input : /\"(.*?)(\"|<br>|<\/P>)/g, output : '<s>"$1$2</s>'}, // strings double quote
    { input : /\b(component|library|environment|mem|prefix|int|float|rdtable|rwtable|select2|select3|ffunction|fconstant|fvariable|button|checkbox|vslider|hslider|nentry|vbargraph|hbargraph|attach|acos|asin|atan|atan2|cos|sin|tan|exp|log|log10|pow|sqrt|abs|min|max|fmod|remainder|floor|ceil|rint)\b/g, output : '<b>$1</b>'},
    { input : /\b(process|with|case|seq|par|sum|prod|import|vgroup|hgroup|tgroup|declare)\b/g, output : '<u>$1</u>'},
    { input : /(&lt;:|:&gt;|,|:)/g, output : '<al>$1</al>'},
    { input : /(~)/g, output : '<al>$1</al>'},
    { input : /([^:]|^)\/\/(.*?)(<br|<\/P)/g, output : '$1<i>//$2</i>$3'}, // comments //
	{ input : /\/\*(.*?)\*\//g, output : '<i>/*$1*/</i>' } // comments /* */
]



Language.snippets = [
    // program and definitions
    { input : 'pr', output : 'process = $0;' },
    { input : 'im', output : 'import("$0.lib");' },
    { input : 'co', output : 'component("$0.dsp")' },
    { input : 'li', output : 'library("$0.dsp")' },
    { input : 'en', output : 'environment {$0}' },
    { input : 'wi', output : 'with {$0}' },

    // pattern matching
    { input : 'ca', output : 'case {$0}' },
    { input : 'ru', output : '($0) => ...;' },
    
    // declaration
    { input : 'de', output : 'declare $0 \t"";' },
    { input : 'dn', output : 'declare name "$0";' },
    { input : 'da', output : 'declare author "$0";' },
    { input : 'dl', output : 'declare license "$0";' },
    { input : 'dv', output : 'declare version "$0";' },

    // user interface
    { input : 'bu', output : 'button("$0")' },
    { input : 'ch', output : 'checkbox("$0")' },

    { input : 'hs', output : 'hslider("$0", 50, 0, 100, 0.1)' },
    { input : 'vs', output : 'vslider("$0", 50, 0, 100, 0.1)' },
    { input : 'ne', output : 'nentry ("$0", 50, 0, 100, 0.1)' },

    { input : 'hb', output : 'hbargraph("$0", 0, 100)' },
    { input : 'vb', output : 'vbargraph("$0", 0, 100)' },

    { input : 'vg', output : 'vgroup("$0", ...)' },
    { input : 'hg', output : 'hgroup("$0", ...)' },
    { input : 'tg', output : 'tgroup("$0", ...)' },

    // iterations
    { input : 'pa', output : 'par(i, $0, ...)' },
    { input : 'su', output : 'sum(i, $0, ...)' },
    { input : 'se', output : 'seq(i, $0, ...)' },
    { input : 'mu', output : 'prod(i, $0, ...)' },

]

Language.complete = [
	{ input : '\'',output : '\'$0\'' },
	{ input : '"', output : '"$0"' },
	{ input : '(', output : '\($0\)' },
	{ input : '[', output : '\[$0\]' },
	{ input : '{', output : '{\n\t$0\n}' }		
]

Language.shortcuts = []
