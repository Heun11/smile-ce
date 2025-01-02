

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



import itertools

bishop_magics = [
    0x89A1121896040240, 0x2004844802002010, 0x2068080051921000, 0x62880A0220200808, # 3
    0x0004042004000000, 0x0100822020200011, 0xC00444222012000A, 0x0028808801216001, # 7
    0x0400492088408100, 0x0201C401040C0084, 0x00840800910A0010, 0x4004880840020, # 11
    0x2000840504006000, 0x30010C4108405004, 0x1008005410080802, 0x8144042209100900, # 15
    0x0208081020014400, 0x004800201208CA00, 0x0F18140408012008, 0x1004002802102001, # 19
    0x0841000820080811, 0x0040200200A42008, 0x0520040470104290, 0x88010400410C9000, # 23
    0x0520040470104290, 0x1004040051500081, 0x2002081833080021, 0x9e7401c064010036, # 27
    0x941408200C002000, 0x0658810000806011, 0x0188071040440A00, 0x4800404002011C00, # 31
    0x0104442040404200, 0x0511080202091021, 0x0004022401120400, 0x80C0040400080120, # 35
    0x8040010040820802, 0x0480810700020090, 0x0102008E00040242, 0x0809005202050100, # 39
    0x8002024220104080, 0x0431008804142000, 0x0019001802081400, 0x0200014208040080, # 43
    0x3308082008200100, 0x041010500040C020, 0x4012020C04210308, 0x208220A202004080, # 47
    0x0111040120082000, 0x6803040141280A00, 0x2101004202410000, 0x8200000041108022, # 51
    0x0000021082088000, 0x0002410204010040, 0x8012020C04210308, 0x0822088220820214, # 55
    0x0040808090012004, 0x00910224040218C9, 0x0402814422015008, 0x0814021148200820, # 59
    0x6803040141280A00, 0x004800201208CA00, 0x0F18140408012008, 0x1020020408102040  # 63 
]

shift_value = 55

attack_table = [[0 for i in range(512)] for i in range(64)]


def generate_bishop_masks(square):
    mask = 0
    row, col = divmod(square, 8)
    directions = [(-1, -1), (-1, 1), (1, -1), (1, 1)]
    
    for dr, dc in directions:
        r, c = row + dr, col + dc
        while 1 <= r < 7 and 1 <= c < 7:
            mask |= 1 << (r * 8 + c)
            r += dr
            c += dc
    
    return mask


def generate_blocker_combinations(mask):
    blocker_squares = [i for i in range(64) if mask & (1 << i)]  # get all bits set in the mask
    num_squares = len(blocker_squares)
    combinations = []
    
    for subset in range(1 << num_squares):
        blocker_board = 0
        for i in range(num_squares):
            if subset & (1 << i):
                blocker_board |= 1 << blocker_squares[i]
        combinations.append(blocker_board)
    
    return combinations


def print_bitboard(bitboard):
    for r in range(8):
        for c in range(8):
            if bitboard & (1 << (r * 8 + c)):
                print("1", end=" ")
            else:
                print(".", end=" ")
        print()
    print()


# 4. Fix validate_magics function to properly track uniqueness
def validate_magics():
    indexes = [[] for i in range(64)]  # List of indices for each square
    unique = [True for i in range(64)]  # Track uniqueness for each square
    
    for i in range(64):
        bishop_mask = generate_bishop_masks(i)  # Get bishop attack mask for the square
        blockers = generate_blocker_combinations(bishop_mask)  
        # print_bitboard(bishop_mask)
        
        # print(f"Validating magic for square {i}...")  # Debug line
        
        for mask in blockers:
            index = to_uint64(mask * bishop_magics[i]) >> shift_value
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

def bishop_attack_mask(square, occupancy):
    def slide_attacks(square, occupancy, deltas):
        attacks = 0
        row, col = divmod(square, 8)
        
        for dr, dc in deltas:
            r, c = row + dr, col + dc
            while 0 <= r < 8 and 0 <= c < 8:
                target_square = r * 8 + c
                attacks |= (1 << target_square)  # Add the target square to the attack mask
                if occupancy & (1 << target_square):  # Stop sliding if a blocker is encountered
                    break
                r += dr
                c += dc
        
        return attacks

    # Bishop moves diagonally
    directions = [(-1, -1), (-1, 1), (1, -1), (1, 1)]
    return slide_attacks(square, occupancy, directions)

def generate_bishop_attack_masks():
    
    for i in range(64):
        bishop_mask = generate_bishop_masks(i)  # Get bishop attack mask for the square
        blockers = generate_blocker_combinations(bishop_mask)  
        
        for mask in blockers:
            index = to_uint64(mask * bishop_magics[i]) >> shift_value
            attack_table[i][index] =  bishop_attack_mask(i, mask)

# Run the validation
validate_magics()
# generate_bishop_attack_masks()
# print_in_c_arr_format_64(bishop_magics)
bishop_mask = [generate_bishop_masks(i) for i in range(64)]
print_in_c_arr_format_64(bishop_mask)
# print_in_c_arr_format_64_512(attack_table)

def find_unique_magic_for_square(square, shift_value, trials=1_000_000):
    from random import randint

    bishop_mask = generate_bishop_masks(square)
    blockers = generate_blocker_combinations(bishop_mask)
    required_bits = len(blockers)

    for _ in range(trials):
        magic_candidate = (randint(0, (1 << 64) - 1) & 0xFFFFFFFFFFFFFFFF)
        if bin(magic_candidate).count("1") < 6:  # Skip weak candidates
            continue

        indexes = {}
        unique = True

        for blocker in blockers:
            index = to_uint64(blocker * magic_candidate) >> shift_value
            if index in indexes:
                unique = False
                break
            indexes[index] = blocker

        if unique:
            return magic_candidate

    raise RuntimeError(f"Could not find a unique magic number for square {square} after {trials} trials.")

# Example of generating magic for square 27
# square_27_magic = find_unique_magic_for_square(27, shift_value=shift_value, trials=10_000_000_000_000)
# print(f"Unique magic number for square 27: {hex(square_27_magic)}")
