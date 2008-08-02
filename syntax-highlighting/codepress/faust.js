/*
 * CodePress regular expressions for Faust syntax highlighting (derived from Java)
 */
 
// Faust
Language.syntax = [
	{ input : /\"(.*?)(\"|<br>|<\/P>)/g, output : '<s>"$1$2</s>'}, // strings double quote
    { input : /\b(component|mem|prefix|int|float|rdtable|rwtable|select2|select3|ffunction|fconstant|fvariable|button|checkbox|vslider|hslider|nentry|vbargraph|hbargraph|attach|acos|asin|atan|atan2|cos|sin|tan|exp|log|log10|pow|sqrt|abs|min|max|fmod|remainder|floor|ceil|rint)\b/g, output : '<b>$1</b>'},
    { input : /\b(process|with|case|seq|par|sum|prod|import|vgroup|hgroup|tgroup|declare)\b/g, output : '<u>$1</u>'},
    { input : /(&lt;:|:&gt;|,|:)/g, output : '<al>$1</al>'},
    { input : /(~)/g, output : '<al>$1</al>'},
    { input : /([^:]|^)\/\/(.*?)(<br|<\/P)/g, output : '$1<i>//$2</i>$3'}, // comments //
	{ input : /\/\*(.*?)\*\//g, output : '<i>/*$1*/</i>' } // comments /* */
]



Language.snippets = []

Language.complete = [
	{ input : '\'',output : '\'$0\'' },
	{ input : '"', output : '"$0"' },
	{ input : '(', output : '\($0\)' },
	{ input : '[', output : '\[$0\]' },
	{ input : '{', output : '{\n\t$0\n}' }		
]

Language.shortcuts = []
