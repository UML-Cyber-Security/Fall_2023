import random

key = ""

# Convert key to an int
seed = sum(ord(c) for c in key)

# Create a separate Random instance with the given seed
rand_gen = random.Random(seed)

ascii_values = list(range(256))
shuffled_values = ascii_values.copy()

# Shuffle the values using the seeded random instance
rand_gen.shuffle(shuffled_values)

# Create encryption and decryption mappings
encryption_map = dict(zip(ascii_values, shuffled_values))
decryption_map = dict(zip(shuffled_values, ascii_values))

def encrypt(message):
    return bytes([encryption_map[b] for b in message])

def decrypt(ciphertext):
    return bytes([decryption_map[b] for b in ciphertext])

# Test the encryption and decryption
message = b""
encrypted = encrypt(message)
decrypted = decrypt(encrypted)

print("Original Message:", message)
print("Encrypted:", encrypted.hex())
print("Decrypted:", decrypted)
