#----------------------------------------------------------------------------------------------
#  Copyright (c) Microsoft Corporation. All rights reserved.
#  Licensed under the MIT License. See License.txt in the project root for license information.
#----------------------------------------------------------------------------------------------
import tokenizer as t
import sys
input_string = "hello, world siic's! on----the 06th of this month and the 124th street, the 1st, 2nd, 3rd, 4th, 5th, the minor fall and the major lift"
input_string = "hello ----the"
input_string = "hello= ===ther’e 520"

if len(sys.argv)>1:
  input_string = sys.argv[1]
tok = t.Tokenizer(0)
tokens = tok.tokenize(input_string, regex_keep_original=True)
output = ' '.join(tokens)

print(output)
