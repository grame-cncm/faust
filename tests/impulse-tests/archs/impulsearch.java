/*
 * Faust impulse-test architecture, double precision.
 * This sample code may be redistributed and modified without restriction.
 */

import java.io.BufferedWriter;
import java.io.OutputStreamWriter;
import java.nio.charset.StandardCharsets;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Formatter;
import java.util.Locale;

class Meta {
    public void declare(String key, String value) {}
}

interface FaustVarAccess {
    String getId();
    void set(double value);
    double get();
}

abstract class dsp {}

class UI {
    private final ArrayList<FaustVarAccess> controls = new ArrayList<>();
    private final ArrayList<Double> defaults = new ArrayList<>();
    private final ArrayList<FaustVarAccess> buttons = new ArrayList<>();

    public void declare(String zone, String key, String value) {}
    public void openTabBox(String label) {}
    public void openHorizontalBox(String label) {}
    public void openVerticalBox(String label) {}
    public void closeBox() {}

    private void addControl(FaustVarAccess zone, double initial) {
        controls.add(zone);
        defaults.add(initial);
    }

    public void addButton(String label, FaustVarAccess zone) {
        addControl(zone, 0.0);
        buttons.add(zone);
    }
    public void addCheckButton(String label, FaustVarAccess zone) {
        addControl(zone, 0.0);
    }
    public void addVerticalSlider(String label, FaustVarAccess zone,
            double initial, double minimum, double maximum, double step) {
        addControl(zone, initial);
    }
    public void addHorizontalSlider(String label, FaustVarAccess zone,
            double initial, double minimum, double maximum, double step) {
        addControl(zone, initial);
    }
    public void addNumEntry(String label, FaustVarAccess zone,
            double initial, double minimum, double maximum, double step) {
        addControl(zone, initial);
    }
    public void addHorizontalBargraph(String label, FaustVarAccess zone,
            double minimum, double maximum) {}
    public void addVerticalBargraph(String label, FaustVarAccess zone,
            double minimum, double maximum) {}

    public void setButtons(boolean pressed) {
        for (FaustVarAccess button : buttons) button.set(pressed ? 1.0 : 0.0);
    }
    public void perturbControls() {
        for (FaustVarAccess control : controls) control.set(0.123456789);
    }
    public void checkDefaults() {
        for (int index = 0; index < controls.size(); index++) {
            if (controls.get(index).get() != defaults.get(index)) {
                throw new AssertionError("Wrong default for " + controls.get(index).getId());
            }
        }
    }
}

<<includeIntrinsic>>
<<includeclass>>

class Impulse {
    private static final int SAMPLE_RATE = 44100;
    private static final int BLOCK_SIZE = 64;
    // The first reference segment is the ordinary scalar impulse response.
    // The remaining segments exercise split blocks and the C++ polyphonic wrapper.
    private static final int SAMPLES = 15000;

    public static void main(String[] args) throws Exception {
        if (args.length != 1 || (!args[0].equals("fixed") && !args[0].equals("fragmented"))) {
            throw new IllegalArgumentException("Expected fixed or fragmented mode");
        }
        boolean fragmented = args[0].equals("fragmented");
        int[] partitions = {1, 7, 3, 19, 2, 11, 5};
        int partition = 0;
        mydsp processor = new mydsp();
        UI ui = new UI();
        processor.buildUserInterface(ui);
        ui.perturbControls();
        processor.init(SAMPLE_RATE);
        if (processor.fSampleRate != SAMPLE_RATE) {
            throw new AssertionError("Wrong sample rate");
        }
        ui.checkDefaults();
        ui.perturbControls();
        processor.instanceResetUserInterface();
        ui.checkDefaults();
        ui.perturbControls();
        processor.instanceInit(SAMPLE_RATE);
        ui.checkDefaults();

        // Match the fresh instance used by the native impulse architecture.
        processor = new mydsp();
        processor.instanceInit(SAMPLE_RATE);
        ui = new UI();
        processor.buildUserInterface(ui);
        int inputsCount = processor.getNumInputs();
        int outputsCount = processor.getNumOutputs();
        double[][] inputs = new double[inputsCount][BLOCK_SIZE];
        double[][] outputs = new double[outputsCount][BLOCK_SIZE];
        for (double[] channel : inputs) channel[0] = 1.0;

        try (BufferedWriter writer = new BufferedWriter(
                new OutputStreamWriter(System.out, StandardCharsets.UTF_8))) {
            Formatter format = new Formatter(writer, Locale.ROOT);
            format.format("number_of_inputs  : %3d%n", inputsCount);
            format.format("number_of_outputs : %3d%n", outputsCount);
            format.format("number_of_frames  : %6d%n", SAMPLES);
            for (int offset = 0; offset < SAMPLES; offset += BLOCK_SIZE) {
                int count = Math.min(BLOCK_SIZE, SAMPLES - offset);
                ui.setButtons(offset == 0);
                if (!fragmented) {
                    processor.compute(count, inputs, outputs);
                } else {
                    // Keep controls at the same 64-frame boundaries as the fixed run.
                    // Slice inputs so an impulse is not repeated at each compute call.
                    for (int start = 0; start < count;) {
                        int size = Math.min(partitions[partition++ % partitions.length], count - start);
                        double[][] slicedInputs = new double[inputsCount][];
                        double[][] slicedOutputs = new double[outputsCount][size];
                        for (int channel = 0; channel < inputsCount; channel++) {
                            slicedInputs[channel] = Arrays.copyOfRange(inputs[channel], start, start + size);
                        }
                        processor.compute(size, slicedInputs, slicedOutputs);
                        for (int channel = 0; channel < outputsCount; channel++) {
                            System.arraycopy(slicedOutputs[channel], 0, outputs[channel], start, size);
                        }
                        start += size;
                    }
                }
                for (int frame = 0; frame < count; frame++) {
                    format.format("%6d : ", offset + frame);
                    for (double[] channel : outputs) {
                        double value = channel[frame];
                        if (!Double.isFinite(value)) {
                            throw new ArithmeticException("Non-finite output at " + (offset + frame));
                        }
                        format.format(" %8.6f", Math.abs(value) < 0.000001 ? 0.0 : value);
                    }
                    format.format("%n");
                }
                for (double[] channel : inputs) channel[0] = 0.0;
            }
            if (format.ioException() != null) throw format.ioException();
        }
    }
}
