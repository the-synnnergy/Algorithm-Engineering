import os
import subprocess
import pandas as pd




results = list()
rootdir = "solutions"
for subdir, dirs, files in os.walk(rootdir):
    for file in files:
        file_comp = os.path.join(subdir,file)
        temp_row = list()
        f = open(file_comp,"r")
        header = f.readline()
        header = header.split("[ms]:")
        instance_name = header[0].split()[0]
        print(header)
        print(instance_name)
        time = int(header[1])
        number_nodes = int(f.readline())
        print(number_nodes)
        terminals = f.readline().count("1")
        print(terminals)
        edges = int(f.readline())
        print(edges)
        sol = 0
        for i in range(edges):
            edge = f.readline().split()
            sol = sol + int(edge[2])
        print(sol)
        temp_row.append(instance_name)
        temp_row.append(number_nodes)
        temp_row.append(terminals)
        temp_row.append(edges)
        temp_row.append(sol)
        temp_row.append(time)
        results.append(temp_row)


df = pd.DataFrame(results,columns=["Instance","Nodes","Terminals","Edges","Solutions","Time"])
df.to_csv("solutions.csv")