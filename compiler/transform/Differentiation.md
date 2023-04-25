# Differentation done at signal level

## Symbolic Differentiation

[Symbolic Differentation](https://en.wikipedia.org/wiki/Computer_algebra) is usually done using rewrite rules on expressions. We differentiate a Faust DSP program with respect to a given input variable (typically controllers like buttons, sliders, numentry). This is expressed using the `[diff:on]` metadata in the controller label.

## Implementation

- a Signal => Signal transformation pass named `SignalAutoDifferentiate` is implemented in `sigPromotion.hh` and `sigPromotion.cpp` files. For now only a subset of signals are actually handled: Integer and Real constants, `sin/cos/sqrt` unary functions, binary operators with special rules for `kMul`and `kDiv`.

- the `signalAutoDifferentiate` function uses a helper `DiffVarCollector` to collect the input variable for a given signal. The `SignalAutoDifferentiate` class is used to compute the derivated signal, then compiled as usual, so code appears in the dsp `init/compute` method (this is the simplest way for now to see what happens). TODO: this obviously will have to be changed !

- the `signalAutoDifferentiate` pass is activated using the `-diff` compiler options.   

- since `SignalAutoDifferentiate`is a subclass of `SignalIdentity`, itself a subclass of `TreeTransform`, the differentiation itself takes profit of the memoïsation system already in place in the `TreeTransform` base class. Thus equal sub-expressions will be derivated once and shared in the transformation.

## Examples of generated code

Since the derivated signal is a regular signal, it takes benefit of all normalisation and optimisation (CSE, factorisation...) steps done in the `simplifyToNormalForm` function in `normalform.cpp`. 

The following program compiled with `faust -diff`:

```
process = 3*f1 + 5*f2
with {
    f1 = hslider("F1", 5, 0, 100, 0.1);
    f2 = hslider("F2 [diff:on]", 5, 0, 30, 0.1);
};
```

generates the C++ code:

```
virtual void compute(int count, 
    FAUSTFLOAT** RESTRICT inputs, 
    FAUSTFLOAT** RESTRICT outputs) {
    FAUSTFLOAT* output0 = outputs[0];
    for (int i0 = 0; i0 < count; i0 = i0 + 1) {
        output0[i0] = FAUSTFLOAT(5.0f);
    }
}
```

The following program compiled with `faust -diff`:

```
process = sin(5*f1)
with {
    f1 = hslider("F1 [diff:on]", 5, 0, 100, 0.1);
    f2 = hslider("F2", 5, 0, 30, 0.1);
};
```

generates the C++ code:

```
virtual void compute(int count, 
    FAUSTFLOAT** RESTRICT inputs, 
    FAUSTFLOAT** RESTRICT outputs) {
    FAUSTFLOAT* output0 = outputs[0];
    float fSlow0 = 5.0f * std::cos(5.0f * float(fHslider0));
    for (int i0 = 0; i0 < count; i0 = i0 + 1) {
        output0[i0] = FAUSTFLOAT(fSlow0);
    }
}
```

The following program compiled with `faust -diff`:

```
process = sin(cos(f2))
with {
    f1 = hslider("F1", 5, 0, 100, 0.1);
    f2 = hslider("F2 [diff:on]", 5, 0, 30, 0.1);
};
```

generates the C++ code:

```
virtual void compute(int count, 
    FAUSTFLOAT** RESTRICT inputs, 
    FAUSTFLOAT** RESTRICT outputs) {
    FAUSTFLOAT* output0 = outputs[0];
    float fSlow0 = float(fHslider0);
    float fSlow1 = std::cos(std::cos(fSlow0)) * (0.0f - std::sin(fSlow0));
    for (int i0 = 0; i0 < count; i0 = i0 + 1) {
        output0[i0] = FAUSTFLOAT(fSlow1);
    }
}
```

The following program compiled with `faust -diff`:

```
process = sin(cos(f2)) + cos(cos(f2))
with {
    f1 = hslider("F1", 5, 0, 100, 0.1);
    f2 = hslider("F2 [diff:on]", 5, 0, 30, 0.1);
};
```

generates the C++ code:

```
virtual void compute(int count, 
    FAUSTFLOAT** RESTRICT inputs, 
    FAUSTFLOAT** RESTRICT outputs) {
    FAUSTFLOAT* output0 = outputs[0];
    float fSlow0 = float(fHslider0);
    float fSlow1 = std::cos(fSlow0);
    float fSlow2 = (0.0f - std::sin(fSlow0)) 
        * (std::cos(fSlow1) 
        + (0.0f - std::sin(fSlow1)));
    for (int i0 = 0; i0 < count; i0 = i0 + 1) {
        output0[i0] = FAUSTFLOAT(fSlow2);
    }
}
```

The [following tool](https://www.matrixcalculus.org) can be used to check derivative computation.
