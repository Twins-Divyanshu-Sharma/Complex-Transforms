# Complex-Transforms

### A COMPILER for Transformations in Argand Plane

A compiler is made that converts complex equation to openGL program and then shows the transformation visually

### How to Use

The complex variable is z. Any transformation can be applied on z and seen visually.\
Terminate the equation using '!' \
Program has three buttons
* Press __'R'__ to restart animation
* Press __'Z'__ to zoom 
* Press __'shift + Z'__ to zoom out

### Lexer
The following represents the DFA ( Deterministic Finite Automaton ) which is used to convert incoming stream of characters into tokens representing complex number, identifier or an operator.

```mermaid
graph LR;
    0((0))--digit-->1((1))
    0((0))--Operator-->10(((10)))
    0((0))--whitespace-->11(((11)))
    0((0))--i-->5((5))
    0((0))--alphabet-->9(((9)))
    
    1((1))--i-->4(((4)))
    1((1))--digit-->1((1))
    1((1))--decimal-->2((2))
    

    2((2))--digit-->3((3))
    3((3))--digit-->3((3))
    3((3))--i-->4(((4)))

    5((5))--digit-->6((6))
    5((5))--alphabet-->9(((9)))

    6((6))--decimal-->7((7))
    6((6))--alphabet-->9(((9)))
    6((6))--digit-->6((6))

    7((7))--digit-->8(((8)))

    8(((8)))--digit-->8(((8)))

    9(((9)))--digit | alphabet | i-->9(((9)))
    
```

### Parser
The following are the production rules.
```
M -> id = X
X -> -E | E
E -> E+T | E-T
T -> T*F | T/F
F -> id | real | imaginary | (X) 
```
After removing left recursion for LL(1) parser
```
M -> id = X
X -> -E | E
E -> TE"
E" -> +TE" | -TE" | e
T -> FT"
T" -> *FT" | /FT" | e
F -> id | real | imaginary | (X)
```

### Predictive Parsing Table
Since LL(1) grammar was used, the production rules are modified to eliminate left recursion
| | id | $ | imaginary | real | + | - | * | / | ( | ) |
|---|---|---|---|---|---|---|---|---|---|---|
| M | M -> id=X | | | | | | | | | | 
| X | X -> E | | X -> E | X -> E | | X -> -E | | | X -> E | |
| E | E -> TE" | | E -> TE" | E -> TE" | | | | | E -> TE" | |
| E" | | E" -> e | | | E" -> +TE" | E" -> -TE" | | | | E" -> e | 
| T | T -> FT" | | T -> FT" | T -> FT" | | | | | T -> FT" | |
| T" | | T" -> e | | | T" -> e | T" -> e | T" -> *FT" | T" -> /FT" | | T" -> e |
| F | F -> id | | F -> imaginary | F -> real | | | | | F -> (X) | |

### Some Examples

```
z = z*z
!
```
![zSquare](https://user-images.githubusercontent.com/47611597/147360623-c6c6b4ea-0086-4db7-9b82-b07093c3dcfa.gif)


```
z = 100/z
!
```
![zDivide](https://user-images.githubusercontent.com/47611597/147360633-eb86c1cd-647f-4f4c-88b8-016a787e1db6.gif)


```
z = z*z*z/100
!
```
![zCubed](https://user-images.githubusercontent.com/47611597/147360646-9fa9c2c4-4c7c-444d-a1ca-a3cd062d9348.gif)


