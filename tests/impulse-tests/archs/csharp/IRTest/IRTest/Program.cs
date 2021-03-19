using System;
using System.IO;

namespace IRTest
{
    class Program
    {
        static bool Verbose = false;
        static bool WriteOutput = false;
        static int ComputeBlockSize = 64;
        static string FaustDir = @"..\..\..\..\..\..\..\..\..\";
        static string[] ExcludeDSP = { "sound.dsp" };

        static void Main(string[] args)
        {
            ExecuteTests(FaustDir);
        }

        static void ExecuteTests(string faustPath)
        {
            string testPath = Path.Combine(faustPath, @"tests\impulse-tests");

            string dspPath = Path.Combine(testPath, @"dsp");
            string irPath = Path.Combine(testPath, "reference");

            DSPCompiler compiler = new DSPCompiler(FaustDir);

            int numSucceeded = 0;
            int numFailed = 0;

            foreach (string dspFile in Directory.GetFiles(dspPath, "*.dsp"))
            {
                string dspName = Path.GetFileName(dspFile);

                if (Array.Exists<string>(ExcludeDSP, element => element == dspName))
                {
                    Console.WriteLine(dspName + " - Excluded");

                    continue;
                }

                if (Verbose)
                    Console.WriteLine("Compiling: " + dspFile);

                IFaustDSP dsp = null;

                bool succeeded = false;

                try
                {
                    try
                    {
                        dsp = compiler.CompileDSP(dspFile);
                    }
                    catch (Exception ex)
                    {
                        if (Verbose)
                            Console.WriteLine("Dsp computation failed with: " + ex.ToString());
                    }

                    if (dsp != null)
                    {
                        string irFile = Path.Combine(irPath, Path.GetFileNameWithoutExtension(dspFile) + ".ir");

                        if (!File.Exists(irFile))
                        {
                            if (Verbose)
                                Console.WriteLine("Unable to find ir file: " + irFile);
                        }
                        else
                        {
                            double[][] irData = ReadIRFile(irFile);

                            if (irData == null)
                            {
                                if (Verbose)
                                    Console.WriteLine("Unable to read ir data from: " + irFile);
                            }
                            else
                            {
                                dsp.Init(44100);

                                int numFrames = irData[0].Length / 4;

                                if (Verbose)
                                    Console.WriteLine("IR files has " + dsp.GetNumInputs() + " inputs, " + dsp.GetNumOutputs() + " outputs, and " + numFrames + " frames");

                                double[][] inputData = new double[dsp.GetNumInputs()][];
                                for (int inputChannel = 0; inputChannel < dsp.GetNumInputs(); inputChannel++)
                                {
                                    inputData[inputChannel] = new double[ComputeBlockSize];
                                }

                                double[][] outputData = new double[dsp.GetNumOutputs()][];
                                for (int outputChannel = 0; outputChannel < dsp.GetNumOutputs(); outputChannel++)
                                {
                                    outputData[outputChannel] = new double[ComputeBlockSize];
                                }

                                double error = 0;
                                double maxErrror = 0;

                                int computeRun = 0;
                                int framesLeft = numFrames;
                                int currentFrame = 0;

                                while (framesLeft > 0)
                                {
                                    if (computeRun == 0)
                                    {
                                        for (int inputChannel = 0; inputChannel < dsp.GetNumInputs(); inputChannel++)
                                        {
                                            inputData[inputChannel][0] = 1;
                                        }

                                        SetButtons(dsp.UIDefinition.RootElement, 1);
                                    }
                                    else if (computeRun == 1)
                                    {
                                        for (int inputChannel = 0; inputChannel < dsp.GetNumInputs(); inputChannel++)
                                        {
                                            inputData[inputChannel][0] = 0;
                                        }

                                        SetButtons(dsp.UIDefinition.RootElement, 0);
                                    }

                                    dsp.Compute(ComputeBlockSize, inputData, outputData);

                                    int blockSize = Math.Min(ComputeBlockSize, framesLeft);

                                    for (int sample = 0; sample < blockSize; sample++)
                                    {
                                        string compString = null;

                                        for (int outputChannel = 0; outputChannel < outputData.Length; outputChannel++)
                                        {
                                            double outputValue = outputData[outputChannel][sample];

                                            outputValue = Math.Round(outputValue * 1000000) / 1000000;

                                            double diff = irData[outputChannel][currentFrame] - outputValue;

                                            if (WriteOutput)
                                                compString += irData[outputChannel][currentFrame] + "/" + outputValue + "  ";

                                            if (Math.Abs(diff) > maxErrror)
                                            {
                                                maxErrror = Math.Abs(diff);
                                            }

                                            if (diff != 0)
                                            {
                                            }

                                            error += diff * diff;
                                        }

                                        currentFrame++;

                                        if (WriteOutput)
                                            Console.WriteLine(compString);
                                    }

                                    framesLeft -= blockSize;
                                    computeRun++;
                                }

                                error = Math.Sqrt(error / (double)(irData.Length * numFrames));

                                if (Verbose)
                                {
                                    Console.WriteLine("Root-mean-square error is: " + error.ToString("0.########") + " Max error is: " + maxErrror.ToString("0.########"));
                                    Console.WriteLine();
                                }
                                else
                                {
                                    succeeded = (maxErrror < 0.001);
                                }
                            }
                        }
                    }
                }
                catch (Exception ex)
                {
                    if (Verbose)
                    {
                        Console.WriteLine("Testing failed with: " + ex.ToString());
                    }
                    else
                    {
                        Console.WriteLine(Path.GetFileName(dspFile) + " - *** Failed");
                    }
                }

                Console.WriteLine(Path.GetFileName(dspFile) + " - " + (succeeded ? "Success" : "*** Failed"));

                if (succeeded)
                    numSucceeded++;
                else
                    numFailed++;
            }

            Console.WriteLine();
            Console.WriteLine(numSucceeded + " tests succeeded. " + numFailed + " tests failed");
        }

        static void SetButtons(FaustUIElement element, double value)
        {
            if (element is FaustBoxElement)
            {
                foreach (FaustUIElement child in (element as FaustBoxElement).Children)
                {
                    SetButtons(child, value);
                }
            }
            else
            {
                if (element is FaustUIVariableElement)
                {
                    if (element.ElementType == EFaustUIElementType.Button)
                    {
                        FaustUIVariableElement variableElement = (element as FaustUIVariableElement);

                        variableElement.VariableAccessor.SetValue(value);
                    }
                }
            }
        }

        static double[][] ReadIRFile(string irFile)
        {
            double[][] irData = null;

            using (StreamReader reader = new StreamReader(irFile))
            {
                int numInputs = -1;
                int numOutputs = -1;
                int numFrames = -1;

                numInputs = ReadIRHeader(reader, "number_of_inputs");

                if (numInputs != -1)
                {
                    numOutputs = ReadIRHeader(reader, "number_of_outputs");

                    if (numOutputs != -1)
                    {
                        numFrames = ReadIRHeader(reader, "number_of_frames");

                        if (numFrames != -1)
                        {
                            irData = new double[numOutputs][];

                            for (int outputChannel = 0; outputChannel < numOutputs; outputChannel++)
                            {
                                irData[outputChannel] = new double[numFrames];
                            }

                            for (int i = 0; i < numFrames; i++)
                            {
                                string frameLine = reader.ReadLine();

                                if (frameLine != null)
                                {
                                    string[] frameSplit = frameLine.Split(':');

                                    if (frameSplit.Length == 2)
                                    {
                                        string[] valueSplit = frameSplit[1].Trim().Split(' ');

                                        if (valueSplit.Length == numOutputs)
                                        {
                                            try
                                            {
                                                for (int outputChannel = 0; outputChannel < numOutputs; outputChannel++)
                                                {
                                                    irData[outputChannel][i] = double.Parse(valueSplit[outputChannel]);
                                                }

                                                continue;
                                            }
                                            catch { };
                                        }
                                    }
                                }

                                Console.WriteLine("Error reading frame data at frame " + i);

                                return null;
                            }
                        }
                    }
                }
            }

            return irData;
        }

        static int ReadIRHeader(StreamReader reader, string parameterName)
        {
            string line = reader.ReadLine();

            if (line != null)
            {
                string[] lineSplit = line.Split(':');

                if (lineSplit.Length == 2)
                {
                    if (lineSplit[0].Trim().ToLower() == parameterName)
                    {
                        return int.Parse(lineSplit[1]);
                    }
                }
            }

            Console.WriteLine("IR file does not contain parameter " + parameterName);

            return -1;
        }
    }
}
