# Optimal Ride the Bus
## Red or Black
| value | action | expectation |
| --- | --- | --- |
| n.a. | red | 1.4421 |
| n.a. | black | 1.4421 |
## Upper or Lower
| card#1 | action | expectation | 
| --- | --- | --- |
| 2 | upper | 4.03297 |
| 3 | upper | 3.61681 |
| 4 | upper | 3.23393 |
| 5 | upper | 2.88435 |
| 6 | upper | 2.56807 |
| 7 | upper | 2.28507 |
| 8 | upper | 2.03537 |
| 9 | forfeit | 2 |
| 10 | lower | 2.26843 |
| J | lower | 2.58471 |
| Q | lower | 2.93429 |
| K | lower | 3.31717 |
| A | lower | 3.73333 |
## Inside or Outside
| abs(card#1 - card#2) | action | expectation |
| --- | --- | --- |
|   0   | outside | 5.09388 |
|   1   | outside | 4.66939 |
|   2   | outside | 4.2449 |
|   3   | outside | 3.82041 |
|   4   | outside | 3.39592 |
|   5   | forfeit | 3 |
|   6   | forfeit | 3 |
|   7   | inside | 3.18367 |
|   8   | inside | 3.60816 |
|   9   | inside | 4.03265 |
|   10  | inside | 4.45714 |
|   11  | inside | 4.88163 |
|   12  | inside | 5.30612 |
## Suit
| value | action | expectation |
| --- | --- | --- |
| any | any suit not in card#1,card#2,card#3 | 5.30612 |
