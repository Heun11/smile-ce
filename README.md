# Smile Chess engine :)
- Raylib & C

# IMPORTANT
    -> ak to bude niekedy randomne hadzat seg fault, moze to byt isCheck (mozno tym ze som tam nemal ziadnych kingov xd)

    -> do buducna board->bools moze robit castling problemy v minimaxe
        - asi nerobi xd

    -> stane sa niekedy ze opakuje tie iste tahy aj ked ma na vyber (ak opakujes aj ty samozrejme)

    -> niekedy sa stale (neviem preco a kedy) z kralovny spravi pesiak :D

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
            [x] make undoMove function (needed for a minimax [probably]) - should be working :D
                [x] basic moves
                [x] promotions
                [x] castle
                [x] capture
                [x] niekedy sa stane ze sa zmena neprejavi v all_pieces 
                    (ked capturnes tak z all_pieces sa vymaze to co si capturol)
                [x] everything for black as well
                    [x] basic moves
                    [x] promotions
                    [x] castle
                    [x] capture
                [x] capture en passant
                    [x] vpodstate ked odvratis en passanta tak uz sa neda spravit :D
            [x] implement basic minimax
            [x] implement alpha beta pruning
            [] make better evaluation function
            [] speed things up a bit
    [] optional
        [] add suport for all promoting pieces

### ideas for optimalization for future
    [] make BOARD_Move smaller by storing it all in uint16_t and then use masking and bitshifts to use 
        6bits for "from", 6bits for "to" and remaining 4 to store the "promotion"
    [] maybe even replace BOARD_MoveList with like whole bitmap which would represent all possible moves for given piece  
    

