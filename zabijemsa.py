

def format_64bit_to_32bit_parts(value):
    lower_half = value & 0xFFFFFFFF
    upper_half = (value >> 32) & 0xFFFFFFFF
    return f"0x{lower_half:08X}, 0x{upper_half:08X}"

def format_to_my_uint64t(value):
    lower_half = value & 0xFFFFFFFF
    upper_half = (value >> 32) & 0xFFFFFFFF
    start = "{{"
    close = "}}"
    return f"(BITBOARD_Bitboard){start}0x{lower_half:08X}, 0x{upper_half:08X}{close},"

def print_in_c_arr_format_64(arr):
    with open("out.txt", 'w') as file:
        print("array = {", file=file)
        for value in arr:
            print("\t", format_to_my_uint64t(value), file=file)
        print("};", file=file)

def print_in_c_arr_format_64_512(arr):
    with open("out.txt", 'w') as file:
        print("array = {", file=file)
        for i in range(64):
            print("\t{", file=file)
            for j in range(512):
                print("\t\t", format_to_my_uint64t(arr[i][j]), file=file, end="")
                if(j%3==0):
                    print("", file=file)
            print("\t},", file=file)
        print("};", file=file)

def to_uint64(value):
    return value & 0xFFFFFFFFFFFFFFFF

def print_bitboard(bitboard):
    for r in range(8):
        for c in range(8):
            if bitboard & (1 << (r * 8 + c)):
                print("1", end=" ")
            else:
                print(".", end=" ")
        print()
    print()


# import itertools
#
# bishop_magics = [
#     0x89A1121896040240, 0x2004844802002010, 0x2068080051921000, 0x62880A0220200808, # 3
#     0x0004042004000000, 0x0100822020200011, 0xC00444222012000A, 0x0028808801216001, # 7
#     0x0400492088408100, 0x0201C401040C0084, 0x00840800910A0010, 0x4004880840020, # 11
#     0x2000840504006000, 0x30010C4108405004, 0x1008005410080802, 0x8144042209100900, # 15
#     0x0208081020014400, 0x004800201208CA00, 0x0F18140408012008, 0x1004002802102001, # 19
#     0x0841000820080811, 0x0040200200A42008, 0x0520040470104290, 0x88010400410C9000, # 23
#     0x0520040470104290, 0x1004040051500081, 0x2002081833080021, 0x9e7401c064010036, # 27
#     0x941408200C002000, 0x0658810000806011, 0x0188071040440A00, 0x4800404002011C00, # 31
#     0x0104442040404200, 0x0511080202091021, 0x0004022401120400, 0x80C0040400080120, # 35
#     0x8040010040820802, 0x0480810700020090, 0x0102008E00040242, 0x0809005202050100, # 39
#     0x8002024220104080, 0x0431008804142000, 0x0019001802081400, 0x0200014208040080, # 43
#     0x3308082008200100, 0x041010500040C020, 0x4012020C04210308, 0x208220A202004080, # 47
#     0x0111040120082000, 0x6803040141280A00, 0x2101004202410000, 0x8200000041108022, # 51
#     0x0000021082088000, 0x0002410204010040, 0x8012020C04210308, 0x0822088220820214, # 55
#     0x0040808090012004, 0x00910224040218C9, 0x0402814422015008, 0x0814021148200820, # 59
#     0x6803040141280A00, 0x004800201208CA00, 0x0F18140408012008, 0x1020020408102040  # 63 
# ]
#
# shift_value = 55
#
# attack_table = [[0 for i in range(512)] for i in range(64)]
#
#
# def generate_bishop_masks(square):
#     mask = 0
#     row, col = divmod(square, 8)
#     directions = [(-1, -1), (-1, 1), (1, -1), (1, 1)]
#     
#     for dr, dc in directions:
#         r, c = row + dr, col + dc
#         while 1 <= r < 7 and 1 <= c < 7:
#             mask |= 1 << (r * 8 + c)
#             r += dr
#             c += dc
#     
#     return mask
#
#
# def generate_blocker_combinations(mask):
#     blocker_squares = [i for i in range(64) if mask & (1 << i)]  # get all bits set in the mask
#     num_squares = len(blocker_squares)
#     combinations = []
#     
#     for subset in range(1 << num_squares):
#         blocker_board = 0
#         for i in range(num_squares):
#             if subset & (1 << i):
#                 blocker_board |= 1 << blocker_squares[i]
#         combinations.append(blocker_board)
#     
#     return combinations
#
#
#
#
# # 4. Fix validate_magics function to properly track uniqueness
# def validate_magics():
#     indexes = [[] for i in range(64)]  # List of indices for each square
#     unique = [True for i in range(64)]  # Track uniqueness for each square
#     
#     for i in range(64):
#         bishop_mask = generate_bishop_masks(i)  # Get bishop attack mask for the square
#         blockers = generate_blocker_combinations(bishop_mask)  
#         # print_bitboard(bishop_mask)
#         
#         # print(f"Validating magic for square {i}...")  # Debug line
#         
#         for mask in blockers:
#             index = to_uint64(mask * bishop_magics[i]) >> shift_value
#             # print(f"Blocker mask: {mask}, Index: {index}")  # Debug line
#             
#             # Check if index already exists for this square
#             if index in indexes[i]:
#                 unique[i] = False  # Collision detected, magic number is not unique
#             else:
#                 indexes[i].append(index)  # Store the unique index for future checks
#     
#     size = 0
#     for i in indexes:
#         size += len(i)
#     print(size)
#
#     # Output squares that have non-unique magic numbers
#     for i in range(len(unique)):
#         # print(max(indexes[i]))
#         if not unique[i]:
#             print(f"Magic number for square {i} is not unique!")
#
# def bishop_attack_mask(square, occupancy):
#     def slide_attacks(square, occupancy, deltas):
#         attacks = 0
#         row, col = divmod(square, 8)
#         
#         for dr, dc in deltas:
#             r, c = row + dr, col + dc
#             while 0 <= r < 8 and 0 <= c < 8:
#                 target_square = r * 8 + c
#                 attacks |= (1 << target_square)  # Add the target square to the attack mask
#                 if occupancy & (1 << target_square):  # Stop sliding if a blocker is encountered
#                     break
#                 r += dr
#                 c += dc
#         
#         return attacks
#
#     # Bishop moves diagonally
#     directions = [(-1, -1), (-1, 1), (1, -1), (1, 1)]
#     return slide_attacks(square, occupancy, directions)
#
# def generate_bishop_attack_masks():
#     
#     for i in range(64):
#         bishop_mask = generate_bishop_masks(i)  # Get bishop attack mask for the square
#         blockers = generate_blocker_combinations(bishop_mask)  
#         
#         for mask in blockers:
#             index = to_uint64(mask * bishop_magics[i]) >> shift_value
#             attack_table[i][index] =  bishop_attack_mask(i, mask)
#
# # Run the validation
# validate_magics()
# # generate_bishop_attack_masks()
# # print_in_c_arr_format_64(bishop_magics)
# bishop_mask = [generate_bishop_masks(i) for i in range(64)]
# print_in_c_arr_format_64(bishop_mask)
# # print_in_c_arr_format_64_512(attack_table)
#
# def find_unique_magic_for_square(square, shift_value, trials=1_000_000):
#     from random import randint
#
#     bishop_mask = generate_bishop_masks(square)
#     blockers = generate_blocker_combinations(bishop_mask)
#     required_bits = len(blockers)
#
#     for _ in range(trials):
#         magic_candidate = (randint(0, (1 << 64) - 1) & 0xFFFFFFFFFFFFFFFF)
#         if bin(magic_candidate).count("1") < 6:  # Skip weak candidates
#             continue
#
#         indexes = {}
#         unique = True
#
#         for blocker in blockers:
#             index = to_uint64(blocker * magic_candidate) >> shift_value
#             if index in indexes:
#                 unique = False
#                 break
#             indexes[index] = blocker
#
#         if unique:
#             return magic_candidate
#
#     raise RuntimeError(f"Could not find a unique magic number for square {square} after {trials} trials.")
#
# # Example of generating magic for square 27
# # square_27_magic = find_unique_magic_for_square(27, shift_value=shift_value, trials=10_000_000_000_000)
# # print(f"Unique magic number for square 27: {hex(square_27_magic)}")


rook_magics = [
    0x8A80104000800020,
    0x0140002000100040,
    0x02801880A0017001,
    0x0100081001000420,
    0x0200020010080420,
    0x03001C0002010008,
    0x8480008002000100,
    0x2080088004402900,
    0x0000800098204000,
    0x2024401000200040,
    0x0100802000801000,
    0x0120800800801000,
    0x0208808088000400,
    0x0002802200800400,
    0x2200800100020080,
    0x0801000060821100,
    0x0080044006422000,
    0x0100808020004000,
    0x12108A0010204200,
    0x0140848010000802,
    0x0481828014002800,
    0x8094004002004100,
    0x4010040010010802,
    0x0000020008806104,
    0x0100400080208000,
    0x2040002120081000,
    0x0021200680100081,
    0x0020100080080080,
    0x0002000A00200410,
    0x0000020080800400,
    0x0080088400100102,
    0x0080004600042881,
    0x4040008040800020,
    0x0440003000200801,
    0x0004200011004500,
    0x0188020010100100,
    0x0014800401802800,
    0x2080040080800200,
    0x0124080204001001,
    0x0200046502000484,
    0x0480400080088020,
    0x1000422010034000,
    0x0030200100110040,
    0x0000100021010009,
    0x2002080100110004,
    0x0202008004008002,
    0x0020020004010100,
    0x2048440040820001,
    0x0101002200408200,
    0x0040802000401080,
    0x4008142004410100,
    0x02060820C0120200,
    0x0001001004080100,
    0x020C020080040080,
    0x2935610830022400,
    0x0044440041009200,
    0x0280001040802101,
    0x2100190040002085,
    0x80C0084100102001,
    0x4024081001000421,
    0x00020030A0244872,
    0x0012001008414402,
    0x02006104900A0804,
    0x0001004081002402,
]

rook_shifts = [
  52, 53, 53, 53, 53, 53, 53, 52, 
  53, 54, 54, 54, 54, 54, 54, 53, 
  53, 54, 54, 54, 54, 54, 54, 53, 
  53, 54, 54, 54, 54, 54, 54, 53, 
  53, 54, 54, 54, 54, 54, 54, 53, 
  53, 54, 54, 54, 54, 54, 54, 53, 
  53, 54, 54, 54, 54, 54, 54, 53, 
  52, 53, 53, 53, 53, 53, 53, 52, 
]

def generate_rook_mask(square):
    if not (0 <= square < 64):
        raise ValueError("Square must be between 0 and 63.")

    attack_mask = 0

    rank = square // 8
    file = square % 8

    for f in range(1,7):
        if f != file:  # Exclude the square itself
            attack_mask |= 1 << (rank * 8 + f)

    for r in range(1,7):
        if r != rank:  # Exclude the square itself
            attack_mask |= 1 << (r * 8 + file)

    return attack_mask

print_bitboard(generate_rook_mask(27))

def generate_blocker_combinations_rook(mask):
    blocker_indices = [i for i in range(64) if (mask >> i) & 1]
    num_blockers = len(blocker_indices)

    blocker_combinations = []
    for combination in range(1 << num_blockers):
        blocker = 0
        for i in range(num_blockers):
            if (combination >> i) & 1:
                blocker |= 1 << blocker_indices[i]
        blocker_combinations.append(blocker)

    return blocker_combinations

def validate_magics_rook():
    indexes = [[] for i in range(64)]  # List of indices for each square
    unique = [True for i in range(64)]  # Track uniqueness for each square
    
    for i in range(64):
        rook_mask = generate_rook_mask(i)  # Get bishop attack mask for the square
        blockers = generate_blocker_combinations_rook(rook_mask)  
        # print_bitboard(bishop_mask)
        
        # print(f"Validating magic for square {i}...")  # Debug line
        
        for mask in blockers:
            index = to_uint64(mask * rook_magics[i]) >> rook_shifts[i]
            # print(f"Blocker mask: {mask}, Index: {index}")  # Debug line
            
            # Check if index already exists for this square
            if index in indexes[i]:
                unique[i] = False  # Collision detected, magic number is not unique
            else:
                indexes[i].append(index)  # Store the unique index for future checks
    
    size = 0
    for i in indexes:
        size += len(i)
    print(size)

    # Output squares that have non-unique magic numbers
    for i in range(len(unique)):
        # print(max(indexes[i]))
        if not unique[i]:
            print(f"Magic number for square {i} is not unique!")

validate_magics_rook()


