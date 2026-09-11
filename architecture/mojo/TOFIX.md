
- `gui.terminal.terminal.ControlDsp` non dovrebbe stare li, inoltre parla esplicitamente con
  `gui.terminal.terminal.TerminalGui`, mentre dovrebbe parlare con una `FaustGui` o qulcosa del genere.
- `audio.portaudio.gpu.PortAudioGpu` non rispetta il contratto di `audio.audio.FaustAudio`
- occorre pensare ad una sorta di contratto anche per la `gpu` in un certo senso, ed agire di composizione
  di piu' parti, con una che magari implementa il contratto di `audio.audio.FaustAudio` e l'altra di `gpu` o
  comunque un approccio del genere.
- primda di pensare ad un possibile generatore occorre tenere d'occhio queste cosucce altrimenti non
  possiamo generare un bel cavolo di niente.
