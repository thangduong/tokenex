#Tokenex - *An extended cross language, cross platform, flexible tokenizer.*
Thang Duong
(issues: e-mail me thduon@microsoft.com)


#**tl;dr;**
Here are some selling points:
* Configurable.  It's configurable to remove space, leave space, use regex, don't use regex, and, in the near future, use your own list of words and regex.
* By default, it's does some simple regex.  For example, numbers to <int>, ordinals to <ord>, etc.
* Works in C++, Python, C#.
* Has some tools to tokenize training data.


# Hello, Tokenex!

Download v0.1 package here:
https://dlwteam.visualstudio.com/6894e6c5-e313-4afd-9c46-95fbfd40a7a8/_api/_versioncontrol/itemContent?repositoryId=e6217287-ad4a-452a-b169-a75286a95971&path=%2Fdist%2Ftokenex-0.1-py3-none-any.whl&version=GBmaster&contentOnly=false&__v=5

Go to where you downloaded it and run:

> sudo pip3 install tokenex-0.1-py3-none-any.whl

## For Python3

### Using the default config
```python
from tokenex.tokenizer as Tokenizer
t = Tokenizer()
t.tokenize('hello, world')
```

### Keep space and don't use regex
```python
from tokenex.tokenizer as Tokenizer
t = Tokenizer(3)
t.tokenize('hello, world')
```

##Everything below here requires checking out the repo

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


### How to use the Python API?

Add the ./tokenex directory to your PYTHONPATH environment variable.

(in Linux)
> export PYTHONPATH=$PYTHONPATH:./tokenex

(in Windows)
> set PYTHONPATH=%PATH%:./tokenex


See *./tokenex/test.py* for an example.

To use the default tokenizer settings:

```python
import tokenizer as t
tok = t.Tokenizer(0)                           # config option 0 is standard
tokens = tok.tokenize("hello, world!")
print(' '.join(tokens))
```

This version will discard space, \r, \n, \t, etc.  and it will automatically translit from UTF-8 to ASCII.

To just tokenize and keep everything unchanged:

```python
import tokenizer as t
tok = t.Tokenizer(3)                           # config option 3 keeps everything
tokens = tok.tokenize("hello, world!")
print(' '.join(tokens))
```

For additional details, see the class definition in tokenex/tokenizer.py.



### How to use the C# API?


Reference tokenizerCS package (.\tokenex\tokenizerCS.dll)


```csharp
using Tokenizex;
```

Then:

```csharp
Tokenizer tok = new Tokenizer(0);           // change this config option to 3 to keep everything
var result = tok.TokenizeEx("hello, world!");
foreach (var token in result)
        System.Console.WriteLine("{0}", token);
```

### How to tokenize a large txt training data file?

Use the program .\tokenex\tokenize.exe (or ./tokenex/tokenize for Linux).

In Linux (and it should be similar in Windows):

> ./tokenex/tokenize <input-file> > <output-file>


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

* Load tokenex.sln, and build all.

### Building in Linux

(assuming you're already in the base directory)
> make

Then check the ./bin directory for output files

