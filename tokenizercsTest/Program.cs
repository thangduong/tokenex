/*---------------------------------------------------------------------------------------------
*  Copyright (c) Microsoft Corporation. All rights reserved.
*  Licensed under the MIT License. See License.txt in the project root for license information.
*--------------------------------------------------------------------------------------------*/
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Tokenex;

namespace tokenizercsTest
{
    class Program
    {
        static void Main(string[] args)
        {
            Tokenizer tok = new Tokenizer();
            string input_string = "The Caf֍ is bad but the tea is good.";// "F.D.R. was a great president in the 1930s, and A.I.G was an insurance company. 1929 was a bad year. bob's cat is black. don't do it.";
            if (args.Length > 0)
                input_string = args[0];
            var result = tok.TokenizeEx(input_string);
            System.Console.WriteLine(input_string);
            foreach (var token in result)
            {
                System.Console.WriteLine("{0}, {1}, {2}, {3}", token.token, token.start, token.len, token.type);
            }
            var tokenizeResult = tok.Tokenize(input_string, true, true);
            System.Console.WriteLine(String.Join(" ", tokenizeResult.ToArray()));
        }
    }
}
