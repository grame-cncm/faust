# Performance

- A parita' di sorgente `.dsp` scritta in linguaggio `faust`, il compilatore di cpp pare essere piu' abile
  ad estrapolare il contesto necessario per poter applicare delle ottimizzazioni.

  In particolare, nel caso di sorgenete `carre_volterra.dsp` il codice assembly generato dalla traduzione in
  `cpp` evidenzia l'estrazione di variabili temporanee dal main loop e la loro scrittura a cascata al
  termine dello stesso, riducendo drasticamente gli accessi alla memoria. D'altra parte, il codice assembly
  generato dalla traduzione in `mojo` effettua continuamente letture e scritture della memoria centrale.

- Un'altra ottimizzazione impiegata da `cpp` nel caso di `carre_volterra.dsp` e' nota come `loop peeling`,
  ovvero... <!-- TODOo -->
