poop
====

Turing tarpit language currently writing for PLT Games competition

^ increments accumulator
- negates accumulator
`some-text' places value of "some-text" local register in accumulator
`some-text+ adds value of "some-text" local register to accumulator
;some-text' places value of "some-text" global register to accumulator
;some-text+ adds value of "some-text" global register to accumulator
>`some-text' stuffs the accumulator into local register "some-text"
>;some-text' stuffs the accumulator into global register "some-text"
>1 stuffs the accumulator onto stdout as an ASCII character
>2 stuffs the accumulator onto stderr as an ASCII character

*some-text| places current continuation in continuation variable "some-text"
!some-text| replaces current continuation with continuation variable "some-text"
?some-text| replaces current continuation with continuation variable "some-text" if the accumulator is non-zero
{ creates a new scope
} exits the current scope, if any.

local registers are dynamically scoped.