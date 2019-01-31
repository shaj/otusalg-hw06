#!/usr/bin/env python3

import random

arraysize = 67890
ia = int(arraysize * 0.05)
ib = int(arraysize * 0.95)
print(ia, ib)

l = [i for i in range(arraysize)]

a = l[ia]
l[ia] = l[ib]
l[ib] = a

with open('1.txt', 'w') as f:
    f.write("%s\n" % len(l))
    for item in l:
        f.write("%s\n" % item)

random.shuffle(l) 

with open('shuffle.txt', 'w') as f:
    f.write("%s\n" % len(l))
    for item in l:
        f.write("%s\n" % item)

