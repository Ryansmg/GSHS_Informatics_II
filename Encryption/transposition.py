import sys
en = [2, 6, 1, 7, 0, 5, 3, 4]
de = [4, 2, 0, 6, 7, 5, 1, 3]
mask = 0x80

p = sys.stdin.readline()
e = ['\0'] * len(p)
d = ['\0'] * len(e)

# Encryption
for i in range(len(p)):
    for j in range(8):
        if ord(p[i]) & (mask >> en[j]):
            e[i] = chr(ord(e[i]) | (mask >> j))
e = ''.join(e)
print(e)

# Decryption
for i in range(len(e)):
    for j in range(8):
        if ord(e[i]) & (mask >> de[j]):
            d[i] = chr(ord(d[i]) | (mask >> j))
d = ''.join(d)
print(d)
