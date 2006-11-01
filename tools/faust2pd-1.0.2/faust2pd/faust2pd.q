#!/usr/bin/q --
#! -cmain

/* Copyright (c) 2006 by Albert Graef.

   This is free software; you can redistribute it and/or modify it under the
   terms of the GNU General Public License as published by the Free Software
   Foundation; either version 2, or (at your option) any later version.

   This software is distributed in the hope that it will be useful, but
   WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
   or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
   more details.

   You should have received a copy of the GNU General Public License along
   with this program; if not, write to the Free Software Foundation, Inc., 675
   Mass Ave, Cambridge, MA 02139, USA. */

var const VERSION = "1.0";

import faustxml;
private pcontrols X;

/* Needed Pd messages and objects. */

type PdObjects = const obj, msg, text, connect, coords, s, r, route,
  bng, tgl, nbx, hsl, vsl, hradio, vradio;

/* Merge subpatches. */

merge A B	= A++map (shift (nobjs A)) B;

shift N (connect X I Y J)
		= connect (X+N) I (Y+N) J;
shift _ X	= X otherwise;

nobjs OBJS	= #filter isobj OBJS;
isobj (F X)	= isobj F;
isobj obj	= true;
isobj msg	= true;
isobj text	= true;
isobj _		= false otherwise;

/* Move subpatches on the canvas. */

move DX DY OBJS:List
		= map (move DX DY) OBJS;
move DX DY (obj X Y)
		= obj (X+DX) (Y+DY);
move DX DY (msg X Y)
		= msg (X+DX) (Y+DY);
move DX DY (F X)
		= move DX DY F X;
move DX DY X	= X otherwise;

/* Write dsp and synth patches to a file. */

write_dsp XMLNAME OUTNAME
		= fputs F "#N canvas 0 0 450 300 10;\n" ||
		  do (write_obj F) OBJS
		    where INFO = info XMLNAME, (NAME|_) = INFO,
		      OUTNAME = if null OUTNAME then NAME++".pd" else OUTNAME,
		      F:File = fopen OUTNAME "w",
		      OBJS:List = make_dsp INFO;

write_synth N XMLNAME OUTNAME
		= fputs F "#N canvas 0 0 450 300 10;\n" ||
		  do (write_obj F) OBJS
		    where INFO = info XMLNAME, (NAME|_) = INFO,
		      OUTNAME = if null OUTNAME then NAME++".pd" else OUTNAME,
		      F:File = fopen OUTNAME "w",
		      OBJS:List = make_synth N INFO;

write_obj F X	= fprintf F "#X %s;\n" $ obj_str X;

obj_str (F X:String)
		= obj_str F if null X;
		= obj_str F++" \\"++X if X!0 = "$";
		= obj_str F++" "++X otherwise;
obj_str (F X:Num)
		= obj_str F++sprintf " %g" X otherwise;
obj_str (F X)	= obj_str F++" "++str X;
obj_str F	= str F otherwise;

/* Construct dsp and synth patches. */

comment Y	= [text 0 (Y+10) $ sprintf "Generated %s by faust2pd v%s. \
See http://faudiostream.sf.net and http://q-lang.sf.net."
		   (strftime "%c" $ localtime time,VERSION)];

make_dsp (NAME,DESCR,VERSION,IN,OUT,LAYOUT)
		= merge DSP CONTROLS++
		  (if null CONTROLS then []
		   else [coords 0 (-1) 1 1 X (Y-10) 1 0 0])++
		  comment Y
		    where CONTROLS = filter is_dsp_control $
		      pcontrols LAYOUT, K = #CONTROLS,
		      (X,Y,CONTROLS) = make_controls LAYOUT CONTROLS,
		      DSP = move 10 (Y+60) $
		      make_simple (NAME++"~") IN OUT;

make_synth N (NAME,DESCR,VERSION,IN,OUT,LAYOUT)
		= merge VOICES CONTROLS++
		  (if null CONTROLS then []
		   else [coords 0 (-1) 1 1 X (Y-10) 1 0 0])++
		  comment Y
		    where CONTROLS = filter is_voice_control $
		      pcontrols LAYOUT, K = #CONTROLS,
		      (X,Y,CONTROLS) = make_controls LAYOUT CONTROLS,
		      VOICES = move 10 (Y+60) $
		      make_voices (NAME++"~") OUT N;

// check for the "active" control which is treated specially
is_dsp_control C
		= (NAME<>"active")
		    where NAME = last $ split "/" $ control_label C;

// check for "active" and special voice controls (freq/gain/gate) which
// shouldn't be exposed in the GUI
is_voice_control C
		= not any (=NAME) ["active","freq","gain","gate"]
		    where NAME = last $ split "/" $ control_label C;

/* Create the dsp subpatch. */

make_simple DSP IN OUT
=						// -- objects --

  [obj (I*60) 0 "inlet~" :			// 0..IN-1	inlet~
   I in [1..IN]] ++
  [obj 0 0 "inlet",				// IN		inlet
   obj (max 2 (IN+1)*60) 0 r "$0-read",		// IN+1		r $0-read
   obj (max 2 (IN+1)*60) 30 "faust-control" "$0",//IN+2		faust-control $0
   obj (max 2 (IN+1)*60) 60 s "$0-write",	// IN+3		s $0-write
   obj 0 60 r "$0-in",				// IN+4		r $0-in
   obj 0 90 DSP,				// IN+5		DSP
   obj 0 120 s "$0-out"] ++			// IN+6		s $0-out
  [obj (I*60) 150 "outlet~" :			// IN+7..IN+7+OUT-1
   I in [1..OUT]] ++				//		outlet~
  [obj 0 150 "outlet"] ++			// IN+7+OUT	outlet

						// -- connections --

  [connect IN 0 (IN+2) 0,			// inlet -> faust-control
   connect (IN+1) 0 (IN+2) 0,			// r $0-read -> faust-control
   connect (IN+2) 0 (IN+3) 0,			// faust-control -> s $0-write
   connect (IN+5) 0 (IN+6) 0,			// DSP -> s $0-out
   connect IN 0 (IN+7+OUT) 0,			// inlet -> outlet
   connect (IN+4) 0 (IN+5) 0] ++		// r $0-in -> DSP
  [connect (I-1) 0 (IN+5) I :			// inlet~ -> DSP
   I in [1..IN]] ++
  [connect (IN+5) I (IN+7+I-1) 0 :		// DSP -> outlet~
   I in [1..OUT]];

/* Create the synth subpatch. */

make_voices DSP OUT N
=						// -- objects --

  [obj 0 0 "inlet",				// 0		inlet #1
   obj 120 0 "inlet",				// 1		inlet #2
   obj 180 0 r "$0-read",			// 2		r $0-read
   obj 120 30 r "$0-all",			// 3		r $0-all
   obj 180 30 "faust-control" "$0",		// 4		faust-control $0
   obj 180 60 s "$0-write",			// 5		s $0-write
   obj 120 60 r "$0-in",			// 6		r $0-in
   obj 120 ((N+1)*30+60) s "$0-out"] ++		// 7		s $0-out
  cat [[obj 0 (I*30+60) "faust-gate" I,		// 8,10..2*N+6	faust-gate 1..N
	obj 120 (I*30+60) DSP] :		// 9,11..2*N+7	DSP #1..N
       I in [1..N]] ++
  [obj (I*60+120) ((N+1)*30+90) "outlet~" :	// 2*N+8..2*N+8+OUT-1
   I in [0..OUT-1]] ++				//		outlet~ #1..N
  [obj 0 ((N+1)*30+90) "outlet"] ++		// 2*N+8+OUT	outlet

						// -- connections --

  [connect 1 0 4 0,				// inlet #2 -> faust-control
   connect 2 0 4 0,				// r $0-read -> faust-control
   connect 4 0 5 0,				// faust-control -> s $0-write
   connect 1 0 (2*N+8+OUT) 0,			// inlet #2 -> outlet
   connect 6 0 9 0,				// r $0-in -> DSP #1
   connect 9 0 7 0] ++				// DSP #1 -> s $0-out
  cat [[connect 0 0 (2*I+8) 0,			// inlet #1 -> faust-gate 1..N
	connect (2*I+8) 0 (2*I+9) 0,		// faust-gate 1..N -> DSP #1..N
	connect 3 0 (2*I+9) 0]:			// r $0-all -> DSP #1..N
       I in [0..N-1]] ++
  [connect (2*I+9) (J+1) (2*N+8+J) 0 :		// DSP #1..N -> outlet~ +1..N
   I in [0..N-1], J in [0..OUT-1]];

/* Create the GUI+controls subpatch. */

const var BLACK = -1, WHITE = -0x40000, GRAY = -0x38e39;

/* FIXME: The following is mostly guesswork, so you might have to customize
   this. Maybe these values should be configurable from the command line, or a
   better layout algorithm should be designed which also takes into account
   the widget labels. */

const var BUTTON_X = 50, BUTTON_Y = 30, NENTRY_X = 75, NENTRY_Y = 30,
  HSLIDER_X = 150, HSLIDER_Y = 30, VSLIDER_X = 50, VSLIDER_Y = 150;

make_controls LAYOUT CONTROLS
		= (X,Y,C)
		    if not null GUI
		    where (X,Y,GUI) = make_gui LAYOUT,
		      C = move (max 450 (X+30)) 10 $
		      make_control_objs CONTROLS,
		      C = merge GUI C;
		= (0,0,[]) otherwise;

/* Create the GUI subpatch. */

def FN1 = 8, FN2 = 10; // GUI font sizes

make_gui LAYOUT	= (X,Y,C++
		   [obj (X-38) 3 bng 15 250 50 1 "$0-init" "$0-ignore"
		    "empty" 0 (-6) 0 FN1 WHITE BLACK BLACK,
		    obj (X-18) 3 tgl 15 1 "$0-active" "$0-active"
		    "empty" 0 (-6) 0 FN1 WHITE BLACK BLACK 1 1])
		    if not null C
		    where (X,Y,C) = make_group "" (10,30) LAYOUT;
		= (0,0,[]) otherwise;

make_group PATH (X,Y) (tgroup X)
		= make_group PATH (X,Y) (hgroup X);
make_group PATH (X,Y) (hgroup (NAME,ITEMS))
		= //printf "end %s\n" $ join2 PATH $ mangle NAME ||
		  (X,Y,cat $ reverse C)
		    where (_,_,_,_,X,Y,C) =
		      //printf "hgroup %s\n" $ join2 PATH $ mangle NAME ||
		      foldl (hstep (make_group (join2 PATH (mangle NAME))))
		      (X,Y,X,Y,X,Y,[]) ITEMS;
make_group PATH (X,Y) (vgroup (NAME,ITEMS))
		= //printf "end %s\n" $ join2 PATH $ mangle NAME ||
		  (X,Y,cat $ reverse C)
		    where (_,_,_,_,X,Y,C) =
		      //printf "vgroup %s\n" $ join2 PATH $ mangle NAME ||
		      foldl (vstep (make_group (join2 PATH (mangle NAME))))
		      (X,Y,X,Y,X,Y,[]) ITEMS;
make_group PATH (X,Y) ITEM
		= //printf "%s [%s] item %s\n" (str (X,Y),PATH,str ITEM) ||
		  add_widget PATH (X,Y) ITEM;

hstep F (X0,Y0,X1,Y1,X2,Y2,C) ITEM
		= hbreak F (X0,Y0,X1,Y1,X2,Y2,C) ITEM (X,Y,C1)
		    where (X,Y,C1) = F (X1,Y1) ITEM;
hbreak F (X0,Y0,X1,Y1,X2,Y2,C) ITEM (X,Y,C1)
		= (X0,Y0,X,Y1,max X2 X,max Y2 Y,[C1|C])
		    if (WIDTH<=0) or else (X<=WIDTH) or else (X1<=X0);
		= hbreak F (X0,Y0,X0,Y2,X2,Y2,C) ITEM (F (X0,Y2) ITEM);
vstep F (X0,Y0,X1,Y1,X2,Y2,C) ITEM
		= vbreak F (X0,Y0,X1,Y1,X2,Y2,C) ITEM (X,Y,C1)
		    where (X,Y,C1) = F (X1,Y1) ITEM;
vbreak F (X0,Y0,X1,Y1,X2,Y2,C) ITEM (X,Y,C1)
		= (X0,Y0,X1,Y,max X2 X,max Y2 Y,[C1|C])
		    if (HEIGHT<=0) or else (Y<=HEIGHT) or else (Y1<=Y0);
		= vbreak F (X0,Y0,X2,Y0,X2,Y2,C) ITEM (F (X2,Y0) ITEM);

checkname NAME	= "empty" if null NAME;
		= NAME otherwise;

match_control PATH NAME PAT
		= fnmatch PAT (join2 PATH NAME) if pos "/" PAT >= 0;
		= fnmatch PAT NAME otherwise;

add_widget PATH (X,Y) ITEM
		= (X,Y,[])
		    if null (join2 PATH NAME) or else
		      any (match_control PATH NAME) EXCLUDE
		    where NAME = mangle $ control_label ITEM;
add_widget PATH (X,Y) (button NAME)
		= add_widget PATH (X,Y) (checkbox NAME) if FAKE_BUTTONS_FLAG;
add_widget PATH (X,Y) (button NAME)
		= (X+BUTTON_X,Y+BUTTON_Y,
		   [obj X Y bng 15 250 50 0 S S
		    NAME 0 (-6) 0 FN1 WHITE BLACK BLACK])
		    where NAME = mangle NAME,
		      S = control_sym $ join2 PATH NAME,
		      NAME = checkname NAME
		    if (NVOICES=0) or else
		      not any (=NAME) ["freq","gain","gate"];
add_widget PATH (X,Y) (checkbox NAME)
		= (X+BUTTON_X,Y+BUTTON_Y,
		   [obj X Y tgl 15 0 S S
		    NAME 0 (-6) 0 FN1 WHITE BLACK BLACK 0 1])
		    where NAME = mangle NAME,
		      S = control_sym $ join2 PATH NAME,
		      NAME = checkname NAME
		    if (NVOICES=0) or else
		      not any (=NAME) ["freq","gain","gate"];
add_widget PATH (X,Y) (nentry (NAME,INIT,MIN,MAX|_))
		= (X+NENTRY_X,Y+NENTRY_Y,
		   [obj X Y nbx 5 14 MIN MAX 0 0 S S
		    NAME 0 (-6) 0 FN2 WHITE BLACK BLACK 256])
		    where NAME = mangle NAME,
		      S = control_sym $ join2 PATH NAME,
		      NAME = checkname NAME
		    if (NVOICES=0) or else
		      not any (=NAME) ["freq","gain","gate"];
add_widget PATH (X,Y) (hslider (NAME,INIT,MIN,MAX,STEP|_))
		= if (RADIO_SLIDERS>0) and then (MIN=0) and then
		    (STEP=1) and then (MAX<RADIO_SLIDERS) then
		    (X+max HSLIDER_X (RADIO_SLIDERS*15),Y+HSLIDER_Y,
		     [obj X Y hradio 15 1 0 (MAX+1) S S
		      NAME 0 (-6) 0 FN1 WHITE BLACK BLACK 0])
		  else if SLIDER_NUMS_FLAG then
		    (X+HSLIDER_X+NENTRY_X,Y+HSLIDER_Y,
		     [obj X Y hsl 128 15 MIN MAX 0 0 S S
		      NAME (-2) (-6) 0 FN1 WHITE BLACK BLACK 0 1,
		      obj (X+HSLIDER_X) Y nbx 5 14 MIN MAX 0 0 S S
		      "empty" 0 (-6) 0 FN2 WHITE BLACK BLACK 256])
		  else
		    (X+HSLIDER_X,Y+HSLIDER_Y,
		     [obj X Y hsl 128 15 MIN MAX 0 0 S S
		      NAME (-2) (-6) 0 FN1 WHITE BLACK BLACK 0 1])
		    where NAME = mangle NAME,
		      S = control_sym $ join2 PATH NAME,
		      NAME = checkname NAME
		    if (NVOICES=0) or else
		      not any (=NAME) ["freq","gain","gate"];
add_widget PATH (X,Y) (vslider (NAME,INIT,MIN,MAX,STEP|_))
		= if (RADIO_SLIDERS>0) and then (MIN=0) and then
		    (STEP=1) and then (MAX<RADIO_SLIDERS) then
		    (X+VSLIDER_X,Y+max VSLIDER_Y (RADIO_SLIDERS*15),
		     [obj X Y vradio 15 1 0 (MAX+1) S S
		      NAME 0 (-6) 0 FN1 WHITE BLACK BLACK 0])
		  else if SLIDER_NUMS_FLAG then
		    (X+NENTRY_X,Y+VSLIDER_Y+NENTRY_Y,
		     [obj X Y vsl 15 128 MIN MAX 0 0 S S
		      NAME 0 (-8) 0 FN1 WHITE BLACK BLACK 0 1,
		      obj X (Y+VSLIDER_Y-10) nbx 5 14 MIN MAX 0 0 S S
		      "empty" 0 (-6) 0 FN2 WHITE BLACK BLACK 256])
		  else
		    (X+VSLIDER_X,Y+VSLIDER_Y,
		     [obj X Y vsl 15 128 MIN MAX 0 0 S S
		      NAME 0 (-8) 0 FN1 WHITE BLACK BLACK 0 1])
		    where NAME = mangle NAME,
		      S = control_sym $ join2 PATH NAME,
		      NAME = checkname NAME
		    if (NVOICES=0) or else
		      not any (=NAME) ["freq","gain","gate"];
add_widget PATH (X,Y) (hbargraph (NAME,MIN,MAX|_))
		= if SLIDER_NUMS_FLAG then
		    (X+HSLIDER_X+NENTRY_X,Y+HSLIDER_Y,
		     [obj X Y hsl 128 15 MIN MAX 0 0 S S
		      NAME (-2) (-6) 0 FN1 GRAY BLACK BLACK 0 1,
		      obj (X+HSLIDER_X) Y nbx 5 14 MIN MAX 0 0 S S
		      "empty" 0 (-6) 0 FN2 GRAY BLACK BLACK 256])
		  else
		    (X+HSLIDER_X,Y+HSLIDER_Y,
		     [obj X Y hsl 128 15 MIN MAX 0 0 S S
		      NAME (-2) (-6) 0 FN1 GRAY BLACK BLACK 0 1])
		    where NAME = mangle NAME,
		      S = control_sym $ join2 PATH NAME,
		      NAME = checkname NAME
		    if (NVOICES=0) or else
		      not any (=NAME) ["freq","gain","gate"];
add_widget PATH (X,Y) (vbargraph (NAME,MIN,MAX|_))
		= if SLIDER_NUMS_FLAG then
		    (X+NENTRY_X,Y+VSLIDER_Y+NENTRY_Y,
		     [obj X Y vsl 15 128 MIN MAX 0 0 S S
		      NAME 0 (-8) 0 FN1 GRAY BLACK BLACK 0 1,
		      obj X (Y+VSLIDER_Y-10) nbx 5 14 MIN MAX 0 0 S S
		      "empty" 0 (-6) 0 FN2 GRAY BLACK BLACK 256])
		  else
		    (X+VSLIDER_X,Y+VSLIDER_Y,
		     [obj X Y vsl 15 128 MIN MAX 0 0 S S
		      NAME 0 (-8) 0 FN1 GRAY BLACK BLACK 0 1])
		    where NAME = mangle NAME,
		      S = control_sym $ join2 PATH NAME,
		      NAME = checkname NAME
		    if (NVOICES=0) or else
		      not any (=NAME) ["freq","gain","gate"];
add_widget _ (X,Y) _
		= (X,Y,[]) otherwise;

/* Create the control objects and wiring. */

make_control_objs CONTROLS
		= [obj 0 0 r "$0-init",
		   obj DX 0 s (if NVOICES>0 then "$0-all" else "$0-in"),
		   obj (DX+DX div 2) 0 s "$0-read",
		   obj (2*DX) 0 r "$0-write"] ++ C
		    where CONTROLS = [checkbox "active"|CONTROLS],
		      DX = foldl max 0 $ map ((#).control_label) CONTROLS,
		      DX = (DX+7)*8,
		      (_,C) = foldl (control_objs DX) (0,[]) CONTROLS;

control_objs DX (J,C) (button NAME)
		= control_objs DX (J,C) (checkbox NAME) if FAKE_BUTTONS_FLAG;
control_objs DX (J,C) (button NAME)
		= (J+1,C++button_control_objs DX J NAME S 0)
		    where S = control_sym NAME;
control_objs DX (J,C) (checkbox "active")
		= (J+1,C++activate_control_objs DX J "active" S 1)
		    where S = control_sym "active";
control_objs DX (J,C) (checkbox NAME)
		= (J+1,C++active_control_objs DX J NAME S 0)
		    where S = control_sym NAME;
control_objs DX (J,C) (nentry (NAME,INIT|_))
		= (J+1,C++active_control_objs DX J NAME S INIT)
		    where S = control_sym NAME;
control_objs DX (J,C) (hslider (NAME,INIT|_))
		= (J+1,C++active_control_objs DX J NAME S INIT)
		    where S = control_sym NAME;
control_objs DX (J,C) (vslider (NAME,INIT|_))
		= (J+1,C++active_control_objs DX J NAME S INIT)
		    where S = control_sym NAME;
control_objs DX (J,C) (hbargraph (NAME|_))
		= (J+1,C++passive_control_objs DX J NAME S 0)
		    where S = control_sym NAME;
control_objs DX (J,C) (vbargraph (NAME|_))
		= (J+1,C++passive_control_objs DX J NAME S 0)
		    where S = control_sym NAME;
control_objs _ (J,C) _
		= (J,C) otherwise;

control_sym NAME
		= sprintf "$0-%s" $ sub NAME 1 (#NAME-1) if NAME!0="/";
		= sprintf "$0-%s" NAME otherwise;

activate_control_objs DX J NAME S INIT
		= [msg 0 ((2*J+1)*20) INIT,
		   obj 0 ((2*J+2)*20) s S,
		   //connect 0 0 (6*J+4) 0,
		   connect (6*J+4) 0 (6*J+5) 0,
		   obj DX ((2*J+1)*20) r S,
		   msg DX ((2*J+2)*20) NAME "$1",
		   connect (6*J+6) 0 (6*J+7) 0,
		   connect (6*J+7) 0 1 0,
		   obj (2*DX) ((2*J+1)*20) route NAME,
		   obj (2*DX) ((2*J+2)*20) s S,
		   connect (if J>0 then 6*J+2 else 3)
		   (if J>0 then 1 else 0) (6*J+8) 0,
		   connect (6*J+8) 0 (6*J+9) 0];

active_control_objs DX J NAME S INIT
		= [msg 0 ((2*J+1)*20) INIT,
		   obj 0 ((2*J+2)*20) s S,
		   connect 0 0 (6*J+4) 0,
		   connect (6*J+4) 0 (6*J+5) 0,
		   obj DX ((2*J+1)*20) r S,
		   msg DX ((2*J+2)*20) NAME "$1",
		   connect (6*J+6) 0 (6*J+7) 0,
		   connect (6*J+7) 0 1 0,
		   obj (2*DX) ((2*J+1)*20) route NAME,
		   obj (2*DX) ((2*J+2)*20) s S,
		   connect (if J>0 then 6*J+2 else 3)
		   (if J>0 then 1 else 0) (6*J+8) 0,
		   connect (6*J+8) 0 (6*J+9) 0];

button_control_objs DX J NAME S INIT
		= [msg 0 ((2*J+1)*20) INIT,
		   obj 0 ((2*J+2)*20) "faust-s" S,
		   connect 0 0 (6*J+4) 0,
		   connect (6*J+4) 0 (6*J+5) 0,
		   obj DX ((2*J+1)*20) r S,
		   obj DX ((2*J+2)*20) "faust-r" NAME,
		   connect (6*J+6) 0 (6*J+7) 0,
		   connect (6*J+7) 0 1 0,
		   obj (2*DX) ((2*J+1)*20) route NAME,
		   obj (2*DX) ((2*J+2)*20) "faust-s" S,
		   connect (if J>0 then 6*J+2 else 3)
		   (if J>0 then 1 else 0) (6*J+8) 0,
		   connect (6*J+8) 0 (6*J+9) 0];

passive_control_objs DX J NAME S INIT
		= [msg 0 ((2*J+1)*20) INIT,
		   obj 0 ((2*J+2)*20) s S,
		   connect 0 0 (6*J+4) 0,
		   connect (6*J+4) 0 (6*J+5) 0,
		   obj DX ((2*J+1)*20) "faust-timer" "$0",
		   msg DX ((2*J+2)*20) NAME,
		   connect (6*J+6) 0 (6*J+7) 0,
		   connect (6*J+7) 0 2 0,
		   obj (2*DX) ((2*J+1)*20) route NAME,
		   obj (2*DX) ((2*J+2)*20) s S,
		   connect (if J>0 then 6*J+2 else 3)
		   (if J>0 then 1 else 0) (6*J+8) 0,
		   connect (6*J+8) 0 (6*J+9) 0];

/* Make control names as in faustxml.q but with name mangling and "/" in
   front. */

mangle S	= join "-" $ filter (neg null) $
		  regex "g" "[^a-zA-Z0-9]+" S regskip ++ [regskip];

pcontrols X:Control
		= filter ((<>"/").control_label) $ controls2 "" X;

join2 "" S	= "/"++S;
join2 S ""	= S;
join2 S T	= S++"/"++T otherwise;

controls2 PATH X:Control
		= cat (map (controls2 (join2 PATH LBL)) CTRLS)
		    where F (LBL:String,CTRLS:List) = X,
		      LBL = mangle LBL;
		= [F (join2 PATH LBL|ARGS)]
		    where F (LBL:String|ARGS:Tuple) = X,
		      LBL = mangle LBL;
		= [F (join2 PATH LBL)]
		    where F LBL:String = X,
		      LBL = mangle LBL;

/* main program */

import getopt;

def OPTS        = [("--help", "-h", NOARG),
		   ("--version", "-V", NOARG),
		   ("--fake-buttons", "-f", NOARG),
		   ("--slider-nums", "-s", NOARG),
		   ("--radio-sliders", "-r", REQARG),
		   ("--nvoices", "-n", REQARG),
		   ("--width", "-x", REQARG),
		   ("--height", "-y", REQARG),
		   ("--exclude", "-X", REQARG),
		   ("--output-file", "-o", REQARG)];

def [PROG|MYARGS] = ARGS;
//def MYARGS = ["-n","8","organ.dsp.xml","-x","160"];

def (MYOPTS,MYARGS) = catch invalid_option $ getopt OPTS MYARGS,
  MYOPTS = dict MYOPTS, HELP_FLAG = member MYOPTS "--help",
  VERSION_FLAG = member MYOPTS "--version",
  FAKE_BUTTONS_FLAG = member MYOPTS "--fake-buttons",
  SLIDER_NUMS_FLAG = member MYOPTS "--slider-nums",
  [RADIO_SLIDERS,NVOICES,HEIGHT,WIDTH] = map get_int
  ["--radio-sliders","--nvoices","--height","--width"],
  EXCLUDE = get_set "--exclude",
  _ = if (#MYARGS<>1) and then not VERSION_FLAG or else HELP_FLAG then
        print_usage PROG,
  _ = if VERSION_FLAG then print_version,
  [XMLNAME|_] = MYARGS;

def OUTNAME = if member MYOPTS "--output-file" then
                MYOPTS!"--output-file"
              else (),
  _ = if eq OUTNAME XMLNAME then
        (fputs ERROR "output would overwrite source file, aborting\n" ||
	 exit 1);

invalid_option OPT
		= fprintf ERROR "%s: invalid option %s\n" (PROG,OPT) ||
		  exit 1;

get_set OPT	= split "," VAL where VAL:String = MYOPTS!OPT;
		= [] otherwise;
get_int OPT	= check_int OPT VAL where VAL:String = MYOPTS!OPT;
		= 0 otherwise;
check_int OPT VAL
		= N if N>0 where 'N:Int = valq VAL;
		= fprintf ERROR "%s: invalid option value %s %s\n"
		  (PROG,OPT,VAL) ||
		  exit 1;

print_usage PROG
		= printf
"faust2pd version %s, Copyright (c) 2006 by Albert Graef\n\
Usage: %s [-hVfs] [-o output-file] [-n #voices] [-r max] \n\
  [-X patterns] [-x width] [-y height] input-file\n\
Options:\n\
-h, --help          display this help message and exit\n\
-V, --version       display the version number and exit\n\
-f, --fake-buttons  replace buttons (bangs) with checkboxes (toggles)\n\
-n, --nvoices       create a synth patch with the given number of voices\n\
-o, --output-file   output file name (`.pd' file)\n\
-r, --radio-sliders radio controls for sliders with values 0..max-1\n\
-s, --slider-nums   sliders with additional number control\n\
-X, --exclude       exclude controls matching the given glob patterns\n\
-x, --width         maximum width of the GUI area\n\
-y, --height        maximum height of the GUI area\n\
input-file          input file name (`.dsp.xml' file)\n\
Default output-file is input-file with new extension `.pd'.\n"
		  (VERSION,PROG) || exit 0;

print_version	= printf
"faust2pd version %s, Copyright (c) 2006 by Albert Graef\n" VERSION ||
		  exit 0;

main		= catch mainerr mainprog || exit 0;
mainerr MSG:String
		= fprintf ERROR "%s: %s\n" (PROG,MSG) || exit 1;
mainerr _	= fprintf ERROR "%s: unknown error\n" PROG || exit 1;
mainprog	= write_synth NVOICES XMLNAME OUTNAME if NVOICES>0;
		= write_dsp XMLNAME OUTNAME otherwise;
