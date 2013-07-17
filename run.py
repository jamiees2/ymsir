import subprocess
p = subprocess.Popen(['./main'],stdout=subprocess.PIPE,stdin=subprocess.PIPE,stderr=subprocess.PIPE,shell=True)
l = ['MELODY\n',"*"*(8+8) + "\n"]
sin, serr = p.communicate(input="".join(l).encode('utf8'))
print('STDIN: ' + str(sin,encoding="utf8"))
print('STDERR: ' + str(serr,encoding="utf8"))
print(p.returncode)
