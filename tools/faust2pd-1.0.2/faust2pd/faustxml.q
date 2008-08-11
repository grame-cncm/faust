
/* faustxml.q: Determine the description of a Faust DSP from its XML file. */

import dict, system, xml;

/* The Control type is used to represent the UI controls of Faust DSPs. The
   elements are the same as for the Control type in the Q-Faust module, minus
   the REF arguments. */

public type Control = const button ARGS, checkbox ARGS, nentry ARGS,
  vslider ARGS, hslider ARGS, vbargraph ARGS, hbargraph ARGS,
  vgroup ARGS, hgroup ARGS, tgroup ARGS;

public control_type X, control_name X, control_label X, control_args X;

control_type X:Control	= F where F ARGS = X;
control_label X:Control	= LBL where F (LBL|ARGS) = X;
control_label X:Control	= LBL where F LBL:String = X;
control_args X:Control	= ARGS where F (LBL|ARGS) = X;
control_args X:Control	= () where F LBL:String = X;

/* The following function returns a flat representation of a control group as
   a list of basic control descriptions, which provides a quick way to access
   all the control values of a Faust DSP. The grouping controls themselves are
   omitted. */

public controls X;

controls X:Control	= cat (map controls CTRLS)
			    where F (_,CTRLS:List) = X;
			= [X] otherwise;

/* The following function works like the controls function above, but also
   replaces the label of each basic control with a fully qualified path
   consisting of all control labels leading up to the given control. Thus,
   e.g., the label of a slider "gain" inside a group "voice#0" inside the
   main "faust" group will be denoted by the label "faust/voice#0/gain". */

public pcontrols X;

private join2 S T, controls2 PATH X;

join2 "" S		= S;
join2 S ""		= S;
join2 S T		= S++"/"++T otherwise;

controls2 PATH X:Control
			= cat (map (controls2 (join2 PATH LBL)) CTRLS)
			    where F (LBL:String,CTRLS:List) = X;
			= [F (join2 PATH LBL|ARGS)]
			    where F (LBL:String|ARGS:Tuple) = X;
			= [F (join2 PATH LBL)]
			    where F LBL:String = X;

pcontrols X:Control	= controls2 "" X;

/* Generate a tree representation of an entire XML document, or the subtree of
   an XML document rooted at a given node. */

type Node = const node INFO CHILDREN;

private tree X;
tree DOC:XMLDoc		= tree (xml_root DOC);
tree NODE:XMLNode	= node (xml_node_info NODE) $ map tree $
			  filter (neg xml_is_blank_node) (xml_children NODE);

// determine the basename of a file (strip off path and extension)

private basename S;
basename S	= S where S:String = last $ split "/" S,
		      S:String = hd $ split "." S;
		= S otherwise;

// remove leading and trailing whitespace

private trim S;
trim S		= S where [S] = regex ""
		      "^[ \t\n]*((.|\n)*[^ \t\n])[ \t\n]*$" S (reg 1);
		= S otherwise;

/* Extract the description of a Faust DSP from its XML file. Returns the name,
   description and version of the DSP, as well as the control descriptions.
   Raises an exception if the XML file doesn't exist or doesn't contain valid
   contents. */

public info FNAME;
private parse DOC, parse_doc INFO;

info FNAME	= (NAME,DESCR|INFO)
		    where DOC:XMLDoc = xml_load_file FNAME 0,
		      NAME = basename FNAME, (DESCR|INFO) = parse DOC,
		      DESCR = if null DESCR then NAME else DESCR;
		= throw "could not open XML file" otherwise;

parse DOC	= parse_doc (NAME,VERSION,IN,OUT,ACTIVE++PASSIVE,LAYOUT)
		    where [[NAME],[VERSION],[IN],[OUT],
			   ACTIVE,PASSIVE,LAYOUT] =
		      map (map tree . xml_select DOC)
		      ["/faust/name","/faust/version",
		       "/faust/inputs","/faust/outputs",
		       "/faust/ui/activewidgets/widget",
		       "/faust/ui/passivewidgets/widget",
		       "/faust/ui/layout/group"];
		= throw "invalid XML data" otherwise;

private str_val S;

str_val S:String
		= S where 'S:String = valq S;
		= S otherwise;

private parse_node X, parse_prop S, parse_control X, parse_group CD X;

parse_doc (node (element "name" _ _) NAME,
	   node (element "version" _ _) VERSION,
	   node (element "inputs" _ _) IN,
	   node (element "outputs" _ _) OUT,
	   CONTROLS,LAYOUT)
= (NAME,VERSION,IN,OUT,CONTROLS)
    where [NAME,VERSION,IN,OUT] = map parse_node [NAME,VERSION,IN,OUT],
      [NAME,VERSION] = map (parse_prop.trim) [NAME,VERSION],
      IN:Int = val IN, OUT:Int = val OUT,
      CONTROLS = map parse_control CONTROLS,
      [CONTROLS] = map (parse_group (dict CONTROLS)) LAYOUT;
parse_doc _ = throw "invalid XML data" otherwise;

parse_node [node (text S:String) _]
		= S;
parse_node []	= "";
parse_node _	= throw "invalid XML data" otherwise;

parse_prop "Unknow" // sic!
		= "";
parse_prop "Unknown"
		= "";
parse_prop S:String
		= str_val S;
parse_prop _	= "" otherwise;

private param X, make_control ID TYPE LABEL PARAMS;

parse_control (node (element "widget" _ ATTRS) PARAMS)
= make_control ID TYPE LABEL PARAMS
    where ATTRS = dict ATTRS, PARAMS = dict $ map param PARAMS,
      TYPE:String = ATTRS!"type", ID:Int = val $ ATTRS!"id",
      LABEL:String = str_val $ PARAMS!"label";
parse_control _ = throw "invalid XML data" otherwise;

param (node (element NAME:String _ _) VAL)
= (NAME,VAL) where VAL:String = parse_node VAL;
param _ _ = throw "invalid XML data" otherwise;

make_control ID TYPE LABEL PARAMS
= (ID,C) where C:Control = (val $ "faustxml::"++TYPE) LABEL
    if any (=TYPE) ["button","checkbox"];
= (ID,C) where [INIT:Num,MIN:Num,MAX:Num,STEP:Num] =
      map (flip sscanf "%lg".(PARAMS!)) ["init","min","max","step"],
      C:Control = (val $ "faustxml::"++ TYPE) (LABEL,INIT,MIN,MAX,STEP)
    if any (=TYPE) ["vslider","hslider","nentry"];
= (ID,C) where [MIN:Num,MAX:Num] =
      map (flip sscanf "%lg".(PARAMS!)) ["min","max"],
      C:Control = (val $ "faustxml::"++ TYPE) (LABEL,MIN,MAX)
    if any (=TYPE) ["vbargraph","hbargraph"];
make_control _ _ _ _ = throw "invalid XML data" otherwise;

private make_group CD TYPE X;

parse_group CD (node (element "group" _ ATTRS) PARAMS)
= make_group CD TYPE PARAMS
    where ATTRS = dict ATTRS, TYPE:String = ATTRS!"type";
parse_group CD (node (element "widgetref" _ [("id",ID)]) [])
= C where ID:Int = val ID, C:Control = CD!ID;
parse_group _ _ = throw "invalid XML data" otherwise;

make_group CD TYPE
[node (element "label" _ _) LABEL|PARAMS]
= C where LABEL:String = parse_node LABEL,
      C:Control = (val $ "faustxml::"++ TYPE)
      (str_val LABEL,map (parse_group CD) PARAMS);
make_group _ _ _ = throw "invalid XML data" otherwise;
