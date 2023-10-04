# Copyright Joan Montas
# All rights reserved.
# License under GNU General Public License v3.0

def encrypt(m, k):
    # encrypt message
    # loop message (ith characters) and find the ith element of the key
    # notice key might be smaller or greater than the message, thus
    # obtain the ith size-of-message's modulus
    x = ""
    m = m.lower()
    vegieregraph = []
    for i in range(26):
        row = []
        single = i
        for j in range(26):
            row.append(single % 26)
            single = single + 1
        vegieregraph.append(row)
    newM = ""
    for i in m:
        if i.isalpha():
            newM = newM + i
    m = newM
    for i in range(0, len(m)):
        c = m[i]
        c = ord(c) - ord('a')
        r = k[i%len(k)]
        r = ord(r) - ord('a')
        y = vegieregraph[r][c]
        y = chr(y + ord('a'))
        x = x + y
    return x

def linearSearch(e, r):
    # given an element, find its position
    for i in range(len(r)):
        if r[i] == e:
            return i
    return -1

def decrypt(s, k):
    s = s.lower()
    vegieregraph = []
    for i in range(26):
        row = []
        single = i
        for j in range(26):
            row.append(single % 26)
            single = single + 1
        vegieregraph.append(row)
    m = ""
    for i in range(0, len(s)):
        char = s[i]
        char = ord(char) - ord('a')
        r = k[i% len(k)]                            # find row
        r = ord(r) - ord('a')
        c = linearSearch(char, vegieregraph[r])     # find column
        char = chr( c + ord('a'))                   # decrypt the char
        m = m + char
    return m

key = ""
plain = ""
sec = encrypt(plain, key)
print(sec)
dec = decrypt(sec, key)
print(dec)



