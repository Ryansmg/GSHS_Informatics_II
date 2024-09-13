import random

n = 10000
strlist = ['W'] * n

out = open("rletext_p.txt", "w")

random.seed()
for i in range(n//10):
    c = random.randrange(n)
    if strlist[c] == 'W':
        strlist[c] = 'B'
    else:
        strlist[c] = 'W'

for i in strlist:
    out.write(i)

out.close()

##############################################

infile = open("rletext_p.txt", "r")
outfile = open("rleencoded_p.txt", "w")

strlist = infile.read()

n = len(strlist)

i = 0
while i < n:
    cnt = 1
    while i + 1 < n and strlist[i] == strlist[i+1]:
        cnt += 1
        i += 1
    outfile.write(f"{cnt}{strlist[i]}")
    i += 1

infile.close()
outfile.close()

############################################

infile = open("rleencoded_p.txt", "r")
outfile = open("rledecoded_p.txt", "w")

strlist = infile.read()

n = len(strlist)

i = 0
while i < n:
    cnt = 0
    while i < n and '0' <= strlist[i] <= '9':
        cnt = cnt * 10
        cnt += (ord(strlist[i]) - ord('0'))
        i += 1

    if i < n:
        outfile.write(strlist[i]*cnt)

    i += 1

infile.close()
outfile.close()