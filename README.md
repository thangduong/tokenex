#Tokenex - *An extended cross language, cross platform, flexible tokenizer.*
Thang Duong
(issues: e-mail me thduon@microsoft.com)


#**tl;dr;**
Here are some selling points:
* Configurable.  It's configurable to remove space, leave space, use regex, don't use regex, and, in the near future, use your own list of words and regex.
* By default, it's does some simple regex.  For example, numbers to <int>, ordinals to <ord>, etc.
* Works in C++, Python, C#.
* Has some tools to tokenize training data.


To play with this:

*Shell Test App*
> cd tokenex
> ./test "hello===world! It is about to be 2018!  We are one year closer to 2020.  I hope the 2020s will be better than 2010s"

*Python*
> cd tokenex
> python test.py "hello===world! It is about to be 2018!  We are one year closer to 2020.  I hope the 2020s will be better than 2010s"

*C# Test App*
> cd tokenex
> tokenizercsTest.exe "hello===world! It is about to be 2018!  We are one year closer to 2020.  I hope the 2020s will be better than 2010s"

The output should look something like this:

> hello === world ! It is about to be <int> ! We are one year closer to <int> . I hope the <decade-year> will be better than <decade-year>


### How to use the Python API



### How to use the C# API




### Relevant subdirectories:
2. libtokenizer
        The core tokenization code.  When compiled, it generates a .lib in Windows, and a .a in Linux.

4. tokenex
        A snapshot of compiled output for both Windows and Linux.

5. tokenize
        A program to tokenize text files.

6. tokenizer
        A wrapper around libtokenizer to create dynamic library (.DLL in Winodws, .so in Linux).

7. tokenizercs
        A C# wrapper around tokenizer dynamic library.

8. tokenizercsTest
        A test C# app demonstrating how to use tokenizercs.

### Building in Windows

* Load token

### Building in Linux

(assuming you're already in the base directory)
> make

Then check the ./bin directory for output files

