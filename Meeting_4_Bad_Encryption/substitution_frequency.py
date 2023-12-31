hex_string = "cbbae7d33da8e01a052b3d2b243de742052de605d4a824e7a8051a2d05cbd4e72da81ad32d3de74a052da81aa8ba3de7246b1a2d2d3d2de7a8051a2de7d4d4e7c81a24e7a81a245cca243dd3d33dcae7d3b81a3dc805ca3d2d05a8ba052d4a052be72de61a1ad4a8ba3d4205e605e03de724d31a423de7ff05e7a81a24d32a2d6bd4e7d3d33dd3e72d052b3dd32a05a8e72dca2be724245ce7ca1a2ac8d43dd32b1a1acb1ae62bba1a2b1ad4e7a83d2bba05cb052b3d2b243de742e72dca1ae62b1a2a24d33d05e005d4d4c824052d6be72be7d33da81a2be724245c425ccb240542e7245c1ac8b83d2ba805ff3d2b1a24ca5c2b3dcb422ad3ba241a1a42d3"
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
