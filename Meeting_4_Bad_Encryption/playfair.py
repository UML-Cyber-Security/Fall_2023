def matrix(key):
    matrix = []
    for e in key.upper():
        if e not in matrix:
            matrix.append(e)
    alphabet = "ABCDEFGHIKLMNOPQRSTUVWXYZ"
    for e in alphabet:
        if e not in matrix:
            matrix.append(e)
    matrix_group = []
    for e in range(5):
        matrix_group.append('')
    matrix_group[0] = matrix[0:5]
    matrix_group[1] = matrix[5:10]
    matrix_group[2] = matrix[10:15]
    matrix_group[3] = matrix[15:20]
    matrix_group[4] = matrix[20:25]
    return matrix_group

def find_position(key_matrix, letter):
    x = y = 0
    for i in range(5):
        for j in range(5):
            if key_matrix[i][j] == letter:
                x = i
                y = j
    return x, y

def encrypt(message, key):
    message = message.upper().replace("J", "I")
    key_matrix = matrix(key)
    i = 0
    result = []
    while i < len(message):
        a = message[i]
        i += 1
        b = message[i] if i < len(message) and message[i] != a else 'X'
        i += 1
        ax, ay = find_position(key_matrix, a)
        bx, by = find_position(key_matrix, b)
        if ax == bx:
            if ay == 4:
                ay = -1
            if by == 4:
                by = -1
            result.append(key_matrix[ax][ay+1])
            result.append(key_matrix[bx][by+1])
        elif ay == by:
            if ax == 4:
                ax = -1
            if bx == 4:
                bx = -1
            result.append(key_matrix[ax+1][ay])
            result.append(key_matrix[bx+1][by])
        else:
            result.append(key_matrix[ax][by])
            result.append(key_matrix[bx][ay])
    return ''.join(result)

def decrypt(message, key):
    key_matrix = matrix(key)
    i = 0
    result = []
    while i < len(message):
        a = message[i]
        i += 1
        b = message[i]
        i += 1
        ax, ay = find_position(key_matrix, a)
        bx, by = find_position(key_matrix, b)
        if ax == bx:
            if ay == 0:
                ay = 5
            if by == 0:
                by = 5
            result.append(key_matrix[ax][ay-1])
            result.append(key_matrix[bx][by-1])
        elif ay == by:
            if ax == 0:
                ax = 5
            if bx == 0:
                bx = 5
            result.append(key_matrix[ax-1][ay])
            result.append(key_matrix[bx-1][by])
        else:
            result.append(key_matrix[ax][by])
            result.append(key_matrix[bx][ay])
    return ''.join(result)

if __name__ == "__main__":
    key = ""
    message = ""
    encrypted_msg = encrypt(message, key)
    decrypted_msg = decrypt(encrypted_msg, key)
    print(f"Message: {message}")
    print(f"Encrypted: {encrypted_msg}")
    print(f"Decrypted: {decrypted_msg}")
