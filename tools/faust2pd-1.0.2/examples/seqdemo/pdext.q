
/* A basic Pd/Q pattern sequencing example. This Q script generates the
   sequences played by the seqdemo.pd patch. */

import pd;

/* In this example, the patterns are simply sequences of note numbers with
   certain random elements. We use either lists or streams to represent those
   sequences. In Q, lists and streams share pretty much the same operations,
   so we can freely switch between the two representations and choose the one
   that is most appropriate in a given circumstance. A list must always be
   finite and all its elements are computed at the time the list is
   evaluated. In contrast, a stream is evaluated lazily and can thus be used
   to represent an infinite sequence whose members are computed "on the fly".

   The repeat function (defined in the standard Q library) generates a stream
   which consists of an infinite number of replications of the same
   element. The repeatn function does the same but produces a finite stream of
   a given size. In both cases the stream members are evaluated "on demand" as
   they are accessed during a traversal of the stream. In this example the
   definition of the members involves random elements which are recomputed
   each time the members are accessed, thus each traversal of the stream
   actually produces a new melody.

   The choose function defined below returns a random element of a list or
   finite stream. This and the random size arguments of the calls of the
   repeatn function are the random elements of the patterns which are
   responsible for the fact that a new melody is produced each time the
   patterns are traversed.

   In our implementation (which was inspired by SuperCollider's sequencing
   framework) patterns can be nested to an arbitrary depth. That is, a pattern
   can be a list or stream of lists or streams etc. When playing back the
   sequence we just "flatten" the pattern stream to a single stream of note
   numbers. This is done by the squash function defined below. Note that when
   it is applied to a stream, squash also works in a lazy manner, so the
   squashing of the stream is done on demand as well.

   The final ingredient of the sequencing algorithm is the event function
   (defined at the end of this file) which is applied to each stream member
   using the standard library function map. The event function is responsible
   for generating the actual sequences of Pd messages which are output by the
   sequencer object for each stream member. Again, the actual computation
   happens when accessing the stream members.

   The nice thing about Q is that we don't really have to worry about the
   "lazy" aspects of the computation when writing down the algorithm. We just
   compose the sequence in a straightforward fashion using standard list and
   stream functions, as if we were dealing with a finite sequence to be
   computed beforehand. All the on-demand evaluation is handled transparently
   by the Q interpreter. */

choose Xs	= Xs!rand 0 (#Xs-1);

squash Xs:List	= streamcat $ map squash Xs;
squash Xs:Stream
		= streamcat $ map squash Xs;
squash X	= {X} otherwise;

/* Random numbers. */

rand N M	= random mod (M-N+1)+N;

/* Sample patterns. pat1 is shamelessly pilfered from the SuperCollider
   documentation, pat2 is a finite section of pat1, and pat3 is a simple
   random C minor arpeggio. */

pat1		= repeat
		  [[24, 31, 36, 43, 48, 55],
		   repeatn (rand 2 5)
		   [60, choose [63, 65], 67, choose [70, 72, 74]],
		   repeatn (rand 3 9) (choose [74, 75, 77, 79, 81])];
pat2		= repeatn (rand 2 5)
		  [[24, 31, 36, 43, 48, 55],
		   repeatn (rand 2 5)
		   [60, choose [63, 65], 67, choose [70, 72, 74]],
		   repeatn (rand 3 9) (choose [74, 75, 77, 79, 81])];
pat3		= repeat [60,60,choose [63,67]];

/* The sequencer object. This is just some wrapper code around the actual
   sequencer function which is necessary to interface with Pd. See the Pd/Q
   documentation for details on how to do this. */

sequencer	= varargs make_seq;

make_seq [PAT:Stream,DUR:Num]
		= seq (DUR,TIME,ref SEQ,ref SEQ)
		    where DUR = ref DUR, TIME = ref 0, CTR = ref 0,
		      SEQ = map (event DUR TIME CTR) (squash PAT);
make_seq [PAT:Stream]
		= make_seq [PAT,500];
make_seq _	= make_seq [pat1];

/* The sequencing function. This is executed each time the sequencer object
   receives a message in Pd. Here we respond to the messages "bang" (produce
   the next stream member), "reset" (rewind the stream to the beginning),
   numbers (change the note duration a.k.a. delta time value) and a pattern
   (to switch patterns on the fly). The function also keeps track of a few
   state variables implemented as references (which are a kind of pointers to
   values in Q): DUR (current note duration in msec, smaller values indicate a
   higher tempo), TIME (time offset of the next event in msec; this is 0
   initially and then becomes equal to DUR as soon as the first note is
   output), SEQ (the remainder of the sequence to be played) and SEQ0 (the
   entire sequence; we need this when we have to rewind the stream in response
   to a "reset" message). Last but not least we also send back a "stop"
   message when the stream ends (of course this will only happen if the
   sequence is finite). */

type PdSeqMsg = const note, pan, wet, stop;

seq (DUR,TIME,SEQ,SEQ0) (float X:Num)
		= put DUR X;
seq (DUR,TIME,SEQ,SEQ0) PAT:Stream
		= put SEQ SEQ1 || put SEQ0 SEQ1 || put TIME 0
		    where CTR = ref 0,
		      SEQ1 = map (event DUR TIME CTR) (squash PAT);
seq (DUR,TIME,SEQ,SEQ0) reset
		= put SEQ (get SEQ0) || put TIME 0;
seq (DUR,TIME,SEQ,SEQ0) bang
		= put SEQ SEQ1 || put TIME (get DUR) || EV
		    where {EV|SEQ1} = get SEQ;
seq _ _		= stop;

/* Turn a stream member (a note number in this case) into a sequence of events
   (a.k.a. Pd messages). The sample event function below illustrates how to
   carry around some state (a running counter in this case) to implement some
   dynamic effects, and how to do random pitch, velocity and onset variations
   on the fly. Also note that here we return an entire "bundle" (i.e., list)
   of Pd messages for each pattern element. */

def PI = 4*atan 1;

getctr C	= put C (K+1) || K where K = get C;

event DUR TIME C N
		= [// play a note on voice #2:
		   T 2 note N 1 D,
		   // vary the pan and wet controls of voice #2 in a periodic
		   // fashion to simulate a sound source walking around in
		   // circles:
		   T 2 pan (0.4+0.3*U),
		   T 2 wet (0.35+0.1*W),
		   // play the same note, delayed by a small amount of time,
		   // transposed down an octave and slightly detuned,
		   // alternating between voice #1 and voice #3:
		   (T+DT) (2*K+1) note (N-12+DN) V D]
		    where I = getctr C, K = I mod 2,
		      X = I mod 100/100*2*PI, U = cos X, W = sin X,
		      T = get TIME, D = get DUR, DT = rand 0 10,
		      DN = rand (-20) 20/1000,
		      V = rand 90 120/100;
