message  = "Dvogs: MssnmQogv. W bssr giddzwsg. O uib, o giwh, gcas wqs qfsoa, shq. Gc W dzob hc aoys o fiu-dizz qfmdhc qiffsbqm qozzsr MssnmQogv. Soqv hcysb wg kcfhv 1 Mssnm gbsoysf. “Wh wgb'h xigh  qiffsbqm; wh'g o ghohsasbh. Ksof wh, tzoibh wh, hfors wh.”"

alphabet = "abcdefghijklmnopqrstuvwxyz"

for i in range(0, 26):
    decrypted = ""
    for char in message:
        if char.isalpha():
            newCharIndex = (alphabet.index(char.lower()) + i) % 26
            newChar = alphabet[newCharIndex]
            decrypted += newChar

    print(decrypted)

