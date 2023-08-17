The song used for this demo was taken from the bitmidi web site:

https://bitmidi.com/the-empire-strikes-back-from-starwars-mid

https://bitmidi.com/dorian-mid

It was converted with the `miditones` tool by Len Shustek.

https://github.com/LenShustek/miditones

`miditones -v -i -pt The-Empire-Strikes-Back-\(From-\'Starwars\'\).mid`

This tool is generating 6 channels by default. It is generating a `.c` file nearly ready to be used in the demo.

The generated file must be modified a little bit before being used. 

Look at first lines of `empire.c` .

