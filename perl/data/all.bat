perl horror.pl -t h
perl horror.pl -t i
perl horror.pl -t c
perl horror.pl -t pm
c:\sdk\swigwin-2.0.4\swig.exe -nocontract -perl -static ida.i
sed s/IDAc/IDA/ ida_wrap.c | perl fix_xs.pl > ..\ida_wrap.c
copy /y ida.cpp ..
copy /y ida.h ..