copy bin\tokenizer.dll tokenex
copy bin\tokenizercs.dll tokenex
tools\nuget.exe pack tokenex.nuspec
copy *.nupkg dist