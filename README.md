splitmbox
=========

Splits an mbox email message file into multiple monthly mbox files.

[Google Takeout][1] allows users to download their email messages as
one mbox. For many, the size of this mbox file will be unwieldy.

This C program reads an mbox file and writes separate mbox files for
each month.

Installation
------------

Compile splitmbox using the gcc-based Makefile.

    $ cd src
    $ make

Usage
-----

    $ cat my_large_gmail.mbox | splitmbox

An mbox is read from standard input, and split into multiple mbox
files -- one for each month of messages.

    $ ls
    201601.mbox  201606.mbox  201611.mbox  201704.mbox  201709.mbox  201802.mbox  201807.mbox
    201602.mbox  201607.mbox  201612.mbox  201705.mbox  201710.mbox  201803.mbox  my_large_gmail.mbox
    201603.mbox  201608.mbox  201701.mbox  201706.mbox  201711.mbox  201804.mbox
    201604.mbox  201609.mbox  201702.mbox  201707.mbox  201712.mbox  201805.mbox
    201605.mbox  201610.mbox  201703.mbox  201708.mbox  201801.mbox  201806.mbox




[1]: https://support.google.com/accounts/answer/3024190?hl=en
