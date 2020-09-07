input()
input()
buf = None
filename = None
while True:
    try:
        line = input().strip('\n').split(': ')
    except EOFError:
        break

    if len(line) == 1:
        filename = line[0]
        buf = bytearray(open(filename, 'rb').read())

        print(f'{filename=}')

    elif len(line) == 2:
        addr = int(line[0], 16)
        line = line[1].split(' ')
        before = int(line[0], 16)
        after = int(line[1], 16)

        print(f'{addr=} {before=} {after=}')

        if buf:
            assert buf[addr] == before
            buf[addr] = after

fout = open(filename+'.patched', 'wb')
fout.write(buf)
fout.close()
