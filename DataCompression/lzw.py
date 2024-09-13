endic = {}
dcnt = 1
enc = []

infile = open("lwztext.txt", "r")
outfile = open("lzwencoded.txt", "w")
content = infile.read()
for c in content:
    s = c
    if s not in endic:
        endic[s] = dcnt
        dcnt += 1
s = ''
ecnt = 1

for c in content:
    if s + c in endic:
        s += c
    else:
        enc.append(endic[s])
        endic[s+c] = dcnt
        dcnt += 1
        s = c

if s:
    enc.append(endic[s])

dcnt -= 1
print(dcnt)

for key, value in endic.items():
    print(f"{value} {key}")

for code in enc:
    print(code, end = ' ')
    outfile.write(str(code) + " ")

infile.close()
outfile.close()

#######################################################

dedic = {}
enc = []

dedic[1] = 'A'
dedic[2] = 'B'
dedic[3] = 'C'
dcnt = 4

infile = open("lzwencoded.txt", "r")
outfile = open("lzwdecoded.txt", "w")

for code in infile.read().split():
    enc.append(int(code))
ecnt = len(enc)

prestr = dedic[enc[0]]
outfile.write(prestr)
for i in range(1, ecnt):
    addstr = ''
    if enc[i] in dedic:
        addstr = prestr + dedic[enc[i]][0]
        prestr = dedic[enc[i]]
    else:
        addstr = prestr + prestr[0]
        prestr = addstr

    outfile.write(prestr)
    dedic[dcnt] = addstr
    dcnt += 1

for key, value in dedic.items():
    print(f"{key} {value}")

infile.close()
outfile.close()
