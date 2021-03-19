using System;
using System.Diagnostics;
using System.Collections.Generic;
using System.IO;
using System.Reflection;
using System.Text;
using Microsoft.CodeAnalysis;
using Microsoft.CodeAnalysis.Emit;
using Microsoft.CodeAnalysis.CSharp;

namespace IRTest
{
    public class DSPCompiler
    {
        string faustDir;

        public DSPCompiler(string faustDir)
        {
            this.faustDir = faustDir;
        }

        public IFaustDSP CompileDSP(string dspPath)
        {
            StringBuilder compilerOutput = new StringBuilder();

            using (Process process = new Process())
            {
                process.StartInfo.FileName = Path.Combine(faustDir, @"build\bin\Release\faust.exe");
                process.StartInfo.Arguments = "-lang csharp -a " + faustDir + @"\architecture\CSharpFaustClass.cs -double " + dspPath;
                process.StartInfo.CreateNoWindow = true;
                process.StartInfo.RedirectStandardOutput = true;
                process.StartInfo.RedirectStandardInput = true;
                process.StartInfo.UseShellExecute = false;

                process.OutputDataReceived += (sender, args) => compilerOutput.AppendLine(args.Data);

                if (process.Start())
                {
                    process.BeginOutputReadLine();
                    
                    process.WaitForExit();

                    List<MetadataReference> refs = new List<MetadataReference>();

                    Assembly executingAssembly = this.GetType().Assembly;

                    refs.Add(MetadataReference.CreateFromFile(executingAssembly.Location));

                    refs.Add(MetadataReference.CreateFromFile(typeof(Object).Assembly.Location));

                    foreach (AssemblyName assemblyName in executingAssembly.GetReferencedAssemblies())
                    {
                        refs.Add(MetadataReference.CreateFromFile(Assembly.Load(assemblyName).Location));
                    }

                    CSharpCompilationOptions options = new CSharpCompilationOptions(OutputKind.DynamicallyLinkedLibrary, optimizationLevel: OptimizationLevel.Release,
                        assemblyIdentityComparer: DesktopAssemblyIdentityComparer.Default);

                    CSharpCompilation csharpCompilation = CSharpCompilation.Create("DynamicPlugin", new[] { CSharpSyntaxTree.ParseText(compilerOutput.ToString()) }, refs, options);

                    using (var memoryStream = new MemoryStream())
                    {
                        EmitResult result = csharpCompilation.Emit(memoryStream);

                        if (result.Success)
                        {
                            memoryStream.Seek(0, SeekOrigin.Begin);
                            Assembly assembly = Assembly.Load(memoryStream.ToArray());

                            Type dspType = assembly.GetType("mydsp");

                            if (dspType == null)
                            {
                                string typeStr = "Couldn't find type in assembly with types: ";

                                foreach (Type type in assembly.GetTypes())
                                {
                                    typeStr += type.FullName + ", ";
                                }

                                throw new Exception(typeStr);
                            }

                            IFaustDSP dspClass = Activator.CreateInstance(dspType) as IFaustDSP;

                            return dspClass;
                        }
                        else
                        {
                            string errStr = null;

                            foreach (Diagnostic diag in result.Diagnostics)
                            {
                                errStr += diag.ToString();
                            }

                            throw new Exception(errStr);
                        }
                    }
                }
            }

            return null;
        }
    }
}
