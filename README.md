# Smile Chess engine :)
- using raylib and C

# IMPORTANT
    -> ak to bude niekedy randomne hadzat seg fault, moze to byt isCheck (mozno tym ze som tam nemal ziadnych kingov xd)

### overall todo 
    [x] create basics
        [x] project setup
        [x] render board
        [x] render pieces
    [] create game of chess
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
        [] winning 
            [] checkmate
            [] stalemate
            [] draw (only kings left ig)
    [] create engine
        [] setup code (try with random moves)
        [] code basic minimax
    [] optional
        [] add suport for all promoting pieces
