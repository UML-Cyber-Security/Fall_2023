hex_string = ""
byte_data = bytes.fromhex(hex_string)

# Conduct frequency analysis
frequency = {}
for byte in byte_data:
    if byte not in frequency:
        frequency[byte] = 0
    frequency[byte] += 1

# Sort the byte values by frequency
sorted_frequency = sorted(frequency.items(), key=lambda item: item[1], reverse=True)

# Create an initial "decoded" list with underscores
decoded_array = ['_' for _ in byte_data]

substitution = {}

for byte, freq in sorted_frequency:
    print(f"Byte: {byte:02x}, Frequency: {freq}")
    replace_char = input("Enter the character you want to replace with or leave blank to skip: ")
    if replace_char:
        substitution[byte] = replace_char
        for i, b in enumerate(byte_data):
            if b == byte:
                decoded_array[i] = replace_char

    # Print the current state of the decoded message after each substitution
    decoded_message = ''.join(decoded_array)
    print("\nCurrent Decoded Message:")
    print(decoded_message)
    print("\n----------------------\n")
