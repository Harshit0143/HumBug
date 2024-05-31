import os
from tqdm import tqdm

import subprocess
import re

def contains_integer(s):
    integers = re.findall(r'\d+', s)
    return bool(integers)
def extract_integer(s):
    integers = re.findall(r'\d+', s)
    return integers
def write_str(text , file_name):
    with open(file_name , 'w') as f:
        f.write(text)




for idx in tqdm(range(15 , 91)):
    file_name = f'./test_cases/level_{idx}.txt'
    with open(file_name , 'r') as file:
        lines = file.readlines()
        while not contains_integer(lines[-1]):
            lines.pop()
        max_moves = extract_integer(lines[-1])[0]

        
        command = f'bash ./run.sh  {max_moves} {file_name}'
        result = subprocess.run(command, shell = True , capture_output = True, text = True)
        write_str(result.stdout[: -1] , f'solutions/level_{idx}.txt')
        assert result.stderr == ""

