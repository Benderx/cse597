import matplotlib.pyplot as plt

def decipher_line(line):
    line = line.strip()
    broken = line.split(',')
    new = []
    for b in range(len(broken)-1):
        new.append(float(broken[b]))
    return new

data = []
with open("out.csv") as f:
    header = decipher_line(f.readline())
    header2 = decipher_line(f.readline())
    count = 0
    for line in f:
        new = decipher_line(line)
        data.append(new)
        count += 1


counter = 0
h = []
for line in data:
    new = plt.plot(header[:len(line)], line, linestyle='dashed', 
        marker='.', label=(str(header2[counter]) + 'B'))[0]
    h.append(new)
    counter += 1


plt.legend(handles=h)

plt.xscale('log')

plt.ylabel('Time (ns)')
plt.xlabel('Stride (bytes)')
plt.show()