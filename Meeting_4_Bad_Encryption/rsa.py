# Copyright Joan Montas
# All rights reserved.
# License under GNU General Public License v3.0

import random
import math

def phiFunction(p, q):
    # find phi as defined in the RSA protocol
    return (p - 1) * (q - 1)

def isPrime(n):
    # naive prime number
    for i in range(2,n):
        if (n%i) == 0:
            return False
    return True

def getAPrimeLesserThan(i):
    # returns a prime number lesser than the given value
    p = random.randint(2, i - 1)
    while not isPrime(p):
        p = random.randint(2, i - 1)
    return p

def maxBit(i):
    # returns maximum possible bits the given integer value can be defined as
    return math.floor(math.log2(i)) + 1

def encrypt(m, pk):
    # encrypt one character at a time, and convert the entire string into a
    # numerical value
    e, n = pk
    x = 0
    bits = maxBit(n)
    for i in m:
        c = (ord(i) ** e) % n
        x = (x << bits) + c
    return x

def decrypt(m, pk):
    # gather each character and decrypt. Turn it back into a string
    d, n = pk
    x = ""
    bits = maxBit(n)
    while m != 0:
        c = m & ((1 << bits) - 1)
        c = (c ** d) % n
        c = chr(c)
        x = c + x
        m = m >> bits
    return x

# main choose two random prime number.
# Ensure that both prime number added is greater than 256
# since n should be greater than the value that is being encrypted
p = 0
q = 0
n = 0
while n < 256:
    # choose any strength of bits 2**10 for sanity check
    p = getAPrimeLesserThan(2**9)
    q = getAPrimeLesserThan(p)
    n = p * q

phi = phiFunction(p, q)

e = None
while True:
    # find a number e that satisfies the equation defined
    # in the rsa protocol
    e = random.randint(2, phi - 1)
    if math.gcd(e, phi) == 1:
        break

# define d as define in the rsa protocol
d = pow(e, -1, phi)

# create public and private keys
publicKey = (e, n)
privateKey = (d, n)

# show case your parameters
print(f"p = {p}, q = {q}, n = {n}, phi = {phi}, e = {e}, d = {d}")


def encrypt_blockwise(m, pk):
    e, n = pk
    input_block_size = 240  # You can adjust based on n's size.
    m_bytes = m.encode('utf-8')
    
    # Chunk the message
    blocks = [m_bytes[i:i + input_block_size] for i in range(0, len(m_bytes), input_block_size)]
    
    encrypted_blocks = []
    for block in blocks:
        num_representation = int.from_bytes(block, byteorder='big')
        encrypted_block = pow(num_representation, e, n)
        encrypted_blocks.append(encrypted_block.to_bytes((n.bit_length() + 7) // 8, byteorder='big'))
        
    return b''.join(encrypted_blocks)

def decrypt_blockwise(c, sk):
    d, n = sk
    encrypted_block_size = (n.bit_length() + 7) // 8
    blocks = [c[i:i + encrypted_block_size] for i in range(0, len(c), encrypted_block_size)]
    
    decrypted_blocks = []
    for block in blocks:
        num_representation = int.from_bytes(block, byteorder='big')
        decrypted_block = pow(num_representation, d, n)
        decrypted_blocks.append(decrypted_block.to_bytes((decrypted_block.bit_length() + 7) // 8, byteorder='big'))
    
    return b''.join(decrypted_blocks).decode('utf-8')

# encrypt and decrypt the given message
mes = ""
sec = encrypt(mes, publicKey)
dec =  decrypt(sec, privateKey)
print(f"The actual message = {mes}")
print(f"The secret = {sec}")
print(f"The decrypted = {dec}")

# el fin
