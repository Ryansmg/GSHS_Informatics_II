en = "ksrdngfbjcpwyuhtvaoqlziexm"
de = [''] * 26
p = input()
e = ""
d = ""

# Encryption
for c in p:
    if 'a' <= c <= 'z':
        e += en[ord(c) - ord('a')]
    else:
        e += c
print(e)

# Decryption
for i in range(26):
    de[ord(en[i]) - ord('a')] = chr(ord('a'+i))

for c in e:
    if 'a' <= c <= 'z':
        d += de[ord(c) - ord('a')]
    else:
        d += c
print(d)
