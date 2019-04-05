.. XXX_PROJECT_NAME_XXX documentation master file, created by
   sphinx-quickstart on Sat Mar 16 12:35:31 2019.
   You can adapt this file completely to your liking, but it should at least
   contain the root `toctree` directive.

Welcome to XXX_PROJECT_NAME_XXX's documentation!
================================================

.. toctree::
   :maxdepth: 2
   :caption: Contents:


Hello bobathons. This is me going through sphinx documentation
and actually walking through.

I can also make a second paragraph, if I really really want to.

This text is *emphasized*.

This text is **strong**.

This text is ``val code: Boolean = true``.

* This is a bulleted list.
* It has two items, the second
  item uses two lines.

1. This is a numbered list.
2. It has two items too.

#. This is a numbered list.
#. It has two items too.

* this is
* a list

  * with a nested list
  * and some subitems

* and here the parent list continues

term (up to a line of text)
   Definition of the term, which must be indented

   and can even consist of multiple paragraphs

next term
   Description.


One day I was walking in the park and I met an old man.

   This is a very wise saying someone
   some day told me.

   You will be a great king, my child.

And this is all the old man ever said to me.

| These lines are
| broken exactly like in
| the source file.

..........
Field List
..........

:Date: 2001-08-16
:Version: 1
:Authors: - Me
          - Myself
          - I
:Indentation: Since the field marker may be quite long, the second
   and subsequent lines of the field body do not have to line up
   with the first line, but they must be indented relative to the
   field name marker, and they must line up with each other.
:Parameter i: integer

...........
Option List
...........

-a         Output all.
-b         Output both (this description is
           quite long).
-c arg     Output just arg.
--long     Output all day long.

-p         This option has two paragraphs in the description.
           This is the first.

           This is the second.  Blank lines may be omitted between
           options (as above) or left in (as here and below).

--very-long-option  A VMS-style option.  Note the adjustment for
                    the required two spaces.

--an-even-longer-option
           The description can also start on the next line.

-2, --two  This option has two variants.

-f FILE, --file=FILE  These two options are synonyms; both have
                      arguments.

/V         A VMS/DOS-style option.

.....................
Quoted Literal Blocks
.....................

John Doe wrote::

>> Great idea!
>
> Why didn't I think of that?

You just did!  ;-)

..............
DocTest Blocks
..............

This is an ordinary paragraph.

>>> print 'this is a Doctest block'
this is a Doctest block

The following is a literal block::

    >>> This is not recognized as a doctest block by
    reStructuredText.  It *will* be recognized by the doctest
    module, though!

..............
Literal Blocks
..............

This is a normal text paragraph. The next paragraph is a code sample::

   It is not processed in any way, except
   that the indentation is removed.

   It can span multiple lines.

This is a normal text paragraph again.

......
Tables
......

+------------------------+------------+----------+----------+
| Header row, column 1   | Header 2   | Header 3 | Header 4 |
| (header rows optional) |            |          |          |
+========================+============+==========+==========+
| body row 1, column 1   | column 2   | column 3 | column 4 |
+------------------------+------------+----------+----------+
| body row 2             | ...        | ...      |          |
+------------------------+------------+----------+----------+

....
Funk
....


:Date: 2001-08-16
:Version: 1
:Authors: - Me
          - Myself
          - I
:Indentation: Since the field marker may be quite long, the second
   and subsequent lines of the field body do not have to line up
   with the first line, but they must be indented relative to the
   field name marker, and they must line up with each other.
:Parameter i: integer

.........................................
Here is a list of all cool stuff from cpp
.........................................


Indices and tables
==================

* :ref:`genindex`
* :ref:`modindex`
* :ref:`search`
