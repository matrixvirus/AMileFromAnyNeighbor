# how to use vim to change the encoding of a file

# change a file encoding to utf-8
if you want to change the encoding of a file to utf8

    vim abc.txt

and then in vim,

    :set bomb
    :set fileencoding=utf8
    :wq

then in linux shell,check the file

    file abc.txt

you will see

    abc.txt: UTF-8 Unicode (with BOM) text

# change a file encoding to utf-16
in vim

    :set bomb
    :set fileencoding=utf16
    :wq

then in linux,check the file

    file abc.txt
    abc.txt:Big-endian UTF-16 Unicode text

open the file

    vim abc.txt

if your vim default encoding is utf8, you will see mess codes,because
you have just change the file to utf16,so you should 

    :set fileencodings=utf16

and reload 

    :e

then you see the correct content.

### note,s vs non s
the two mode,when change the encoding of a file,use

    :set fileencoding=utf8

when change the encoding of opening,use

    :set fileencodings=utf16

do you notice?one with 's',one without 's'.

# note,the - between utf and 16 
is optionable,you can also use 

    :set fileencoding=utf-16

or

    :set fileencoding=utf-8

# note,some convert is not recoverable
you can convert utf8 to utf16,but you if you convert it back to utf8,
the content is lost.

# how to use vim to convert encoding in one step

    vim -c "set bomb" -c "set fileencoding=utf8" -c "wq" abc.txt

