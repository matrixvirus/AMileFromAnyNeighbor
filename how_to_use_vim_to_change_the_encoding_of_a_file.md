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

note,the - between utf and 16 is optionable,you can also use 

    :set fileencoding=utf-16

or

    :set fileencoding=utf-8

