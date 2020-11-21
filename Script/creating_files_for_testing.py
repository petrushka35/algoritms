import random
from pathlib import Path

d = Path('input')
d.mkdir(parents=True,exist_ok=True)
k = Path('results')
k.mkdir(parents=True,exist_ok=True)
k = Path('true_results')
k.mkdir(parents=True,exist_ok=True)

a = ''
min=100
for i in range(0,100):
    p = Path('input/input' + str(i).zfill(3)+".txt",exist_ok=True)
    step=random.randint(min+100, min + 200)
    a+=str(step)+"\n"
    for m in range(step):
        a+=str(random.randint(-100,100))+' '
    min=step
    p.write_text(a[:-1])
    a=''


for i in range(0, 100):
    input_file = open("input/input" + str(i).zfill(3) + ".txt", "r")
    input_argv = input_file.read()
    argv_arr = list(map(int, input_argv.split()))
    
    argv_arr.sort()

    output_txt = open("true_results/output" + str(i).zfill(3) + ".txt", "w")

    len_a = len(argv_arr)

    for j in range(0, len_a - 2):
        output_txt.write(str(argv_arr[j]) + " ")
    
    output_txt.write(str(argv_arr[len_a - 2]))

    output_txt.close()

print("my mission is done, now you can kill me :)")