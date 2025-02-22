# Smile Chess engine :)
- using raylib and C

# IMPORTANT
    -> ak to bude niekedy randomne hadzat seg fault, moze to byt isCheck (mozno tym ze som tam nemal ziadnych kingov xd)

### overall todo 
    [x] create basics
        [x] project setup
        [x] render board
        [x] render pieces
    [x] create game of chess
        [x] basic moving pieces
            [x] isCheck
            [x] generate pseudo legal moves
            [x] filter legal moves
            [x] actually move those pieces
            [x] capturing pieces
        [x] fancy moves 
            [x] en passant 
            [x] castle
            [x] promotion (for queen only)
        [x] winning 
            [x] checkmate
            [x] stalemate
            [x] draw (only kings left ig)
    [] create engine
        [x] setup code (try with random moves)
        [] code minimax
            [] make undoMove function (needed for a minimax [probably])
                [x] basic moves
                [x] promotions
                [x] castle
                [] capture
                [] everything for black as well
            [] implement basic minimax
            [] implement alpha beta pruning
    [] optional
        [] add suport for all promoting pieces
