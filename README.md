This is a project I started as a freshman in college.  I pick it up to play with every few years.

It's an implementation of the solitaire encryption algorithm:
www.schneier.com/solitaire.html

A short breakdown of what things are:
* solpipe: Pipe text through the command line for encryption/decryption
* bench: runs through the deck for beanchmarking purposes
* hasher: mostly to keep a hash of decks for loop analysis.  Don't try to use it with a large deck size
* dumper: dumps the deck through iterations
* alphabreaker: Tries to break encrypted text using iterations of decks keyed with letter strings
* numbreaker: Tries to break encrypted text using iterations of decks keyed with incremental numbered decks (not realistic)
* solitaire: ncurses frontend to encryption/decryption

