/*---------------------------------------------------------------------------------------------
*  Copyright (c) Microsoft Corporation. All rights reserved.
*  Licensed under the MIT License. See License.txt in the project root for license information.
*--------------------------------------------------------------------------------------------*/
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Runtime.InteropServices;

namespace Tokenex
{
    public class Tokenizer : IDisposable
    {
        [DllImport(@"tokenizer.dll")]
        public static extern IntPtr LoadTokenizer();
        [DllImport(@"tokenizer.dll")]
        public static extern void UnloadTokenizer(IntPtr tokenizer);
        [DllImport(@"tokenizer.dll")]
        public static extern void LoadDefaultConfig(IntPtr tokenizer, int config_type);
        [DllImport(@"tokenizer.dll")]
        public static extern IntPtr TokenizeString(IntPtr tokenizer, byte[] input_string, bool translit);
        [DllImport(@"tokenizer.dll")]
        public static extern IntPtr NextToken(IntPtr result, ref int start, ref int len, ref int type);
        [DllImport(@"tokenizer.dll")]
        public static extern void FreeTokenizedResult(IntPtr result);

        IntPtr _tokenizer;
        bool _disposed = false;

        /// <summary>
        /// Token structure contains the string token, the start position
        /// of the token in the larger string, the length, and the type (for regex).
        /// </summary>
        public struct Token {
            public string token;
            public int start;
            public int len;
            public int type;
        };

        public Tokenizer(int config_type = 0)
        {
            _tokenizer = LoadTokenizer();
            LoadDefaultConfig(_tokenizer, config_type);
        }

        public IntPtr TokenizeCSString(IntPtr tokenizer, string input_string, bool translit)
        {
            System.Text.Encoding utf_8 = System.Text.Encoding.UTF8;

            // Convert a string to utf-8 bytes.
            byte[] utf8Bytes = System.Text.Encoding.UTF8.GetBytes(input_string);
            return TokenizeString(tokenizer, utf8Bytes, translit);
        }

        /// <summary>
        /// Tokenize a string using the C++ native tokenizer.
        /// </summary>
        /// <param name="input_string">Input string to tokenize.  Try "F.D.R. was a great president in the 1930s."</param>
        /// <param name="translit">True to turn on UTF-8 to ASCII translit</param>
        /// <returns>A list of tokens</returns>
        public List<Token> TokenizeEx(string input_string, bool translit=true)
        {
            List<Token> token_list = new List<Token>();
            IntPtr tokenized_result = TokenizeCSString(_tokenizer, input_string, translit);
            Token token;
            token.start = token.len = token.type = 0;
            IntPtr native_string = IntPtr.Zero;
            while ((native_string = NextToken(tokenized_result, ref token.start, ref token.len, ref token.type)) != IntPtr.Zero) {
                token.token = Marshal.PtrToStringAnsi(native_string);
                token_list.Add(token);
            }
            FreeTokenizedResult(tokenized_result);
            return token_list;
        }

        public List<string> Tokenize(string input_string, bool translit=true, bool regex_keep_original=false)
        {
            List<string> token_list = new List<string>();
            IntPtr tokenized_result = TokenizeCSString(_tokenizer, input_string, translit);
            Token token;
            token.start = token.len = token.type = 0;
            IntPtr native_string = IntPtr.Zero;
            while ((native_string = NextToken(tokenized_result, ref token.start, ref token.len, ref token.type)) != IntPtr.Zero) {
                token.token = Marshal.PtrToStringAnsi(native_string);
                var token_value = token.token;
                if ((token.type > 0) && (regex_keep_original) && (token_value[0] == '<') && (token_value[token_value.Length - 1] == '>'))
                    token_value = token_value + "|" + input_string.Substring(token.start, token.len);
                token_list.Add(token_value);
            }
            FreeTokenizedResult(tokenized_result);
            return token_list;
        }

        public void Dispose()
        {
            Dispose(true);
            GC.SuppressFinalize(this);
        }

        protected virtual void Dispose(bool disposing)
        {
            if (_disposed)
                return;

            if (_disposed)
            {
                UnloadTokenizer(_tokenizer);
            }

            // Free any unmanaged objects here.
            //
            _disposed = true;
        }
    }
}
