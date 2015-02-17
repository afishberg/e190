import sys


infilename = sys.argv[1]
outfilename = sys.argv[2]

infile = open(infilename, 'r')
content = infile.read()
infile.close()

outfile = open(outfilename, 'w')
outfile.write('seconds,')
outfile.write('falls,')
outfile.write('reversals,')
outfile.write('attacks,')
outfile.write('dmgdealt,')
outfile.write('dmgtaken,')
outfile.write('score,')
outfile.write('times hit,')
outfile.write('times hit enemies')
outfile.write('\n')

rows = content.split('\n')

rows = rows[2:] # remove first two rows
lenrows = len(rows)

i = 1

time = long(rows[0].split(',')[0])
taken = 0
given = 0
prev = []

while i < lenrows and rows[i] != '':
	if 'START STAGE' in rows[i]:
		line = prev

		outfile.write(str(long(line[0]) - time))
		outfile.write(',')
		outfile.write(line[2])
		outfile.write(',')
		outfile.write(line[13])
		outfile.write(',')
		outfile.write(line[14])
		outfile.write(',')
		outfile.write(line[15])
		outfile.write(',')
		outfile.write(line[16])
		outfile.write(',')
		outfile.write(line[19])
		outfile.write(',')
		outfile.write(str(taken))
		outfile.write(',')
		outfile.write(str(given))
		outfile.write('\n')

		taken = 0
		given = 0
		time = long(rows[i].split(',')[0])

	else:
		prev = rows[i].split(',')
		if len(prev) < 22:
			print prev, i
		if 'user' == prev[20]:
			taken += 1
		else:
			given +=1



	i += 1

line = prev

outfile.write(str(long(line[0]) - time))
outfile.write(',')
outfile.write(line[2])
outfile.write(',')
outfile.write(line[12])
outfile.write(',')
outfile.write(line[13])
outfile.write(',')
outfile.write(line[14])
outfile.write(',')
outfile.write(line[15])
outfile.write(',')
outfile.write(line[18])
outfile.write(',')
outfile.write(str(taken))
outfile.write(',')
outfile.write(str(given))
outfile.write('\n')

outfile.close()