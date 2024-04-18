
import subprocess
import sys

file =  sys.argv[1]
command =["fstdraw", file ,f"{file}.dot"]
subprocess.run(command)
with open(f"{file}.dot","r") as f:
    lines = f.readlines()
    lines = lines[7:]
    line = [ i.strip() for i in lines]
    print(line)