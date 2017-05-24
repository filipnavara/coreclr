﻿using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Text.RegularExpressions;
using System.Threading.Tasks;

namespace MonoProxyCodeGen
{
    class Program
    {
        struct Parameter
        {
            public string Type;

            public string Name;
        }

        static void Main(string[] args)
        {
            //var writer = Console.Out;

            // Defines the platform
            //var platform = "PLATFORM_OSX";
            var platform = "PLATFORM_WIN";
            const bool generateProxy = true;
            var fileOutput = generateProxy ? "../../../mono-proxy/monoproxy.cpp" : "monoproxy_decl.cpp";

            var writer = new StreamWriter(Path.Combine(Environment.CurrentDirectory, fileOutput));

            var processStartInfo = new ProcessStartInfo(@"C:\Program Files (x86)\Microsoft Visual Studio\2017\Professional\VC\Tools\MSVC\14.10.25017\bin\HostX86\x86\cl.exe",
                $"/E /nologo /D{platform}=1 /I{Environment.GetEnvironmentVariable("UNITY_ROOT")}\\runtime\\mono MonoFunctionsProxy.h");

            processStartInfo.UseShellExecute = false;
            processStartInfo.RedirectStandardOutput = true;

            var process = Process.Start(processStartInfo);
            process.Start();

            var reader = process.StandardOutput;
            
            string line = null;
            var split = new char[] {'|'};
            var splitParams = new char[] {','};

            if (generateProxy)
            {
                writer.WriteLine("// This file is generated automatically DO NOT EDIT");
                writer.WriteLine("// Generated with MonoProxyCodeGen");
                writer.WriteLine();
                writer.WriteLine("#include \"monoproxy.h\"");
            }

            var regexArgName = new Regex(@"[A-Za-z_][A-Za-z_0-9]*(\[\])?$");
            var functions = new List<string>();
            while ((line = reader.ReadLine()) != null)
            {
                if (!line.StartsWith("|"))
                {
                    continue;
                }
                var entries = line.Split(split, StringSplitOptions.RemoveEmptyEntries);
                Debug.Assert(entries.Length == 3);

                var returnType = entries[0].Trim();
                var functionName = entries[1].Trim();
                var rawParameters = entries[2].Trim().TrimStart('(').TrimEnd(')').Split(splitParams, StringSplitOptions.RemoveEmptyEntries);

                var parameters = new Parameter[rawParameters.Length];
                var paramRedirect = new StringBuilder();
                for (int i = 0; i < rawParameters.Length; i++)
                {
                    var p = rawParameters[i].Trim();
                    var result = regexArgName.Match(p);
                    Debug.Assert(result.Success);
                    var param = new Parameter
                    {
                        Type = p.Substring(0, result.Index),
                        Name = p.Substring(result.Index).TrimEnd('[', ']')
                    };
                    parameters[i] = param;
                    if (i > 0)
                    {
                        paramRedirect.Append(", ");
                    }
                    paramRedirect.Append(param.Name);
                }
                
                var callback = $"__{functionName}__";
                writer.WriteLine();

                if (generateProxy)
                {
                    writer.WriteLine($"typedef {returnType} (*type_{functionName}){entries[2]};");
                    writer.WriteLine($"type_{functionName} {callback};");
                }
                var export = generateProxy ? "EXPORT_API " : "";
                writer.WriteLine($"extern \"C\" {export}{returnType} {functionName}{entries[2]}");
                writer.WriteLine("{");
                if (generateProxy)
                {
                    writer.WriteLine($"    log_function_usage(\"{functionName}\");");
                    writer.WriteLine($"    if (!{callback})");
                    writer.WriteLine(
                        $"        {callback} = (type_{functionName})load_mono_function(\"{functionName}\");");
                    writer.Write(returnType == "void" ? "    " : "    return ");
                    writer.WriteLine($"{callback}({paramRedirect});");
                }
                else
                {
                    writer.WriteLine($"    ASSERT_NOT_IMPLEMENTED;");
                    if (returnType != "void")
                    {
                        writer.WriteLine($"    return ({returnType})0;");
                    }
                }
                writer.WriteLine("}");

                functions.Add(functionName);
            }

            writer.WriteLine();
            writer.WriteLine($"// Exported Functions for platform {platform}");
            foreach (var function in functions)
            {
                writer.WriteLine($"// {function}");
            }

            writer.Flush();
            writer.Close();
        }
    }
}
