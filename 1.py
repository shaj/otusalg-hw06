#!/usr/bin/env python3

import sys
import random


arraysize = 1000

if(len(sys.argv) > 1):
	try:
		arraysize = int(sys.argv[1])
	except:
		arraysize = 1000


ia = int(arraysize * 0.05)
ib = int(arraysize * 0.95)
print(ia, ib)

l = [i for i in range(arraysize)]

a = l[ia]
l[ia] = l[ib]
l[ib] = a

with open('o{}.txt'.format(arraysize), 'w') as f:
    f.write("%s\n" % len(l))
    for item in l:
        f.write("%s\n" % item)

random.shuffle(l) 

with open('s{}.txt'.format(arraysize), 'w') as f:
    f.write("%s\n" % len(l))
    for item in l:
        f.write("%s\n" % item)

